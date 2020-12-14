// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "PupilDetector.h"
#include "CVlegacy.h"

std::optional<cv::Point>
PupilDetector::detect(const cv::Mat& frame)
{
	auto eye_region = cv::Rect(0, 0, frame.cols, frame.rows);
	auto res = find_eye_center(frame, eye_region);
	return {res };
}

std::optional<cv::Point>
PupilDetector::detect(const cv::Mat& frame, const cv::Rect& eye_region)
{
	auto res = detect(frame(eye_region)).value();
	res.x += eye_region.x;
	res.y += eye_region.y;
	return { res };
}
