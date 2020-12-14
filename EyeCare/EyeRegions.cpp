// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "EyeRegions.h"
#include "CVlegacy.h"

std::optional<std::tuple<cv::Rect, cv::Rect>>
EyeRegions::detect(const cv::Mat& frame)
{
	const auto face_region = cv::Rect(0, 0, frame.cols, frame.rows);
	auto [left, right] = find_eyes(frame, face_region);
	return { { left, right } };
}

std::optional<std::tuple<cv::Rect, cv::Rect>>
EyeRegions::detect(const cv::Mat& frame, const cv::Rect& face_region)
{
	auto [left, right] = detect(frame(face_region)).value();
	for (auto& r : std::vector({std::ref(left), std::ref(right)}))
	{
		r.get().x += face_region.x;
		r.get().y += face_region.y;
	}
	return { {left, right} };
}

