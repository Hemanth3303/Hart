#pragma once

// from the C++ standard library
#include <iostream>
#include <string>
#include <string_view>
#include <memory>
#include <array>
#include <vector>
#include <initializer_list>
#include <deque>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <chrono>
#include <iomanip>
#include <random>
#include <numbers>
#include <numeric>
#include <limits>

// from the C standard library
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>

// platform specific
#if defined(HART_ENGINE_PLATFORM_WINDOWS)
	#include <windows.h>
	#include <intrin.h>
#elif defined(HART_ENGINE_PLATFORM_LINUX)
	#include <unistd.h>
	#include <signal.h>
#endif

// from engine
#include "Core/Base.hpp"
#include "Core/Assert.hpp"
#include "Utils/FileManager.hpp"
#include "Utils/Logger.hpp"
#include "Utils/Random.hpp"
#include "Utils/Timer.hpp"
