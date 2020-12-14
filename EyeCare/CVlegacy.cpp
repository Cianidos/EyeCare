// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <opencv2/imgproc.hpp>
#include "CVlegacy.h"

using namespace cv;

cv::Mat skin_cr_cb_hist = cv::Mat::zeros(cv::Size(256, 256), CV_8UC1);

std::tuple<cv::Rect, cv::Rect>
find_eyes(const cv::Mat& frame_gray, const cv::Rect& face) {
	cv::Mat face_roi = frame_gray(face);
	cv::Mat debug_face = std::move(face_roi);

	if (kSmoothFaceImage) {
		double sigma = kSmoothFaceFactor * face.width;
		GaussianBlur(face_roi, face_roi, cv::Size(0, 0), sigma);
	}
	//-- Find eye regions and draw them
	const auto width = static_cast<double>(face.width);
	const auto height = static_cast<double>(face.height);

	const int eye_region_width = cvRound(width * (kEyePercentWidth / 100.0));
	const int eye_region_height = cvRound(height * (kEyePercentHeight / 100.0));
	const int eye_region_top = cvRound(height * (kEyePercentTop / 100.0));

	cv::Rect left_eye_region(width * (kEyePercentSide / 100.0),
		eye_region_top, eye_region_width, eye_region_height);
	cv::Rect right_eye_region(width - eye_region_width - face.width * (kEyePercentSide / 100.0),
		eye_region_top, eye_region_width, eye_region_height);


	////-- Find Eye Centers
	//cv::Point leftPupil = findEyeCenter(faceROI,leftEyeRegion);
	//cv::Point rightPupil = findEyeCenter(faceROI,rightEyeRegion);

	//// change eye centers to face coordinates
	//rightPupil.x += rightEyeRegion.x;
	//rightPupil.y += rightEyeRegion.y;
	//leftPupil.x += leftEyeRegion.x;
	//leftPupil.y += leftEyeRegion.y;
	//// draw eye centers
	//circle(debugFace, rightPupil, 3, 1234);
	//circle(debugFace, leftPupil, 3, 1234);

	// get corner regions
	//cv::Rect leftRightCornerRegion(leftEyeRegion);
	//leftRightCornerRegion.width -= leftPupil.x;
	//leftRightCornerRegion.x += leftPupil.x;
	//leftRightCornerRegion.height /= 2;
	//leftRightCornerRegion.y += leftRightCornerRegion.height / 2;
	//cv::Rect leftLeftCornerRegion(leftEyeRegion);
	//leftLeftCornerRegion.width = leftPupil.x;
	//leftLeftCornerRegion.height /= 2;
	//leftLeftCornerRegion.y += leftLeftCornerRegion.height / 2;
	//cv::Rect rightLeftCornerRegion(rightEyeRegion);
	//rightLeftCornerRegion.width = rightPupil.x;
	//rightLeftCornerRegion.height /= 2;
	//rightLeftCornerRegion.y += rightLeftCornerRegion.height / 2;
	//cv::Rect rightRightCornerRegion(rightEyeRegion);
	//rightRightCornerRegion.width -= rightPupil.x;
	//rightRightCornerRegion.x += rightPupil.x;
	//rightRightCornerRegion.height /= 2;
	//rightRightCornerRegion.y += rightRightCornerRegion.height / 2;
	////draw rectangles
	//rectangle(debugFace,leftRightCornerRegion,200);
	//rectangle(debugFace,leftLeftCornerRegion,200);
	//rectangle(debugFace,rightLeftCornerRegion,200);
	//rectangle(debugFace,rightRightCornerRegion,200);
	////-- Find Eye Corners
	//if (kEnableEyeCorner) {
	//  cv::Point2f leftRightCorner = findEyeCorner(faceROI(leftRightCornerRegion), true, false);
	//  leftRightCorner.x += leftRightCornerRegion.x;
	//  leftRightCorner.y += leftRightCornerRegion.y;
	//  cv::Point2f leftLeftCorner = findEyeCorner(faceROI(leftLeftCornerRegion), true, true);
	//  leftLeftCorner.x += leftLeftCornerRegion.x;
	//  leftLeftCorner.y += leftLeftCornerRegion.y;
	//  cv::Point2f rightLeftCorner = findEyeCorner(faceROI(rightLeftCornerRegion), false, true);
	//  rightLeftCorner.x += rightLeftCornerRegion.x;
	//  rightLeftCorner.y += rightLeftCornerRegion.y;
	//  cv::Point2f rightRightCorner = findEyeCorner(faceROI(rightRightCornerRegion), false, false);
	//  rightRightCorner.x += rightRightCornerRegion.x;
	//  rightRightCorner.y += rightRightCornerRegion.y;
	//  circle(faceROI, leftRightCorner, 3, 200);
	//  circle(faceROI, leftLeftCorner, 3, 200);
	//  circle(faceROI, rightLeftCorner, 3, 200);
	//  circle(faceROI, rightRightCorner, 3, 200);
	//}

	//w.qtShow2(faceROI);
  //  cv::Rect roi( cv::Point( 0, 0 ), faceROI.size());
  //  cv::Mat destinationROI = debugImage( roi );
  //  faceROI.copyTo( destinationROI );
	return { left_eye_region, right_eye_region };
}


