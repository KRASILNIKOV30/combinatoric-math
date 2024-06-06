#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <set>

const int INF = std::numeric_limits<int>::max();
using Matrix = std::vector<std::vector<int>>;
using Match = std::map<int, int>;
using Subsets = std::pair<std::set<int>, std::set<int>>;

class Distributor
{
public:
	Distributor(Matrix const& matrix);
	void Init();
	Matrix GetMatrix() const;
	Match GetMinMatch();
	Subsets GetSubsets() const;

private:
	void ForEach(std::function<void(int x, int y, int& v)> callback);
	void ForEachRow(std::function<void(std::vector<int*> row)> callback);
	void ForEachColumn(std::function<void(std::vector<int*> column)> callback);
	void Minimize(std::vector<int*> const& v);
	Match TryGetMatch();
	int GetZeroIndex(std::vector<int> const& row, Match const& match);
	void BuiltChain(int start);
	void BuiltChainFromLeft(int start, Subsets subsets);
	void BuiltChainFromRight(int start, Subsets subsets);
	Match GetFlippedMatch(Match const& match);
	void Transform();
	

private:
	Matrix m_startMatrix;
	Matrix m_matrix;
	int m_size;
	Match m_match = {};
	Subsets m_subsets = { {}, {} };
};

inline bool operator==(std::vector<int> const& a, std::vector<int> const b)
{
	return std::ranges::equal(a, b);
}

inline bool operator==(Matrix const& a, Matrix const& b)
{
	return std::ranges::equal(a, b);
}

inline bool operator==(Match const& a, std::map<int, int> const& b)
{
	return std::ranges::equal(a, b);
}

inline bool operator==(Subsets const& a, Subsets const& b)
{
	return std::ranges::equal(a.first, b.first) && std::ranges::equal(a.second, b.second);
}

inline std::strong_ordering operator<=>(Subsets const& a, Subsets const& b)
{
	auto sizeA = a.first.size() + a.second.size();
	auto sizeB = b.first.size() + b.second.size();
	return sizeA <=> sizeB;
}

