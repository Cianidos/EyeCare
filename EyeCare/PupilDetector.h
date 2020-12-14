#pragma once
#include <optional>
#include <opencv2/core.hpp>

#include "IDetector.h"

class PupilDetector : public IDetector<cv::Point>
{
public:
	std::optional<cv::Point>
	detect(const cv::Mat& frame) override;

	std::optional<cv::Point>
	detect(const cv::Mat& frame, const cv::Rect& eye_region);
};

