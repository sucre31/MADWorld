#include "CameraStream.h"
#include <cstring>

CameraStream::CameraStream() {}

CameraStream::~CameraStream()
{
	stop();
}

bool CameraStream::start(int camIndex, int w, int h)
{
	width = w;
	height = h;

	cap.open(camIndex, cv::CAP_DSHOW);

	if (!cap.isOpened())
		return false;

	cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
	cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);

	buffer = new unsigned char[width * height * 3];

	memset(&baseImage, 0, sizeof(BASEIMAGE));
	CreateFullColorData(&baseImage.ColorData);

	baseImage.GraphData = buffer;
	baseImage.Width = width;
	baseImage.Height = height;
	baseImage.Pitch = width * 3;

	runThread = true;
	captureThread = std::thread(&CameraStream::captureLoop, this);

	return true;
}

void CameraStream::stop()
{
	runThread = false;

	if (captureThread.joinable())
		captureThread.join();

	cap.release();

	if (buffer)
	{
		delete[] buffer;
		buffer = nullptr;
	}

	if (graphHandle != -1)
	{
		DeleteGraph(graphHandle);
		graphHandle = -1;
	}
}

void CameraStream::captureLoop()
{
	while (runThread)
	{
		cv::Mat frame;
		cap >> frame;

		if (frame.empty()) continue;

		//cv::flip(frame, frame, 1);

		{
			std::lock_guard<std::mutex> lock(frameMutex);
			threadFrame = frame.clone();
		}

		hasNewFrame = true;
	}
}

void CameraStream::update()
{
	if (!hasNewFrame.exchange(false))
		return;

	cv::Mat local;

	{
		std::lock_guard<std::mutex> lock(frameMutex);
		local = threadFrame.clone();
	}

	if (local.empty()) return;

	std::memcpy(buffer, local.data, width * height * 3);

	if (graphHandle == -1)
	{
		graphHandle = CreateGraphFromBaseImage(&baseImage);
	}
	else
	{
		ReCreateGraphFromBaseImage(&baseImage, graphHandle);
	}
}

int CameraStream::getGraphHandle() const
{
	return graphHandle;
}