#pragma once

#include <opencv2/videoio.hpp>

class Camera
{
	cv::VideoCapture capture_;

public:
	Camera();
	void take_frame(cv::Mat& frame);
};
