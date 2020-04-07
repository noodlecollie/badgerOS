#pragma once

namespace CoreUtil
{
	void assertFunc(bool condition, const char* conditionStr, const char* desc, const char* file, int line);
}

#define BGRS_ASSERT(cond, desc) ::CoreUtil::assertFunc(cond, #cond, desc, __FILE__, __LINE__)

#ifdef DEBUG
#define BGRS_ASSERTD(cond, desc) BGRS_ASSERT(cond, desc)
#else
#define BGRS_ASSERTD(...)
#endif
