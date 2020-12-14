#pragma once
#include <optional>
#include <opencv2/core.hpp>

template <typename ReturnT>
class IDetector
{
public:
	virtual std::optional<ReturnT> detect(const cv::Mat& frame) = 0;
};

