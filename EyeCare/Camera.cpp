// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Camera.h"

Camera::Camera()
{
	capture_ = cv::VideoCapture(0);
}

void Camera::take_frame(cv::Mat& frame)
{
	static cv::Mat buffer_;
	do {
		capture_.read(buffer_);
		buffer_.copyTo(frame);
	} while (std::empty(buffer_));
	/* else
	{
		printf("No frame Captured");
	}
	*/
}
