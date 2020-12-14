#pragma once
#include <optional>
#include <opencv2/core/types.hpp>

#include "IDetector.h"

class EyeRegions : public IDetector<std::tuple<cv::Rect, cv::Rect>>
{
public:
	virtual std::optional<std::tuple<cv::Rect, cv::Rect>>
	detect(const cv::Mat& frame) override;

	std::optional<std::tuple<cv::Rect, cv::Rect>>
	detect(const cv::Mat& frame, const cv::Rect& face_region);
};

