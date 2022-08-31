#pragma once

#include "HartPch.hpp"

#if defined(HART_DEBUG)
#include <cassert>

	#define HART_ASSERT(cond) assert(cond)
	#define HART_ASSERT_EQUALS(cond, val) assert(cond == val)
	#define HART_ASSERT_NOT_EQUALS(cond, val) assert(cond != val)

#else

	#define HART_ASSERT(cond) 
	#define HART_ASSERT_EQUALS(cond, val) 
	#define HART_ASSERT_NOT_EQUALS(cond, val) 

#endif //HART_DEBUG