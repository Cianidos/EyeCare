#pragma once
#include <string>


enum class EyeSide
{
	left = 1,
	right = 2,
	vcenter = 3,
	up = 4,
	down = 8,
	hcenter = 12,
};

enum class EyeState
{
	closed = 0,
	opened = 16,
	left = opened | 1,
	right = opened | 2,
	vcenter = opened | 3,
	up = opened | 4,
	lu = left | up,
	ru = right | up,
	down = opened | 8,
	ld = left | down,
	rd = right | down,
	hcenter = opened | 12,
};

inline std::string to_string(EyeState es)
{
	switch (es)
	{
	case EyeState::closed:
		return "closed";
	case EyeState::opened:
		return "opened";
	case EyeState::left:
		return "left";
	case EyeState::right:
		return "right";
	case EyeState::vcenter: 
		return "vcenter";
	case EyeState::up: 
		return "up";
	case EyeState::lu: 
		return "lu";
	case EyeState::ru: 
		return "ru";
	case EyeState::down: 
		return "down";
	case EyeState::ld: 
		return "ld";
	case EyeState::rd: 
		return "rd";
	case EyeState::hcenter:
		return "hcenter";
	default: 
		return "I DON'T KNOW";
	}
}
