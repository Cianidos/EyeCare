#pragma once

#include <opencv2/core.hpp>

//#include <mgl2/mgl.h>

#include <queue>
#include <cstdio>
#include <iostream>

////
// CONSTANTS
////
// Debugging
const bool kPlotVectorField = false;

// Size constants
const int kEyePercentTop = 30;
const int kEyePercentSide = 20;
const int kEyePercentHeight = 17;
const int kEyePercentWidth = 23;
//
// const int kEyePercentTop = 25;
// const int kEyePercentSide = 13;
// const int kEyePercentHeight = 30;
// const int kEyePercentWidth = 35;

// Preprocessing
const bool kSmoothFaceImage = false;
const float kSmoothFaceFactor = 0.005;

// Algorithm Parameters
const int kFastEyeWidth = 50;
const int kWeightBlurSize = 5;
const bool kEnableWeight = true;
const float kWeightDivisor = 1.0;
const double kGradientThreshold = 50.0;

// Postprocessing
const bool kEnablePostProcess = true;
const float kPostProcessThreshold = 0.97;

// Eye Corner
const bool kEnableEyeCorner = false;



/* Attempt at supporting openCV version 4.0.1 or higher */

#define K_EYE_LEFT true
#define K_EYE_RIGHT false

cv::Point find_eye_center(const cv::Mat& face, const cv::Rect& eye);
std::tuple<cv::Rect, cv::Rect> find_eyes(const cv::Mat& frame_gray, const cv::Rect& face);

void create_corner_kernels();
void release_corner_kernels();
cv::Point2f find_eye_corner(const cv::Mat& region,bool left, bool left2);
cv::Point2f find_subpixel_eye_corner(cv::Mat region, cv::Point maxP);

bool rect_in_image(const cv::Rect& rect, const cv::Mat& image);
bool in_mat(const cv::Point& p,int rows,int cols);
cv::Mat matrix_magnitude(const cv::Mat &matX, const cv::Mat &matY);
double compute_dynamic_threshold(const cv::Mat &mat, double stdDevFactor);
