#pragma once

#include <chrono>

#include "EStates.h"

using EState = EyeState;

struct Exercise
{
	EState expected;
	std::chrono::microseconds continues;
};

