#pragma once
#define BOOST_TIMER_ENABLE_DEPRECATED
#include <boost/timer.hpp>

class TimerFixture
{
public:
	void StartTimer()
	{
		m_timer.restart();
	}

	double StopTimer()
	{
		return m_timer.elapsed();
	}

private:
	boost::timer m_timer;
};