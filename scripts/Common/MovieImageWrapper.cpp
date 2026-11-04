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
    MovieData data;
    data.msPerFrame = 33; // デフォルト値(約30fps)
    std::vector<int> handles;

    // 1. フォーマットコンテキストの準備
    AVFormatContext* pFormatCtx = nullptr;
    if (avformat_open_input(&pFormatCtx, filePath.c_str(), nullptr, nullptr) != 0) {
        return data;
    }

    if (avformat_find_stream_info(pFormatCtx, nullptr) < 0) {
        avformat_close_input(&pFormatCtx);
        return data;
    }

    // 2. ビデオストリームの検索
    int videoStreamIdx = -1;
    for (unsigned int i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIdx = i;
            break;
        }
    }
    if (videoStreamIdx == -1) {
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
        // VP9の場合は、アルファチャンネルに対応している「libvpx-vp9」を強制する
        pCodec = avcodec_find_decoder_by_name("libvpx-vp9");
    }

    // 見つからなかった場合や、VP9以外の動画だった場合は標準のデコーダーを使う
    if (!pCodec) {
        pCodec = avcodec_find_decoder(pCodecPar->codec_id);
    }

    if (!pCodec) {
        avformat_close_input(&pFormatCtx);
        return data;
    }

    AVCodecContext* pCodecCtx = avcodec_alloc_context3(pCodec);
    avcodec_parameters_to_context(pCodecCtx, pCodecPar);

    // ★VP8/VP9デコーダーにアルファモードを強制
    AVDictionary* opts = nullptr;
    av_dict_set(&opts, "alpha_mode", "1", 0);

    if (avcodec_open2(pCodecCtx, pCodec, &opts) < 0) {
        av_dict_free(&opts);
        avcodec_free_context(&pCodecCtx);
        avformat_close_input(&pFormatCtx);
        return data;
    }
    av_dict_free(&opts);

    // 4. フレームバッファとスケーラーの準備
    AVFrame* pFrame = av_frame_alloc();
    AVFrame* pFrameRGB = av_frame_alloc();
    int width = pCodecCtx->width;
    int height = pCodecCtx->height;

    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_BGRA, width, height, 1);
    uint8_t* buffer = (uint8_t*)av_malloc(numBytes);
    av_image_fill_arrays(pFrameRGB->data, pFrameRGB->linesize, buffer, AV_PIX_FMT_BGRA, width, height, 1);

    // ★ここではまだ sws_getContext を作らない！
    struct SwsContext* swsCtx = nullptr;

    int64_t nb_frames = pFormatCtx->streams[videoStreamIdx]->nb_frames;
    if (nb_frames > 0) handles.reserve((size_t)nb_frames);
    else handles.reserve(120);

    // 5. デコードループ
    AVPacket* packet = av_packet_alloc();
    while (av_read_frame(pFormatCtx, packet) >= 0) {
        if (packet->stream_index == videoStreamIdx) {
            if (avcodec_send_packet(pCodecCtx, packet) >= 0) {
                while (avcodec_receive_frame(pCodecCtx, pFrame) >= 0) {
                    // ★ここから診断用ログ出力コード
                    static bool isFirstFrame = true;
                    if (isFirstFrame) {
                        std::ofstream log("webm_debug_log.txt");
                        log << "=== WebM Alpha Debug Log ===\n";
                        log << "File: " << filePath << "\n";
                        log << "1. Codec Context Format: " << av_get_pix_fmt_name(pCodecCtx->pix_fmt) << "\n";
                        log << "2. Decoded Frame Format: " << av_get_pix_fmt_name((AVPixelFormat)pFrame->format) << "\n";

                        if (pFrame->format == AV_PIX_FMT_YUVA420P) {
                            log << "   -> SUCCESS! Frame has Alpha channel (YUVA420P)\n";
                        }
                        else {
                            log << "   -> FAILURE! Frame does NOT have Alpha (Expected YUVA420P, got "
                                << av_get_pix_fmt_name((AVPixelFormat)pFrame->format) << ")\n";
                        }
                        isFirstFrame = false;
                    }

                    if (swsCtx == nullptr) {
                        swsCtx = sws_getContext(
                            pFrame->width, pFrame->height, (AVPixelFormat)pFrame->format,
                            width, height, AV_PIX_FMT_BGRA,
                            SWS_BILINEAR, nullptr, nullptr, nullptr
                        );
                    }

                    if (swsCtx) {
                        sws_scale(swsCtx, pFrame->data, pFrame->linesize, 0, pFrame->height,
                            pFrameRGB->data, pFrameRGB->linesize);

                        // ★変換後のピクセルのアルファ値をチェック
                        static bool isFirstPixelCheck = true;
                        if (isFirstPixelCheck) {
                            std::ofstream log("webm_debug_log.txt", std::ios::app);
                            int alpha255 = 0, alpha0 = 0, alphaOther = 0;
                            for (int y = 0; y < height; y++) {
                                for (int x = 0; x < width; x++) {
                                    int base = (y * pFrameRGB->linesize[0]) + (x * 4);
                                    uint8_t a = pFrameRGB->data[0][base + 3];
                                    if (a == 255) alpha255++;
                                    else if (a == 0) alpha0++;
                                    else alphaOther++;
                                }
                            }
                            log << "3. Sws_Scale BGRA Alpha Stats:\n";
                            log << "   A=255 (Opaque): " << alpha255 << " pixels\n";
                            log << "   A=0 (Transparent): " << alpha0 << " pixels\n";
                            log << "   A=1~254 (Semi): " << alphaOther << " pixels\n";

                            if (alpha0 == 0 && alphaOther == 0) {
                                log << "   -> FAILURE! All pixels are 100% opaque. Alpha was lost during conversion.\n";
                            }
                            else {
                                log << "   -> SUCCESS! Alpha values exist in BGRA buffer.\n";
                            }
                            log << "============================\n";
                            isFirstPixelCheck = false;
                        }

                        int softImg = MakeARGB8ColorSoftImage(width, height);
                        uint8_t* dest = (uint8_t*)GetImageAddressSoftImage(softImg);

                        for (int y = 0; y < height; y++) {
                            memcpy(dest + y * (width * 4),
                                pFrameRGB->data[0] + y * pFrameRGB->linesize[0],
                                width * 4);
                        }

                        SetDrawValidAlphaChannelGraphCreateFlag(TRUE);
                        int h = CreateGraphFromSoftImage(softImg);
                        SetDrawValidAlphaChannelGraphCreateFlag(FALSE);

                        if (h != -1) handles.push_back(h);
                        DeleteSoftImage(softImg);
                    }
                }
            }
        }
        av_packet_unref(packet);
    }

    // 残存フレームのフラッシュ
    if (avcodec_send_packet(pCodecCtx, nullptr) >= 0) {
        while (avcodec_receive_frame(pCodecCtx, pFrame) >= 0) {
            if (swsCtx) {
                sws_scale(swsCtx, pFrame->data, pFrame->linesize, 0, pFrame->height,
                    pFrameRGB->data, pFrameRGB->linesize);

                int softImg = MakeARGB8ColorSoftImage(width, height);
                uint8_t* dest = (uint8_t*)GetImageAddressSoftImage(softImg);

                for (int y = 0; y < height; y++) {
                    memcpy(dest + y * (width * 4),
                        pFrameRGB->data[0] + y * pFrameRGB->linesize[0],
                        width * 4);
                }

                SetDrawValidAlphaChannelGraphCreateFlag(TRUE);
                int h = CreateGraphFromSoftImage(softImg);
                SetDrawValidAlphaChannelGraphCreateFlag(FALSE);

                if (h != -1) handles.push_back(h);
                DeleteSoftImage(softImg);
            }
        }
    }

    // 6. リソース解放
    av_packet_free(&packet);
    if (swsCtx) sws_freeContext(swsCtx);
    av_free(buffer);
    av_frame_free(&pFrameRGB);
    av_frame_free(&pFrame);
    avcodec_free_context(&pCodecCtx);
    avformat_close_input(&pFormatCtx);

    data.handles = std::move(handles);
    return data;
}