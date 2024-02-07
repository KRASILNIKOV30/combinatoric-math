#include <iostream>
#include <vector>
#define BOOST_TIMER_ENABLE_DEPRECATED
#include <boost/timer.hpp>

const int N = 20;

void WriteSubset(std::vector<int> set, std::vector<int> bin)
{
	std::cout << "{ ";
	for (int i = 0; i < N; i++)
	{
		if (bin[i])
		{

			std::cout << set[i] << " ";
		}
	}
	std::cout << "}";
}

bool NextBinNumber(std::vector<int>& bin)
{
	int i = N - 1;
	while (true)
	{
		if (bin[i] != 1)
		{
			bin[i] = 1;
			i++;
			while (i < N)
			{
				bin[i] = 0;
				i++;
			}
			return true;
		}
		else if (i != 0)
		{
			i--;
		}
		else
		{
			return false;
		}
	}
}

int main()
{
	boost::timer t;
	t.restart();

	std::vector<int> bin(N);
	std::vector<int> set(N);
	for (int i = 0; i < N; i++)
	{
		bin[i] = 0;
		set[i] = i + 1;
	};
	do
	{
		WriteSubset(set, bin);
		std::cout << std::endl;
	} while (NextBinNumber(bin));

	double duration = t.elapsed();
	std::cout << std::endl << duration << std::endl;
}

/*
	Time test

	N = 10: 0.005 s
	N = 20: 7.52 s
*/