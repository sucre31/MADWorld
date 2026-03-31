#pragma once

#include <vector>
#include <string>

struct MovieData {
    std::vector<int> handles;
    int msPerFrame; // 1フレームあたりのミリ秒 (SozaiのplayRateに相当)
};

/**
 * @brief 動画ファイルを解析し、DXライブラリの画像ハンドルの配列に変換するユーティリティクラス
 */
class MovieImageWrapper {
public:
    /**
     * @brief 動画の全フレームをデコードし、DXライブラリのグラフィックハンドルを生成して返します。
     * @param filePath 動画ファイルへのパス
     * @return std::vector<int> 生成されたDXライブラリの画像ハンドル配列。失敗時は空。
     */
    static MovieData load(const std::string& filePath);

private:
    MovieImageWrapper() = delete; // インスタンス化を禁止
};