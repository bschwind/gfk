#include <GFK/GameTime.hpp>

#if defined(PLATFORM_WINDOWS)
	#include <Windows.h>
#elif defined(PLATFORM_MAC)
	#include <mach/mach_time.h>
#elif defined(PLATFORM_UNIX)
	#include <sys/time.h>
	#include <time.h>
#endif

namespace gfk
{

double GameTime::clockResolution(0.0);
long GameTime::clockBase(0);

bool GameTime::hasPerformanceCounter(false);
unsigned int GameTime::time32(0);
__int64 GameTime::time64(0);

GameTime::GameTime() :
ElapsedGameTime(0),
TotalGameTime(0)
{

}

GameTime::~GameTime()
{

}

void GameTime::InitClock()
{
	#if defined(PLATFORM_WINDOWS)
		__int64 freq;

		if (QueryPerformanceFrequency((LARGE_INTEGER*) &freq))
		{
			hasPerformanceCounter = true;
			clockResolution = 1.0 / (double) freq;
			QueryPerformanceCounter((LARGE_INTEGER*) &time64);
		}
		else
		{
			hasPerformanceCounter = false;
			clockResolution = 0.001; // winmm resolution is 1 ms
			//time32 = timeGetTime();
		}
	#elif defined(PLATFORM_MAC)
		mach_timebase_info_data_t info;
		mach_timebase_info(&info);

		clockResolution = (double) info.numer / (info.denom * 1.0e9);
		clockBase = GetRawTime();
	#elif defined(PLATFORM_UNIX)
		clockResolution = 1.0e-6;
		clockBase = GetRawTime();
	#endif
}

double GameTime::GetSystemTime()
{
	#if defined(PLATFORM_WINDOWS)
		double t;
		__int64 t_64;

		if (hasPerformanceCounter)
		{
			QueryPerformanceCounter((LARGE_INTEGER*) &t_64);
			t = (double)(t_64 - time64);
		}
		else
		{
			//t = (double)(timeGetTime() - time32);
		}

		return t * clockResolution;
	#else
		return (double)(GetRawTime() - clockBase) * clockResolution;
	#endif
}

void GameTime::SetSystemTime(double time)
{
	#if defined(PLATFORM_WINDOWS)
		__int64 t_64;

		if (hasPerformanceCounter)
		{
			QueryPerformanceCounter((LARGE_INTEGER*) &t_64);
			time64 = t_64 - (long) (time / clockResolution);
		}
		else
		{
			//time32 = timeGetTime() - (int)(time * 1000.0);
		}
	#else
		clockBase = GetRawTime() - (long) (time / clockResolution);
	#endif
}

long GameTime::GetRawTime()
{
	#if defined(PLATFORM_WINDOWS)
		// This function is not used in the Windows time code, so return 0
		return 0.0;
	#elif defined(PLATFORM_MAC)
		return mach_absolute_time();
	#elif defined(PLATFORM_UNIX)
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return (long) tv.tv_sec * (long) 1000000 + (long) tv.tv_usec;
	#endif
}

}
