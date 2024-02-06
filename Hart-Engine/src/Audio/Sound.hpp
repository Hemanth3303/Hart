// SFX files

#pragma once

#include "HartPch.hpp"

#include "miniaudio.h"

namespace Hart {
	struct Sound {
	public:
		Sound(const std::string filePath);
		~Sound();

	public:
		ma_decoder decoder;
	};
}