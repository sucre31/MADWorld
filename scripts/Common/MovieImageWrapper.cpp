#pragma once
#include <fstream>
#include "MovieImageWrapper.h"
#include <DxLib.h>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavutil/mem.h>

    // リンカへのライブラリ指示
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "avutil.lib")
}

MovieData MovieImageWrapper::load(const std::string& filePath) {
    AppLogAdd("MovieImageWrapper::load: Start [%s]\n", filePath.c_str());
    MovieData data;
    data.msPerFrame = 33; // デフォルト値(約30fps)
    std::vector<int> handles;

    // 1. フォーマットコンテキストの準備
    AVFormatContext* pFormatCtx = nullptr;
    AppLogAdd("MovieImageWrapper::load: Calling avformat_open_input...\n");
    if (avformat_open_input(&pFormatCtx, filePath.c_str(), nullptr, nullptr) != 0) {
        AppLogAdd("MovieImageWrapper::load: ERROR - avformat_open_input failed\n");
        return data;
    }

    AppLogAdd("MovieImageWrapper::load: Calling avformat_find_stream_info...\n");
    if (avformat_find_stream_info(pFormatCtx, nullptr) < 0) {
        AppLogAdd("MovieImageWrapper::load: ERROR - avformat_find_stream_info failed\n");
        avformat_close_input(&pFormatCtx);
        return data;
    }

    // 2. ビデオストリームの検索
    AppLogAdd("MovieImageWrapper::load: Finding video stream...\n");
    int videoStreamIdx = -1;
    for (unsigned int i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIdx = i;
            break;
        }
    }
    if (videoStreamIdx == -1) {
        AppLogAdd("MovieImageWrapper::load: ERROR - No video stream found\n");
        avformat_close_input(&pFormatCtx);
        return data;
    }

    // 3. デコーダの検索とオープン
    AVRational fps = pFormatCtx->streams[videoStreamIdx]->avg_frame_rate;
    if (fps.num > 0 && fps.den > 0) {
        data.msPerFrame = (int)(1000.0 * fps.den / fps.num);
    }

    AVCodecParameters* pCodecPar = pFormatCtx->streams[videoStreamIdx]->codecpar;
    const AVCodec* pCodec = nullptr;
    if (pCodecPar->codec_id == AV_CODEC_ID_VP9) {
        pCodec = avcodec_find_decoder_by_name("libvpx-vp9");
    }
    if (!pCodec) {
        pCodec = avcodec_find_decoder(pCodecPar->codec_id);
    }
    if (!pCodec) {
        AppLogAdd("MovieImageWrapper::load: ERROR - Codec not found\n");
        avformat_close_input(&pFormatCtx);
        return data;
    }

    AVCodecContext* pCodecCtx = avcodec_alloc_context3(pCodec);
    avcodec_parameters_to_context(pCodecCtx, pCodecPar);

    AVDictionary* opts = nullptr;
    av_dict_set(&opts, "alpha_mode", "1", 0);

    AppLogAdd("MovieImageWrapper::load: Calling avcodec_open2...\n");
    if (avcodec_open2(pCodecCtx, pCodec, &opts) < 0) {
        AppLogAdd("MovieImageWrapper::load: ERROR - avcodec_open2 failed\n");
        av_dict_free(&opts);
        avcodec_free_context(&pCodecCtx);
        avformat_close_input(&pFormatCtx);
        return data;
    }
    av_dict_free(&opts);

    // 4. フレームバッファとスケーラーの準備
    AppLogAdd("MovieImageWrapper::load: Allocating frames and buffer...\n");
    AVFrame* pFrame = av_frame_alloc();
    AVFrame* pFrameRGB = av_frame_alloc();
    int width = pCodecCtx->width;
    int height = pCodecCtx->height;

    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_BGRA, width, height, 1);
    uint8_t* buffer = (uint8_t*)av_malloc(numBytes);
    av_image_fill_arrays(pFrameRGB->data, pFrameRGB->linesize, buffer, AV_PIX_FMT_BGRA, width, height, 1);

    struct SwsContext* swsCtx = nullptr;
    int64_t nb_frames = pFormatCtx->streams[videoStreamIdx]->nb_frames;
    if (nb_frames > 0) handles.reserve((size_t)nb_frames);
    else handles.reserve(120);

    // 5. デコードループ
    AppLogAdd("MovieImageWrapper::load: Starting decode loop (width:%d, height:%d)\n", width, height);
    AVPacket* packet = av_packet_alloc();
    int frameCount = 0;

    while (av_read_frame(pFormatCtx, packet) >= 0) {
        if (packet->stream_index == videoStreamIdx) {
            if (avcodec_send_packet(pCodecCtx, packet) >= 0) {
                while (avcodec_receive_frame(pCodecCtx, pFrame) >= 0) {
                    if (swsCtx == nullptr) {
                        AppLogAdd("MovieImageWrapper::load: Calling sws_getContext...\n");
                        swsCtx = sws_getContext(
                            pFrame->width, pFrame->height, (AVPixelFormat)pFrame->format,
                            width, height, AV_PIX_FMT_BGRA,
                            SWS_BILINEAR, nullptr, nullptr, nullptr
                        );
                        if (!swsCtx) AppLogAdd("MovieImageWrapper::load: WARNING - sws_getContext returned null!\n");
                    }

                    if (swsCtx) {
                        sws_scale(swsCtx, pFrame->data, pFrame->linesize, 0, pFrame->height,
                            pFrameRGB->data, pFrameRGB->linesize);

                        int softImg = MakeARGB8ColorSoftImage(width, height);
                        uint8_t* dest = (uint8_t*)GetImageAddressSoftImage(softImg);
                        int pitch = GetPitchSoftImage(softImg); // DxLibが確保した実際の1行のバイト数（ピッチ）を取得

                        for (int y = 0; y < height; y++) {
                            // destのY行目の先頭アドレスを、正確なpitchを使って計算する
                            uint8_t* destRow = dest + (y * pitch);
                            uint8_t* srcRow = pFrameRGB->data[0] + (y * pFrameRGB->linesize[0]);

                            // コピーするサイズは「幅×4」と「DxLibのピッチ」と「FFmpegのラインサイズ」の中で一番小さい安全なサイズにする
                            int copySize = width * 4;
                            if (pitch < copySize) copySize = pitch;
                            if (pFrameRGB->linesize[0] < copySize) copySize = pFrameRGB->linesize[0];

                            memcpy(destRow, srcRow, copySize);
                        }

                        SetDrawValidAlphaChannelGraphCreateFlag(TRUE);
                        int h = CreateGraphFromSoftImage(softImg);
                        SetDrawValidAlphaChannelGraphCreateFlag(FALSE);

                        if (h != -1) {
                            handles.push_back(h);
                        }
                        else {
                            // DxLibのハンドル生成に失敗した場合（VRAM枯渇の可能性大）
                            AppLogAdd("MovieImageWrapper::load: ERROR - CreateGraphFromSoftImage failed at frame %d\n", frameCount);
                        }
                        DeleteSoftImage(softImg);

                        frameCount++;
                        if (frameCount % 50 == 0) {
                            AppLogAdd("MovieImageWrapper::load: ... decoded %d frames ...\n", frameCount);
                        }
                    }
                }
            }
        }
        av_packet_unref(packet);
    }

    AppLogAdd("MovieImageWrapper::load: Flushing remaining frames...\n");
    // 残存フレームのフラッシュ
    if (avcodec_send_packet(pCodecCtx, nullptr) >= 0) {
        while (avcodec_receive_frame(pCodecCtx, pFrame) >= 0) {
            if (swsCtx) {
                sws_scale(swsCtx, pFrame->data, pFrame->linesize, 0, pFrame->height,
                    pFrameRGB->data, pFrameRGB->linesize);

                int softImg = MakeARGB8ColorSoftImage(width, height);
                uint8_t* dest = (uint8_t*)GetImageAddressSoftImage(softImg);
                int pitch = GetPitchSoftImage(softImg); // DxLibが確保した実際の1行のバイト数（ピッチ）を取得

                for (int y = 0; y < height; y++) {
                    // destのY行目の先頭アドレスを、正確なpitchを使って計算する
                    uint8_t* destRow = dest + (y * pitch);
                    uint8_t* srcRow = pFrameRGB->data[0] + (y * pFrameRGB->linesize[0]);

                    // コピーするサイズは「幅×4」と「DxLibのピッチ」と「FFmpegのラインサイズ」の中で一番小さい安全なサイズにする
                    int copySize = width * 4;
                    if (pitch < copySize) copySize = pitch;
                    if (pFrameRGB->linesize[0] < copySize) copySize = pFrameRGB->linesize[0];

                    memcpy(destRow, srcRow, copySize);
                }

                SetDrawValidAlphaChannelGraphCreateFlag(TRUE);
                int h = CreateGraphFromSoftImage(softImg);
                SetDrawValidAlphaChannelGraphCreateFlag(FALSE);

                if (h != -1) handles.push_back(h);
                DeleteSoftImage(softImg);

                frameCount++;
            }
        }
    }

    AppLogAdd("MovieImageWrapper::load: Total %d frames decoded. Starting cleanup...\n", frameCount);

    // 6. リソース解放
    av_packet_free(&packet);
    if (swsCtx) sws_freeContext(swsCtx);
    av_free(buffer);
    AppLogAdd("MovieImageWrapper::load: buffer freed\n");

    av_frame_free(&pFrameRGB);
    av_frame_free(&pFrame);
    AppLogAdd("MovieImageWrapper::load: frames freed\n");

    avcodec_free_context(&pCodecCtx);
    AppLogAdd("MovieImageWrapper::load: codec context freed\n");

    avformat_close_input(&pFormatCtx);
    AppLogAdd("MovieImageWrapper::load: format context closed\n");

    data.handles = std::move(handles);
    AppLogAdd("MovieImageWrapper::load: Finish Successfully\n");
    return data;
}