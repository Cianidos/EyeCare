// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "DataAnalyzer.h"

DataAnalyzer::DataAnalyzer(ImageDataCollector& idc)
	: idc_(idc)
{}

std::vector<EyeSide> DataAnalyzer::side_eyes_looks() const
{
	std::vector<EyeSide> res;
	const cv::Point
		l_center(
			idc_.l_eye_region_.x + idc_.l_eye_region_.width / 2,
			idc_.l_eye_region_.y + idc_.l_eye_region_.height / 2),
		r_center(
			idc_.r_eye_region_.x + idc_.r_eye_region_.width / 2,
			idc_.r_eye_region_.y + idc_.r_eye_region_.height / 2);

	const cv::Size offset(idc_.r_eye_region_.size() / 20);
	
	if ((idc_.l_pupil_.x < (l_center.x - offset.width)) && (idc_.r_pupil_.x < (r_center.x - offset.width)))
	{
		res.push_back(EyeSide::left);
	}
	else if ((idc_.l_pupil_.x > (l_center.x + offset.width)) && (idc_.r_pupil_.x > (r_center.x + offset.width)))
	{
		res.push_back(EyeSide::right);
	}
	else
	{
		res.push_back(EyeSide::vcenter);
	}

	if ((idc_.l_pupil_.y < (l_center.y - offset.height)) && (idc_.r_pupil_.y < (r_center.y - offset.height)))
	{
		res.push_back(EyeSide::up);
	}
	else if ((idc_.l_pupil_.y > (l_center.y + offset.height)) && (idc_.r_pupil_.y > (r_center.y + offset.height)))
	{
		res.push_back(EyeSide::down);
	}
	else
	{
		res.push_back(EyeSide::hcenter);
	}
	return res;
}

std::pair<bool, bool> DataAnalyzer::eyes_opened() const
{
	bool l = idc_.l_pupil_.y > (idc_.l_eye_region_.y + idc_.l_eye_region_.height / 10);
	bool r = idc_.r_pupil_.y > (idc_.r_eye_region_.y + idc_.r_eye_region_.height / 10);
	return { l, r };
}

std::tuple<int, int, int> DataAnalyzer::get_head_angle() const
{
	return { 0,0,0 };
}


// TODO: repair state recognition 
EyeState DataAnalyzer::get_eyes_state() const
{
	auto [l, r] = eyes_opened();
	auto res = (l && r) ? 
		           static_cast<int>(EyeState::opened)
		           : static_cast<int>(EyeState::closed);
	
	// TODO: exclude side_eyes_looks() method
	for (auto i : side_eyes_looks())
	{
		res += static_cast<int>(res);
	}
	return static_cast<EyeState>(res);
}