cv::Mat find_skin(cv::Mat& frame) {
	cv::Mat input;
	cv::Mat output = cv::Mat(frame.rows, frame.cols, CV_8U);

	cvtColor(frame, input, cv::COLOR_BGR2YCrCb);

	for (ptrdiff_t y = 0; y < input.rows; ++y) {
		const cv::Vec3b* Mr = input.ptr<cv::Vec3b>(y);
		//     uchar *Or = output.ptr<uchar>(y);
		auto* const Or = frame.ptr<cv::Vec3b>(y);
		for (ptrdiff_t x = 0; x < input.cols; ++x) {
			cv::Vec3b ycrcb = Mr[x];
			Or[x] = (skin_cr_cb_hist.at<uchar>(ycrcb[1], ycrcb[2]) > 0) ? 255 : 0;
			if (skin_cr_cb_hist.at<uchar>(ycrcb[1], ycrcb[2]) == 0) {
				Or[x] = cv::Vec3b(0, 0, 0);
			}
		}
	}
	return output;
}


//cvtColor( frame, frame_gray, cv::ColorConversionCodes::COLOR_BGR2GRAY);
//equalizeHist( frame_gray, frame_gray );
//cv::pow(frame_gray, CV_64F, frame_gray);



// Pre-declarations
cv::Mat flood_kill_edges(cv::Mat& mat);

#pragma mark Visualization
/*
template<typename T> mglData *matToData(const cv::Mat &mat) {
  mglData *data = new mglData(mat.cols,mat.rows);
  for (int y = 0; y < mat.rows; ++y) {
	const T *Mr = mat.ptr<T>(y);
	for (int x = 0; x < mat.cols; ++x) {
	  data->Put(((mreal)Mr[x]),x,y);
	}
  }
  return data;
}

void plotVecField(const cv::Mat &gradientX, const cv::Mat &gradientY, const cv::Mat &img) {
  mglData *xData = matToData<double>(gradientX);
  mglData *yData = matToData<double>(gradientY);
  mglData *imgData = matToData<float>(img);

  mglGraph gr(0,gradientX.cols * 20, gradientY.rows * 20);
  gr.Vect(*xData, *yData);
  gr.Mesh(*imgData);
  gr.WriteFrame("vecField.png");

  delete xData;
  delete yData;
  delete imgData;
}*/

#pragma mark Helpers

cv::Point unscale_point(const cv::Point& p, const cv::Rect& origSize) {
	const float ratio = (static_cast<float>(kFastEyeWidth) / origSize.width);
	const int x = round(p.x / ratio);
	const int y = round(p.y / ratio);
	return { x, y };
}

void scale_to_fast_size(const cv::Mat& src, cv::Mat& dst) {
	cv::resize(src, dst, cv::Size(kFastEyeWidth, (((float)kFastEyeWidth) / src.cols) * src.rows));
}

