#pragma once
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
        // ミリ秒 = 1000 / (num / den) => 1000 * den / num
        data.msPerFrame = (int)(1000.0 * fps.den / fps.num);
    }

    AVCodecParameters* pCodecPar = pFormatCtx->streams[videoStreamIdx]->codecpar;
    const AVCodec* pCodec = avcodec_find_decoder(pCodecPar->codec_id);
    if (!pCodec) {
        avformat_close_input(&pFormatCtx);
        return data;
    }

    AVCodecContext* pCodecCtx = avcodec_alloc_context3(pCodec);
    avcodec_parameters_to_context(pCodecCtx, pCodecPar);
    if (avcodec_open2(pCodecCtx, pCodec, nullptr) < 0) {
        avcodec_free_context(&pCodecCtx);
        avformat_close_input(&pFormatCtx);
        return data;
    }

    // 4. フレームバッファとスケーラーの準備
    AVFrame* pFrame = av_frame_alloc();
    AVFrame* pFrameRGB = av_frame_alloc();
    int width = pCodecCtx->width;
    int height = pCodecCtx->height;

    // DXライブラリとの親和性が高い BGRA 形式を指定
    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_BGRA, width, height, 1);
    uint8_t* buffer = (uint8_t*)av_malloc(numBytes);
    av_image_fill_arrays(pFrameRGB->data, pFrameRGB->linesize, buffer, AV_PIX_FMT_BGRA, width, height, 1);

    struct SwsContext* swsCtx = sws_getContext(
        width, height, pCodecCtx->pix_fmt,
        width, height, AV_PIX_FMT_BGRA,
        SWS_BILINEAR, nullptr, nullptr, nullptr
    );

    // フレーム数を予約して vector の再確保（out of range の原因）を防ぐ
    int64_t nb_frames = pFormatCtx->streams[videoStreamIdx]->nb_frames;
    if (nb_frames > 0) handles.reserve((size_t)nb_frames);
    else handles.reserve(120); // 不明な場合も最低限確保

    // 5. デコードループ
    AVPacket* packet = av_packet_alloc();
    while (av_read_frame(pFormatCtx, packet) >= 0) {
        if (packet->stream_index == videoStreamIdx) {
            if (avcodec_send_packet(pCodecCtx, packet) >= 0) {
                while (avcodec_receive_frame(pCodecCtx, pFrame) >= 0) {
                    // BGRAに変換
                    sws_scale(swsCtx, pFrame->data, pFrame->linesize, 0, height,
                        pFrameRGB->data, pFrameRGB->linesize);

                    // ソフトイメージを経由してハンドルを作成
                    int softImg = MakeSoftImage(width, height);

                    // ピクセルデータの転送
                    for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) {
                            int base = (y * pFrameRGB->linesize[0]) + (x * 4);
                            // FFmpeg(BGRA) -> DXLib(R, G, B, A)
                            DrawPixelSoftImage(softImg, x, y,
                                pFrameRGB->data[0][base + 2], // R
                                pFrameRGB->data[0][base + 1], // G
                                pFrameRGB->data[0][base + 0], // B
                                pFrameRGB->data[0][base + 3]  // A
                            );
                        }
                    }

                    int h = CreateGraphFromSoftImage(softImg);
                    if (h != -1) handles.push_back(h);
                    DeleteSoftImage(softImg);
                }
            }
        }
        av_packet_unref(packet);
    }

    // 6. リソース解放
    av_packet_free(&packet);
    sws_freeContext(swsCtx);
    av_free(buffer);
    av_frame_free(&pFrameRGB);
    av_frame_free(&pFrame);
    avcodec_free_context(&pCodecCtx);
    avformat_close_input(&pFormatCtx);

    data.handles = std::move(handles); // 結果を格納
    return data;
}