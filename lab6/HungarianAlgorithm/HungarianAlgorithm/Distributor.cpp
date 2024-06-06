#include "Distributor.h"
#include <numeric>
#include <iostream>
#include <stdexcept>
#include <iterator>

Distributor::Distributor(Matrix const& matrix)
	: m_matrix(matrix)
	, m_startMatrix(matrix)
	, m_size(static_cast<int>(matrix.size()))
{
	Init();
}

void Distributor::Init()
{
	ForEach([](int, int, int& v) {
		if (v == 0)
		{
			v = INF;
		}
	});

	ForEachRow([&](std::vector<int*> row) { Minimize(row); });
	ForEachColumn([&](std::vector<int*> col) { Minimize(col); });
}

Matrix Distributor::GetMatrix() const
{
	return m_matrix;
}

std::map<int, int> Distributor::GetMinMatch()
{
	m_match = TryGetMatch();
	if (m_match.size() == m_size)
	{
		return m_match;
	}
	for (int i = 0; i < m_size; ++i)
	{
		if (!m_match.contains(i))
		{
			BuiltChain(i);

			std::erase_if(m_match, [&](auto& p) {
				return m_subsets.second.contains(p.second);
			});

			Transform();

			m_match.insert({ i, GetZeroIndex(m_matrix[i], GetFlippedMatch(m_match))});
			
			for (int x = 0; x < m_size; ++x)
			{
				if (!m_match.contains(x))
				{
					m_match.insert({ x, GetZeroIndex(m_matrix[x], GetFlippedMatch(m_match)) });
				}
			}
		}
	}
	
	return m_match;
}

Subsets Distributor::GetSubsets() const
{
	return m_subsets;
}

void Distributor::ForEach(std::function<void(int x, int y, int& v)> callback)
{
	for (int x = 0; x < m_size; ++x)
	{
		for (int y = 0; y < m_size; ++y)
		{
			callback(x, y, m_matrix[x][y]);
		}
	}
}

void Distributor::ForEachRow(std::function<void(std::vector<int*> row)> callback)
{
	for (int i = 0; i < m_size; ++i)
	{
		std::vector<int*> column;
		for (int j = 0; j < m_size; ++j)
		{
			column.push_back(&m_matrix[i][j]);
		}
		callback(column);
	}
}

void Distributor::ForEachColumn(std::function<void(std::vector<int*> column)> callback)
{
	const int size = static_cast<int>(m_matrix.size());
	for (int i = 0; i < size; ++i)
	{
		std::vector<int*> column;
		for (int j = 0; j < size; ++j)
		{
			column.push_back(&m_matrix[j][i]);
		}
		callback(column);
	}
}

void Distributor::Minimize(std::vector<int*> const& v)
{
	int min = *std::ranges::min(v, [](const int* a, const int* b) { return *a < *b; });
	for (auto& el : v)
	{
		if (*el != INF)
		{
			*el -= min;
		}
	}
}

int Distributor::GetZeroIndex(std::vector<int> const& row, Match const& match)
{
	int i;
	for (i = 0; i < m_size; ++i)
	{
		if (row[i] == 0 && !match.contains(i))
		{
			break;
		}
	}
	return i;
}

void Distributor::BuiltChain(int start)
{
	for (int i = 0; i < m_size && m_subsets == Subsets{ {}, {} }; ++i)
	{
		Subsets subsets{};
		BuiltChainFromLeft(start, subsets);
	}
}

void Distributor::BuiltChainFromLeft(int start, Subsets subsets)
{
	if (!subsets.first.insert(start).second)
	{
		return;
	}

	for (int i = 0; i < m_size; ++i)
	{
		if (m_matrix[start][i] != INF)
		{
			BuiltChainFromRight(i, subsets);
		}
	}
}

void Distributor::BuiltChainFromRight(int start, Subsets subsets)
{
	if (subsets.second.contains(start))
	{
		return;
	}
	auto flipped = GetFlippedMatch(m_match);
	if (!flipped.contains(start))
	{
		if (subsets > m_subsets)
		{
			m_subsets = subsets;
		}
		return;
	}
	int left = flipped.at(start);
	subsets.second.insert(start);
	BuiltChainFromLeft(left, subsets);
}

Match Distributor::GetFlippedMatch(Match const& match)
{
	Match flipped;
	for (auto& [k, v] : match)
	{
		flipped.insert({ v, k });
	}
	return flipped;
}

void Distributor::Transform()
{
	std::vector<int> ds;
	for (auto& x : m_subsets.first)
	{
		for (int y = 0; y < m_size; ++y)
		{
			if (!m_subsets.second.contains(y))
			{
				ds.push_back(m_matrix[x][y]);
			}
		}
	}
	if (ds.empty())
	{
		throw std::runtime_error("full match does not exist");
	}
	const int d = std::ranges::min(ds);
	ForEach([&](int x, int y, int& v) {
		if (m_subsets.first.contains(x))
		{
			if (v != INF)
			{
				v -= d;
			}
		}
		if (m_subsets.second.contains(y))
		{
			if (v != INF)
			{
				v += d;
			}
		}
	});
}

Match Distributor::TryGetMatch()
{
	Match match;
	for (int i = 0; i < m_size; ++i)
	{
		auto& row = m_matrix[i];
		int zeroIndex = GetZeroIndex(row, match);
		if (zeroIndex == m_size)
		{
			break;
		}
		match.insert({ zeroIndex, i });
	}

	return GetFlippedMatch(match);
}
