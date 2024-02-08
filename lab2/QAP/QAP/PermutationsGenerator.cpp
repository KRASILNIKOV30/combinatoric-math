#include "PermutationsGenerator.h"

PermutationsGenerator::PermutationsGenerator(int elementsAmount)
	: m_n(elementsAmount)
{
	InitVectors();
}

void PermutationsGenerator::InitVectors()
{
	m_curPerm.resize(m_n + 2);
	m_reversePerm.resize(m_n + 2);
	m_direction.resize(m_n + 2);
	for (int i = 1; i <= m_n; i++)
	{
		m_curPerm[i] = i;
		m_reversePerm[i] = i;
		m_direction[i] = -1;
	}
	m_curPerm[0] = m_n + 1;
	m_curPerm[m_n + 1] = m_n + 1;
	m_direction[0] = 0;
}

void PermutationsGenerator::GenerateNext()
{
	if (!IsNextAvailable())
	{
		return;
	}

	m_mobileNumber = m_n;

	while ((m_curPerm[m_reversePerm[m_mobileNumber] + m_direction[m_mobileNumber]] > m_mobileNumber) && (m_mobileNumber > 1))
	{
		m_direction[m_mobileNumber] *= -1;
		m_mobileNumber -= 1;
	}
	std::swap(m_curPerm[m_reversePerm[m_mobileNumber]], m_curPerm[m_reversePerm[m_mobileNumber] + m_direction[m_mobileNumber]]);
	std::swap(m_reversePerm[m_curPerm[m_reversePerm[m_mobileNumber]]], m_reversePerm[m_curPerm[m_reversePerm[m_mobileNumber] + m_direction[m_mobileNumber]]]);
}

std::vector<int> PermutationsGenerator::GetNext()
{
	std::vector<int> curPerm(m_curPerm.begin() + 1, m_curPerm.end() - 1);
	GenerateNext();
	return curPerm;
}

bool PermutationsGenerator::IsNextAvailable()
{
	return m_mobileNumber != 1;
}


