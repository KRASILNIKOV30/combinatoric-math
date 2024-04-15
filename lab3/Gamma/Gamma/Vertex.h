#pragma once
#include <map>
#include <Segment.h>

class Vertex;

using Edges = std::map<int, Vertex*>;

class Vertex
{
public:
	Vertex(int n)
		: m_number(n)
	{}

	int GetNumber() const;
	bool IsContact() const;
	bool IsVisited() const;
	void AddSibling(Vertex* v);
	bool HasNext() const;
	Vertex* Next();
	void SetVisited(bool visited = true);
	void SetContact();
	Edges GetEdges();
	bool WillDelete();
	void DeleteEdges();
	void DeleteLink(int vertex);
	~Vertex();

private:
	int m_number;
	Edges m_edges = {};
	bool m_contact = false;
	bool m_visited = false;
	int m_next = 0;
};