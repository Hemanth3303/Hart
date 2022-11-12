#pragma once

//from the standard library
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <ctime>


//windows specific
#if defined(HART_WINDOWS)
#include <Windows.h>
#elif defined(HART_LINUX)

#endif // Platform check


//from engine
#include "Core/Assert.hpp"