#include "Network.h"
#include <numeric>
#include <iterator>
#include <iostream>

Network::Network(Matrix const& matrix)
	: m_constraints(matrix)
{
	Init();
}

void Network::Init()
{
	const int size = static_cast<int>(m_constraints.size());
	m_level = std::vector<int>(size, 0);
	m_flow = std::vector<std::vector<int>>(size, m_level);

	ForEachOutput(0, [&](int v, int c, int) {
		m_flow[0][v] = c;
		m_flow[v][0] = -c;
		return false;
	});

	m_level[0] = size;
}

Matrix Network::GetFlow() const
{
	return m_flow;
}

std::vector<int> Network::GetLevels() const
{
	return m_level;
}

int Network::GetResidualCapacity(int u, int v)
{
	return std::min(GetOverflow(u), m_constraints[u][v] - m_flow[u][v]);
}

void Network::Push(int u, int v)
{
	const int diff = GetResidualCapacity(u, v);
	m_flow[u][v] += diff;
	m_flow[v][u] = -m_flow[u][v];
}

int Network::GetOverflow(int vertex) const
{
	return std::reduce(m_flow[vertex].begin(), m_flow[vertex].end(), 0, std::minus<int>());
}

void Network::Relabel(int vertex)
{
	std::vector<int> levels;
	ForEachOutput(vertex, [&](int v, int c, int f) {
		if (f < c)
		{
			levels.push_back(m_level[v]);
		}
		return false;
	});
	m_level[vertex] = std::ranges::min(levels) + 1;
}

bool Network::MaxFlowFound()
{
	return GetOverflowed().size() == 0;
}

int Network::GetMaxLevelVertex()
{
	return std::ranges::max(GetOverflowed(), [&](int a, int b) { return m_level[a] < m_level[b]; });
}

int Network::GetMaxFlow()
{
	while (!MaxFlowFound())
	{
		PushMaxLevelVertex();

		if (MaxFlowFound())
		{
			break;
		}

		RelabelMaxLevelVertex();
	}

	return static_cast<int>(GetOverflow(m_constraints.size() - 1));
}

void Network::PushMaxLevelVertex()
{
	const int u = GetMaxLevelVertex();
	ForEachOutput(u, [&](int v, int c, int f) {
		if (c - f > 0 && m_level[u] == m_level[v] + 1)
		{
			Push(u, v);
			return true;
		}
		return false;
	});
}

void Network::RelabelMaxLevelVertex()
{
	const int u = GetMaxLevelVertex();
	if (std::ranges::all_of(GetOutputs(u), [&](int v) { return m_level[u] <= m_level[v]; }))
	{
		Relabel(u);
	}
}

void Network::ForEachOutput(int vertex, std::function<bool(int vertex, int constraint, int flow)> callback)
{
	for (int i = 0; i < m_constraints.size(); ++i)
	{
		int c = m_constraints[vertex][i];
		int f = m_flow[vertex][i];
		if (c != 0 || f != 0)
		{
			if (callback(i, c, f))
			{
				break;
			}
		}
	}
}

void Network::ForEachInput(int vertex, std::function<void(int vertex, int constraint, int flow)> callback)
{
	for (int i = 0; i < m_constraints.size(); ++i)
	{
		int c = m_constraints[i][vertex];
		int f = m_flow[i][vertex];
		if (c != 0)
		{
			callback(i, c, f);
		}
	}
}

void Network::ForEachOverflowed(std::function<void(int vertex)> callback)
{
	for (int i = 1; i < m_constraints.size() - 1; ++i)
	{
		if (GetOverflow(i) > 0)
		{
			callback(i);
		}
	}
}

std::vector<int> Network::GetOverflowed()
{
	std::vector<int> overflowed;
	ForEachOverflowed([&](int v) { overflowed.push_back(v); });
	return overflowed;
}

std::vector<int> Network::GetOutputs(int vertex)
{
	std::vector<int> outputs;
	ForEachOutput(vertex, [&](int v, int c, int f) { 
		if (GetResidualCapacity(vertex, v))
		{
			outputs.push_back(v);
		}
		return false;
	});
	return outputs;
}
