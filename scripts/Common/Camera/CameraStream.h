#pragma once
#include <opencv2/opencv.hpp>
#include <thread>
#include <atomic>
#include <mutex>
#include <DxLib.h>

class CameraStream
{
public:
	CameraStream();
	~CameraStream();

	bool start(int camIndex = 0, int width = 1280, int height = 720);
	void stop();

	// DxLib側でそのまま描画できる
	int getGraphHandle() const;

	// 更新が必要なら呼ぶ（Scene側）
	void update();

	bool isRunning() const { return runThread; }

private:
	void captureLoop();

private:
	cv::VideoCapture cap;
	cv::Mat threadFrame;

	std::thread captureThread;
	std::atomic<bool> runThread = false;
	std::atomic<bool> hasNewFrame = false;

	mutable std::mutex frameMutex;

	// DxLib
	unsigned char* buffer = nullptr;
	int graphHandle = -1;

	BASEIMAGE baseImage;

	int width = 1280;
	int height = 720;
};