// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "AdvencedEyeClassifier.h"
#include <opencv2/tracking.hpp>
#include <opencv2/core.hpp>

AdvancedEyeClassifier::AdvancedEyeClassifier()
{
	tracker_ = cv::TrackerBoosting::create();
}

std::optional<cv::Rect> AdvancedEyeClassifier::detect(const cv::Mat& frame, const cv::Rect& region)
{
	std::optional<cv::Rect> attempt;
	if (detector_ == detector::classifier) {
		attempt = EyeClassifier::detect(frame, region);
		if (attempt)
		{
			tracker_->init(frame, *attempt);
			detector_ = detector::tracker;
		}
	}
	else if (detector_ == detector::tracker)
	{
		if (cv::Rect2d tmp; tracker_->update(frame, tmp))
		{
			attempt = tmp;
		}
		else
		{
			attempt = EyeClassifier::detect(frame, region);
			if (attempt)
				detector_ = detector::tracker;
		}
	}

	return attempt;
}
