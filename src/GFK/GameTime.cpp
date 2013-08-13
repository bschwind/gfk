#include <GFK/GameTime.hpp>
#include <GFK/OSDetection.hpp>

#if defined(PLATFORM_WINDOWS)
	#include
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
		long freq;

		if (QueryPerformanceFrequency((LARGE_INTEGER*) &freq))
		{
			_glfw.win32.timer.hasPC = GL_TRUE;
			clockResolution = 1.0 / (double) freq;
			QueryPerformanceCounter((LARGE_INTEGER*) &_glfw.win32.timer.t0_64);
		}
		else
		{
			_glfw.win32.timer.hasPC = GL_FALSE;
			clockResolution = 0.001; // winmm resolution is 1 ms
			_glfw.win32.timer.t0_32 = _glfw_timeGetTime();
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
		long t_64;

		if (_glfw.win32.timer.hasPC)
		{
			QueryPerformanceCounter((LARGE_INTEGER*) &t_64);
			t = (double)(t_64 - _glfw.win32.timer.t0_64);
		}
		else
		{
			t = (double)(_glfw_timeGetTime() - _glfw.win32.timer.t0_32);
		}

		return t * clockResolution;
	#else
		return (double)(GetRawTime() - clockBase) * clockResolution;
	#endif
}

void GameTime::SetSystemTime(double time)
{
	#if defined(PLATFORM_WINDOWS)
		long t_64;

		if (_glfw.win32.timer.hasPC)
		{
			QueryPerformanceCounter((LARGE_INTEGER*) &t_64);
			_glfw.win32.timer.t0_64 = t_64 - (long) (t / clockResolution);
		}
		else
		{
			_glfw.win32.timer.t0_32 = _glfw_timeGetTime() - (int)(t * 1000.0);
		}
	#else
		clockBase = GetRawTime() - (long) (time / clockResolution);
	#endif
}

long GameTime::GetRawTime()
{
	#if defined(PLATFORM_WINDOWS)
		#include
	#elif defined(PLATFORM_MAC)
		return mach_absolute_time();
	#elif defined(PLATFORM_UNIX)
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return (long) tv.tv_sec * (long) 1000000 + (long) tv.tv_usec;
	#endif
}

}
