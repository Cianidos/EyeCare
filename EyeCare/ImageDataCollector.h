#pragma once

#include <QImage>
#include <QSize>
#include <opencv2/core.hpp>


#include "AdvencedEyeClassifier.h"
#include "Camera.h"
#include "FaceClassifier.h"
#include "EyeRegions.h"
#include "EyeClassifier.h"
#include "PupilDetector.h"



class ImageDataCollector
{
public:

    void update();
    QImage get_image();
    cv::Size img_size() const;
    QSize img_qsize() const;
	
    cv::Mat frame_;
    cv::Mat gray_frame_;
    cv::Rect face_, l_eye_region_, r_eye_region_, l_eye_, r_eye_, l_face, r_face;
	cv::Point l_pupil_, r_pupil_;
    bool b_face_, b_l_eye_, b_r_eye_;

private:

    void draw_rects(cv::Mat& frame, const std::vector<cv::Rect>& rects);

    Camera camera_;
    FaceClassifier face_classifier_;
    EyeRegions eye_regions_;
    EyeClassifier eye_classifier_l;
    EyeClassifier eye_classifier_r;
    PupilDetector pupil_;
};

inline QSize cvSz2qSz(const cv::Size& sz)
{
    return { sz.width, sz.height };
}