cv::Mat compute_mat_x_gradient(const cv::Mat& mat) {
	cv::Mat out(mat.rows, mat.cols, CV_64F);

	for (auto y = 0; y < mat.rows; ++y) {
		const auto* const Mr = mat.ptr<uchar>(y);
		auto* const Or = out.ptr<double>(y);

		Or[0] = Mr[1] - Mr[0];
		for (int x = 1; x < mat.cols - 1; ++x) {
			Or[x] = (Mr[x + 1] - Mr[x - 1]) / 2.0;
		}
		Or[mat.cols - 1] = Mr[mat.cols - 1] - Mr[mat.cols - 2];
	}

	return out;
}

#pragma mark Main Algorithm

void test_possible_centers_formula(int x, int y, const cv::Mat& weight, double gx, double gy, cv::Mat& out) {
	// for all possible centers
	for (int cy = 0; cy < out.rows; ++cy) {
		double* Or = out.ptr<double>(cy);
		const unsigned char* Wr = weight.ptr<unsigned char>(cy);
		for (int cx = 0; cx < out.cols; ++cx) {
			if (x == cx && y == cy) {
				continue;
			}
			// create a vector from the possible center to the gradient origin
			double dx = x - cx;
			double dy = y - cy;
			// normalize d
			const double magnitude = sqrt((dx * dx) + (dy * dy));
			dx = dx / magnitude;
			dy = dy / magnitude;
			double dot_product = dx * gx + dy * gy;
			dot_product = std::max(0.0, dot_product);
			// square and multiply by the weight
			if (kEnableWeight) {
				Or[cx] += dot_product * dot_product * (Wr[cx] / kWeightDivisor);
			}
			else {
				Or[cx] += dot_product * dot_product;
			}
		}
	}
}

cv::Point find_eye_center(const cv::Mat& face, const cv::Rect& eye) {
	cv::Mat eye_roi_unscaled = face(eye);
	cv::Mat eye_roi;
	scale_to_fast_size(eye_roi_unscaled, eye_roi);
	// draw eye region
	//rectangle(face,eye,1234);
	//-- Find the gradient
	cv::Mat gradientX = compute_mat_x_gradient(eye_roi);
	cv::Mat gradientY = compute_mat_x_gradient(eye_roi.t()).t();
	//-- Normalize and threshold the gradient
	// compute all the magnitudes
	cv::Mat mags = matrix_magnitude(gradientX, gradientY);
	//compute the threshold
	double gradientThresh = compute_dynamic_threshold(mags, kGradientThreshold);
	//double gradientThresh = kGradientThreshold;
	//double gradientThresh = 0;
	//normalize
	for (int y = 0; y < eye_roi.rows; ++y) {
		double* Xr = gradientX.ptr<double>(y), * Yr = gradientY.ptr<double>(y);
		const double* Mr = mags.ptr<double>(y);
		for (int x = 0; x < eye_roi.cols; ++x) {
			double gX = Xr[x], gY = Yr[x];
			double magnitude = Mr[x];
			if (magnitude > gradientThresh) {
				Xr[x] = gX / magnitude;
				Yr[x] = gY / magnitude;
			}
			else {
				Xr[x] = 0.0;
				Yr[x] = 0.0;
			}
		}
	}
	//imshow(debugWindow,gradientX);
	//-- Create a blurred and inverted image for weighting
	cv::Mat weight;
	GaussianBlur(eye_roi, weight, cv::Size(kWeightBlurSize, kWeightBlurSize), 0, 0);
	for (int y = 0; y < weight.rows; ++y) {
		unsigned char* row = weight.ptr<unsigned char>(y);
		for (int x = 0; x < weight.cols; ++x) {
			row[x] = (255 - row[x]);
		}
	}
	//imshow(debugWindow,weight);
	//-- Run the algorithm!
	cv::Mat outSum = cv::Mat::zeros(eye_roi.rows, eye_roi.cols, CV_64F);
	// for each possible gradient location
	// Note: these loops are reversed from the way the paper does them
	// it evaluates every possible center for each gradient location instead of
	// every possible gradient location for every center.
	printf("Eye Size: %ix%i\n", outSum.cols, outSum.rows);
	for (int y = 0; y < weight.rows; ++y) {
		const double* Xr = gradientX.ptr<double>(y), * Yr = gradientY.ptr<double>(y);
		for (int x = 0; x < weight.cols; ++x) {
			double gX = Xr[x], gY = Yr[x];
			if (gX == 0.0 && gY == 0.0) {
				continue;
			}
			test_possible_centers_formula(x, y, weight, gX, gY, outSum);
		}
	}
	// scale all the values down, basically averaging them
	double numGradients = static_cast<double>(weight.rows * weight.cols);
	cv::Mat out;
	outSum.convertTo(out, CV_32F, 1.0 / numGradients);
	//imshow(debugWindow,out);
	//-- Find the maximum point
	cv::Point maxP;
	double maxVal;
	cv::minMaxLoc(out, NULL, &maxVal, NULL, &maxP);
	//-- Flood fill the edges
	if (kEnablePostProcess) {
		cv::Mat floodClone;
		//double floodThresh = computeDynamicThreshold(out, 1.5);
		double floodThresh = maxVal * kPostProcessThreshold;
		cv::threshold(out, floodClone, floodThresh, 0.0f, cv::THRESH_TOZERO);
		if (kPlotVectorField) {
			//plotVecField(gradientX, gradientY, floodClone);
		}
		cv::Mat mask = flood_kill_edges(floodClone);
		//imshow(debugWindow + " Mask",mask);
		//imshow(debugWindow,out);
		// redo max
		cv::minMaxLoc(out, NULL, &maxVal, NULL, &maxP, mask);
	}
	return unscale_point(maxP, eye);
}

