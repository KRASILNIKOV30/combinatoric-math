#include <unordered_set>

struct Vertex
{
	Vertex(int n)
		: number(n)
	{}

	int number;
	std::unordered_set<Vertex*> edges = {};
	bool contact = false;
	bool visited = false;
};