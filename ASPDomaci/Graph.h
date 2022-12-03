#ifndef _graph_h_
#define _graph_h_

#include <string>

class Graph
{
public:
	~Graph();
	Graph(const std::string& path);

	bool IsLoaded() const { return m_N > 0; }
	
	friend std::ostream& operator<<(std::ostream& ostream, const Graph& rhs);

private:
	int GetVertexIndexByName(const std::string& name) const;

	void FreeMemory();

	int m_N;
	float** m_Adjacency;
	std::string* m_Vertices;
};

#endif // _graph_h_