#pragma once

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
};
}
