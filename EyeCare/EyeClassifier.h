#pragma once
#include "Classifier.h"
#include <opencv2/core/types.hpp>

class EyeClassifier
	: public Classifier<>
{
public:
	EyeClassifier(const std::string& path =
		R"(.\haarcascade_eye_tree_eyeglasses.xml)")
		:Classifier(path) {}

	virtual std::optional<cv::Rect> detect(const cv::Mat& frame, const cv::Rect& region);
};

