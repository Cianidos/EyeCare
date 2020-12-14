#pragma once
#include "ImageDataCollector.h"
#include "EStates.h"



class DataAnalyzer
{

public:
	ImageDataCollector& idc_;
	DataAnalyzer(ImageDataCollector& idc);

	std::vector<EyeSide> side_eyes_looks() const;
	std::pair<bool, bool> eyes_opened() const;
	std::tuple<int, int, int> get_head_angle() const;
	EyeState get_eyes_state() const;
};
