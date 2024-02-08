#pragma once
#include "GetMinAssignment.h"
#include "PermutationsGenerator.h"

int CalculateCost(Matrix const& facilities, Matrix const& locations, std::vector<int> const& assignment) {
	int cost = 0;
	int n = static_cast<int>(facilities.size());

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int facility1 = assignment[i] - 1;
			int facility2 = assignment[j] - 1;
			int location1 = i;
			int location2 = j;

			cost += facilities[facility1][facility2] * locations[location1][location2];
		}
	}

	return cost;
}

std::vector<int> GetMinAssigment(Matrix const& facilities, Matrix const& locations)
{
	int n = static_cast<int>(facilities.size());
	PermutationsGenerator generator(n);
	std::vector<int> assignment = generator.GetNext();
	std::vector<int> minAssignment = assignment;
	int minCost = CalculateCost(facilities, locations, assignment);

	while (generator.IsNextAvailable())
	{
		assignment = generator.GetNext();
		int cost = CalculateCost(facilities, locations, assignment);
		if (cost < minCost)
		{
			minCost = cost;
			minAssignment = assignment;
		}
	}

	return minAssignment;
}