#pragma mark Postprocessing

bool floodShouldPushPoint(const cv::Point& np, const cv::Mat& mat) {
	return in_mat(np, mat.rows, mat.cols);
}

// returns a mask
cv::Mat flood_kill_edges(cv::Mat& mat) {
	rectangle(mat, cv::Rect(0, 0, mat.cols, mat.rows), 255);

	cv::Mat mask(mat.rows, mat.cols, CV_8U, 255);
	std::queue<cv::Point> toDo;
	toDo.push(cv::Point(0, 0));
	while (!toDo.empty()) {
		cv::Point p = toDo.front();
		toDo.pop();
		if (mat.at<float>(p) == 0.0f) {
			continue;
		}
		// add in every direction
		cv::Point np(p.x + 1, p.y); // right
		if (floodShouldPushPoint(np, mat)) toDo.push(np);
		np.x = p.x - 1; np.y = p.y; // left
		if (floodShouldPushPoint(np, mat)) toDo.push(np);
		np.x = p.x; np.y = p.y + 1; // down
		if (floodShouldPushPoint(np, mat)) toDo.push(np);
		np.x = p.x; np.y = p.y - 1; // up
		if (floodShouldPushPoint(np, mat)) toDo.push(np);
		// kill it
		mat.at<float>(p) = 0.0f;
		mask.at<uchar>(p) = 0;
	}
	return mask;
}


cv::Mat* leftCornerKernel;
cv::Mat* rightCornerKernel;

// not constant because stupid opencv type signatures
float kEyeCornerKernel[4][6] = {
  {-1,-1,-1, 1, 1, 1},
  {-1,-1,-1,-1, 1, 1},
  {-1,-1,-1,-1, 0, 3},
  { 1, 1, 1, 1, 1, 1},
};

void create_corner_kernels() {
	rightCornerKernel = new cv::Mat(4, 6, CV_32F, kEyeCornerKernel);
	leftCornerKernel = new cv::Mat(4, 6, CV_32F);
	// flip horizontally
	cv::flip(*rightCornerKernel, *leftCornerKernel, 1);
}

void release_corner_kernels() {
	delete leftCornerKernel;
	delete rightCornerKernel;
}

// TODO implement these
cv::Mat eyeCornerMap(const cv::Mat& region, bool left, bool left2) {
	cv::Mat cornerMap;

	cv::Size sizeRegion = region.size();
	cv::Range colRange(sizeRegion.width / 4, sizeRegion.width * 3 / 4);
	cv::Range rowRange(sizeRegion.height / 4, sizeRegion.height * 3 / 4);

	cv::Mat miRegion(region, rowRange, colRange);

	cv::filter2D(miRegion, cornerMap, CV_32F,
		(left && !left2) || (!left && !left2) ? *leftCornerKernel : *rightCornerKernel);

	return cornerMap;
}

