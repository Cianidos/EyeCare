// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "EyeClassifier.h"

std::optional<cv::Rect> EyeClassifier::detect(const cv::Mat& frame, const cv::Rect& region)
{
	cv::Mat ROI(frame, region);
	auto res = Classifier::detect(ROI);
	if (res)
	{
		res->x += region.x;
		res->y += region.y;
	}
	return res;
}
