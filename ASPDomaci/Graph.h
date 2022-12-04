#ifndef _graph_h_
#define _graph_h_

#include <string>

class Graph
{
public:
	~Graph();
	Graph();
	Graph(const std::string& path);
	Graph(const Graph&) = delete;

	void LoadFromFile(const std::string& path);
	void FreeMemory();
	inline bool IsLoaded() const { return m_N >= 0; }

	int AddVertex(const std::string& name);
	int RemoveVertex(const std::string& name);

	int AddEdge(const std::string& from, const std::string& to, float weight);
	int RemoveEdge(const std::string& from, const std::string& to);

	int FindKMostSimilar(const std::string& name, int k) const;
	int DijkstraShortestPath(const std::string& from, const std::string& to, bool print = true) const;
	int FindStronglyConnected(const std::string& name) const;
	
	friend std::ostream& operator<<(std::ostream& ostream, const Graph& rhs);

private:
	int GetVertexIndexByName(const std::string& name) const;
	int DijkstraShortestPath(int fromIndex, int toIndex, bool print = false) const;

	int m_N;
	float** m_Adjacency;
	std::string* m_Vertices;
};

#endif // _graph_h_