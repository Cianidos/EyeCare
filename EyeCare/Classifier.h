#pragma once
#include <string>
#include <optional>
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>

#include "IDetector.h"

template<typename TClassifier = cv::CascadeClassifier>
class Classifier : public IDetector<cv::Rect>
{
protected:
	TClassifier classifier_;
	
public:
	Classifier(const std::string& path);
	std ::optional<cv::Rect> detect(const cv::Mat& frame) override;
};


inline Classifier<cv::CascadeClassifier>::Classifier(const std::string& path)
{
	if (!classifier_.load(path))
		printf("--(!)Error loading cascade\n");
}

inline std::optional<cv::Rect> Classifier<cv::CascadeClassifier>::detect(const cv::Mat& frame)
{
	std::vector<cv::Rect> res;
	classifier_.detectMultiScale( frame, res, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE|cv::CASCADE_FIND_BIGGEST_OBJECT, cv::Size(150, 150) );
	if (!std::empty(res))
		return { res.at(0) };
	else
		return {};
}
