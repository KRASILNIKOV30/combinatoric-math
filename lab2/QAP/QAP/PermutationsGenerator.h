#pragma once
#include <vector>

class PermutationsGenerator
{
public:
	PermutationsGenerator(int elementsAmount);
	std::vector<int> GetNext();
	bool IsNextAvailable();

private:
	void InitVectors();
	void GenerateNext();

private:
	int m_n;
	int m_mobileNumber;
	std::vector<int> m_curPerm;
	std::vector<int> m_reversePerm;
	std::vector<int> m_direction;
};

