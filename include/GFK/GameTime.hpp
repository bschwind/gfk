#pragma once
#include <GFK/OSDetection.hpp>


namespace gfk
{

class GameTime
{
public:
	GameTime();
	~GameTime();
	static void InitClock();
	static double GetSystemTime();
	static void SetSystemTime(double time);
	double ElapsedGameTime;
	double TotalGameTime;
private:
	static long GetRawTime();
	static double clockResolution;
	static long clockBase;

	// Stupid Windows-specific timer variables
	#if defined(PLATFORM_WINDOWS)
		static bool hasPerformanceCounter;
		static unsigned int time32;
		static __int64 time64;
	#endif
};

}
