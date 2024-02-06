// Music files

#pragma once

#include "HartPch.hpp"

#include "miniaudio.h"

namespace Hart {
	struct Music {
	public:
		Music(const std::string filePath);
		~Music();

	public:
		ma_decoder decoder;
	};
}