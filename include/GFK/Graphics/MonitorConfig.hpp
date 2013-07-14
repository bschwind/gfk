#pragma once

#include <string>
#include <vector>

namespace gfk
{

struct Monitor
{
	int Width;
	int Height;
	std::string WindowName;
	bool IsFullScreen;
};

class MonitorConfig
{
public:
	typedef std::vector<Monitor>::const_iterator const_iterator;
	static const_iterator begin() { return monitors.begin(); }
	static const_iterator end() { return monitors.end(); }
	static int GetMonitorCount() {return monitors.size(); }
	static void SetupMonitor(int width, int height, std::string windowName, bool isFullScreen);
protected:
private:
	static std::vector<Monitor> monitors;
};

}