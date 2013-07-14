#include <GFK/Graphics/MonitorConfig.hpp>
#include <iostream>
#include <vector>

namespace gfk
{

std::vector<Monitor> MonitorConfig::monitors;

void MonitorConfig::SetupMonitor(int width, int height, std::string windowName, bool isFullScreen)
{
	Monitor monitor;
	monitor.Width = width;
	monitor.Height = height;
	monitor.WindowName = windowName;
	monitor.IsFullScreen = isFullScreen;
	monitors.push_back(monitor);
}

}
