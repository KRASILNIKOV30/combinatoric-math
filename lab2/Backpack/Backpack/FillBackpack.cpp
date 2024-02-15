#include <iostream>
#include "FillBackpack.h"

bool NextBinNumber(std::vector<int>& bin)
{
	int n = bin.size();
	int i = n - 1;
	while (true)
	{
		if (bin[i] != 1)
		{
			bin[i] = 1;
			i++;
			while (i < n)
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

std::vector<int> GetSubset(std::vector<int> const& bin)
{
	std::vector<int> subset = {};
	for (int i = 0; i < bin.size(); i++)
	{
		if (bin[i])
		{
			subset.push_back(i);
		}
	}

	return subset;
}

int GetSubsetSum(std::vector<int> const& bin, std::vector<int> values)
{
	int sum = 0;
	for (int i = 0; i < bin.size(); i++)
	{
		if (bin[i])
		{
			sum += values[i];
		}
	}

	return sum;
}

std::vector<int> FillBackpack(std::vector<int> weights, std::vector<int> values, int maxWeight)
{
	size_t n = weights.size();
	std::vector<int> set(n);
	std::vector<int> bin(n);
	int maxCost = 0;
	std::vector<int> bestCombination = {};

	for (int i = 0; i < set.size(); i++)
	{
		set[i] = i;
	}

	do
	{
		if (GetSubsetSum(bin, weights) > maxWeight)
		{
			continue;
		}

		int cost = GetSubsetSum(bin, values);
		if (cost > maxCost)
		{
			maxCost = cost;
			bestCombination = GetSubset(bin);
		}

	} while (NextBinNumber(bin));

	return bestCombination;
}