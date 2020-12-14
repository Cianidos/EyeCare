// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "ImageDataCollector.h"

#include <opencv2/imgproc.hpp>
#include <opencv2/photo.hpp>

cv::Point operator+(const cv::Point& p, const cv::Size& s)
{
    cv::Point res;
    res.y += s.height;
    res.x += s.width;
    return res;
}

void ImageDataCollector::draw_rects(cv::Mat& frame, const std::vector<cv::Rect>& rects)
{
    for (const auto& rec : rects)
    {
        cv::rectangle(frame, rec, cv::Scalar(140, 10, 200));
    }
}


void ImageDataCollector::update()
{
    cv::setUseOptimized(true);

    camera_.take_frame(frame_);
    

    //cv::Mat new_image = cv::Mat::zeros(frame_.size(), frame_.type());
    //double alpha = 1.7; /*< Simple contrast control */
    //int beta = 20;       /*< Simple brightness control */

    //for (int y = 0; y < frame_.rows; y++) {
    //    for (int x = 0; x < frame_.cols; x++) {
    //        for (int c = 0; c < frame_.channels(); c++) {
    //            new_image.at<cv::Vec3b>(y, x)[c] =
	   //             cv::saturate_cast<uchar>(alpha * frame_.at<cv::Vec3b>(y, x)[c] + beta);
    //        }
    //    }
    //}

    //frame_ = new_image;

    //cv::cvtColor(frame_, frame_, cv::COLOR_BGR2HLS);
    //cv::Mat hsv_mat[3];
    //cv::split(frame_, hsv_mat);
    //cv::merge(hsv_mat, 3, frame_);
    //cv::cvtColor(frame_, frame_, cv::COLOR_HLS2BGR);

    cv::flip(frame_, frame_, 1);
    cv::cvtColor(frame_, gray_frame_, cv::COLOR_BGR2GRAY);

    cv::fastNlMeansDenoising(gray_frame_, gray_frame_);
    
    //cv::extractChannel(frame_, gray_frame_, 2);


    if (auto f = face_classifier_.detect(gray_frame_))
    {
        b_face_ = true;
        face_ = *f;
    }
    else b_face_ = false;

	std::tie(l_eye_region_, r_eye_region_) = eye_regions_.detect(gray_frame_, face_).value();

    const cv::Size half_face(face_.width / 2, face_.height);
    l_face = cv::Rect(
        face_.tl(), half_face
    );
    r_face = cv::Rect(
        cv::Point(face_.x + half_face.width, face_.y), half_face
    );

    if (auto le = eye_classifier_l.detect(gray_frame_, l_eye_region_))
    {
        b_l_eye_ = true;
        l_eye_ = *le;
    }
    else
    {
       // l_eye_ = cv::Rect();
	    b_l_eye_ = false;
    }

	if (auto re = eye_classifier_r.detect(gray_frame_, r_eye_region_))
    {
        b_r_eye_ = true;
        r_eye_ = *re;
    }
    else
    {
       // r_eye_ = cv::Rect();
        b_r_eye_ = false;
    }

    //l_eye_ = l_eye_region_;
    //r_eye_ = r_eye_region_;
	
    if (!std::empty(l_eye_))
    if (auto lp = pupil_.detect(gray_frame_, l_eye_))
        l_pupil_ = *lp;

    if (!std::empty(r_eye_))
    if (auto rp = pupil_.detect(gray_frame_, r_eye_))
        r_pupil_ = *rp;

    l_pupil_.x -= 2;
    l_pupil_.y -= 2;
    r_pupil_.x -= 2;
    r_pupil_.y -= 2;
}

QImage ImageDataCollector::get_image()
{
    cv::Mat cp;
    frame_.copyTo(cp);
    draw_rects(cp, { face_, l_eye_region_, r_eye_region_, l_eye_, r_eye_, l_face, r_face,
        cv::Rect(l_pupil_, cv::Size(5, 5)),
        cv::Rect(r_pupil_, cv::Size(5, 5)) });

    return QImage(cp.data, cp.cols, cp.rows, QImage::Format_BGR888);
}

cv::Size ImageDataCollector::img_size() const
{ return frame_.size(); }

QSize ImageDataCollector::img_qsize() const
{ return cvSz2qSz(img_size()); }




