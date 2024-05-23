#pragma once
#include <vector>
#include <ostream>
#include <algorithm>
#include <functional>

using Matrix = std::vector<std::vector<int>>;

class Network
{
public:
	Network(Matrix const& matrix);
	void Init();
	Matrix GetFlow() const;
	std::vector<int> GetLevels() const;
	void Push(int u, int v);
	int GetOverflow(int vertex) const;
	void Relabel(int vertex);
	int GetMaxFlow();
	bool MaxFlowFound();
	int GetMaxLevelVertex();

private:
	void ForEachOutput(int vertex, std::function<bool(int vertex, int constraint, int flow)> callback);
	void ForEachInput(int vertex, std::function<void(int vertex, int constraint, int flow)> callback);
	void ForEachOverflowed(std::function<void(int vertex)> callback);
	std::vector<int> GetOverflowed();
	std::vector<int> GetOutputs(int vertex);
	void PushMaxLevelVertex();
	void RelabelMaxLevelVertex();

private:
	Matrix m_constraints;
	Matrix m_flow;
	std::vector<int> m_level;
};

inline bool operator==(std::vector<int> const& a, std::vector<int> const b)
{
	return std::ranges::equal(a, b);
}

inline bool operator==(Matrix const& a, Matrix const& b)
{
	return std::ranges::equal(a, b);
}
