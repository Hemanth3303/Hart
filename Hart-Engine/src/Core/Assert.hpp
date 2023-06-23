/*
* Custom assert macros, stripped in distribution builds
*/

#pragma once

#ifdef HART_DEBUG

#include <cassert>

	#define HART_ASSERT(expression, ...) assert(expression)
	#define HART_ASSERT_EQUAL(expression, value) assert(expression == value)
	#define HART_ASSERT_NOT_EQUAL(expression, value) assert(expression != value)

#else

	#define HART_ASSERT(expression) 
	#define HART_ASSERT_EQUAL(expression, value) 
	#define HART_ASSERT_NOT_EQUAL(expression, value) 

#endif // HART_DEBUG