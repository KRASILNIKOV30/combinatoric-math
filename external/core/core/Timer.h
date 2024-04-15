#pragma once

class TimerFixture
{
public:
	void StartTimer()
	{
		m_start = m_timer.now();
	}

	std::chrono::microseconds StopTimer()
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(m_timer.now() - m_start);
	}

private:
	std::chrono::high_resolution_clock m_timer;
	std::chrono::steady_clock::time_point m_start;
};