#include <GFK/System/GameTime.hpp>

#if defined(PLATFORM_WINDOWS)
	#include <Windows.h>
#elif defined(PLATFORM_MAC)
	#include <mach/mach_time.h>
#elif defined(PLATFORM_UNIX) || defined(PLATFORM_ANDROID)
	#include <sys/time.h>
	#include <time.h>
#endif

namespace gfk
{

double GameTime::clockResolution(0.0);
unsigned long long int GameTime::clockBase(0);

#if defined(PLATFORM_WINDOWS)
	bool GameTime::hasPerformanceCounter(false);
	unsigned int GameTime::time32(0);
	__int64 GameTime::time64(0);
#endif

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
	#elif defined(PLATFORM_UNIX) || defined(PLATFORM_ANDROID)
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
			time64 = t_64 - (unsigned long long int) (time / clockResolution);
		}
		else
		{
			//time32 = timeGetTime() - (int)(time * 1000.0);
		}
	#else
		clockBase = GetRawTime() - (unsigned long long int) (time / clockResolution);
	#endif
}

unsigned long long int GameTime::GetRawTime()
{
	#if defined(PLATFORM_WINDOWS)
		// This function is not used in the Windows time code, so return 0
		return 0.0;
	#elif defined(PLATFORM_MAC)
		return mach_absolute_time();
	#elif defined(PLATFORM_UNIX) || defined(PLATFORM_ANDROID)
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return (unsigned long long int) tv.tv_sec * (unsigned long long int) 1000000 + (unsigned long long int) tv.tv_usec;
	#endif
}

}
