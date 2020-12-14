#pragma once
#include "EyeClassifier.h"
#include <opencv2/tracking.hpp>
#include <opencv2/core.hpp>

class AdvancedEyeClassifier :
    public EyeClassifier
{
	cv::Ptr<cv::Tracker> tracker_;
	enum class detector{
		classifier,
		tracker
	};	
	detector detector_;
public:
	AdvancedEyeClassifier();
	std::optional<cv::Rect> detect(const cv::Mat& frame, const cv::Rect& region) override;
};