cv::Point2f find_eye_corner(const cv::Mat& region, bool left, bool left2) {
	cv::Mat cornerMap = eyeCornerMap(region, left, left2);

	cv::Point maxP;
	cv::minMaxLoc(cornerMap, NULL, NULL, NULL, &maxP);

	cv::Point2f maxP2;
	maxP2 = find_subpixel_eye_corner(cornerMap, maxP);
	// GFTT
  //  std::vector<cv::Point2f> corners;
  //  cv::goodFeaturesToTrack(region, corners, 500, 0.005, 20);
  //  for (int i = 0; i < corners.size(); ++i) {
  //    cv::circle(region, corners[i], 2, 200);
  //  }
  //  imshow("Corners",region);

	return maxP2;
}
cv::Point2f find_subpixel_eye_corner(cv::Mat region, cv::Point maxP) {

	cv::Size sizeRegion = region.size();

	// Matrix dichotomy
	// Not useful, matrix becomes too small

	/*int offsetX = 0;
	if(maxP.x - sizeRegion.width / 4 <= 0) {
	  offsetX = 0;
	} else if(maxP.x + sizeRegion.width / 4 >= sizeRegion.width) {
	  offsetX = sizeRegion.width / 2 - 1;
	} else {
	  offsetX = maxP.x - sizeRegion.width / 4;
	}
	int offsetY = 0;
	if(maxP.y - sizeRegion.height / 4 <= 0) {
	  offsetY = 0;
	} else if(maxP.y + sizeRegion.height / 4 >= sizeRegion.height) {
	  offsetY = sizeRegion.height / 2 - 1;
	} else {
	  offsetY = maxP.y - sizeRegion.height / 4;
	}
	cv::Range colRange(offsetX, offsetX + sizeRegion.width / 2);
	cv::Range rowRange(offsetY, offsetY + sizeRegion.height / 2);

	cv::Mat miRegion(region, rowRange, colRange);


  if(left){
	  imshow("aa",miRegion);
	} else {
	  imshow("aaa",miRegion);
	}*/

	cv::Mat cornerMap(sizeRegion.height * 10, sizeRegion.width * 10, CV_32F);

	cv::resize(region, cornerMap, cornerMap.size(), 0, 0, cv::INTER_CUBIC);

	cv::Point maxP2;
	cv::minMaxLoc(cornerMap, NULL, NULL, NULL, &maxP2);

	return cv::Point2f(sizeRegion.width / 2 + maxP2.x / 10,
		sizeRegion.height / 2 + maxP2.y / 10);
}


bool rect_in_image(const cv::Rect& rect, const cv::Mat& image) {
	return rect.x > 0 && rect.y > 0 && rect.x + rect.width < image.cols&&
		rect.y + rect.height < image.rows;
}

bool in_mat(const cv::Point& p, const int rows, const int cols) {
	return p.x >= 0 && p.x < cols&& p.y >= 0 && p.y < rows;
}

cv::Mat matrix_magnitude(const cv::Mat& matX, const cv::Mat& matY) {
	cv::Mat mags(matX.rows, matX.cols, CV_64F);
	for (int y = 0; y < matX.rows; ++y) {
		const double* Xr = matX.ptr<double>(y), * Yr = matY.ptr<double>(y);
		double* Mr = mags.ptr<double>(y);
		for (int x = 0; x < matX.cols; ++x) {
			double gX = Xr[x], gY = Yr[x];
			double magnitude = sqrt((gX * gX) + (gY * gY));
			Mr[x] = magnitude;
		}
	}
	return mags;
}

double compute_dynamic_threshold(const cv::Mat& mat, double stdDevFactor) {
	cv::Scalar stdMagnGrad, meanMagnGrad;
	cv::meanStdDev(mat, meanMagnGrad, stdMagnGrad);
	double stdDev = stdMagnGrad[0] / sqrt(mat.rows * mat.cols);
	return stdDevFactor * stdDev + meanMagnGrad[0];
}
