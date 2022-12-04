#include <fstream>
#include <sstream>
#include <iostream>

#include "Graph.h"
#include "Utility.h"

Graph::~Graph()
{
	FreeMemory();
}

Graph::Graph()
	:
	m_N(-1),
	m_Adjacency(nullptr),
	m_Vertices(nullptr)
{
}

Graph::Graph(const std::string& path)
	:
	m_N(-1),
	m_Adjacency(nullptr),
	m_Vertices(nullptr)
	 
{
	LoadFromFile(path);
}

void Graph::LoadFromFile(const std::string& path)
{
	std::ifstream infile(path);
	if (infile.fail())
	{
		std::stringstream sstream;
		sstream << "Fajl na putanji \"" << path << "\" ne postoji!\n\n";
		PrintError(sstream.str());
	}

	int lineCounter = 0;
	int edgeCount = 0;

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		if (lineCounter == 0)
		{
			if (!(iss >> m_N))
			{
				PrintError("Fajl nije validan, nije pronadjen broj cvorova.\n\n");
				FreeMemory();
				return;
			}

			m_Adjacency = new float* [m_N];
			for (int i = 0; i < m_N; i++)
			{
				m_Adjacency[i] = new float[m_N];
				for (int j = 0; j < m_N; j++)
				{
					m_Adjacency[i][j] = -1;
				}
			}
		}
		else if (lineCounter == 1)
		{
			if (!(iss >> edgeCount))
			{
				PrintError("Fajl nije validan, nije pronadjen broj grana.\n\n");
				FreeMemory();
				return;
			}
		}
		else if (lineCounter == 2)
		{
			m_Vertices = new std::string[m_N];
			for (int i = 0; i < m_N; i++)
			{
				if (!(iss >> m_Vertices[i]))
				{
					PrintError("Fajl nije validan, nisu lepo ucitana imena cvorova.\n\n");
					FreeMemory();
					return;
				}
			}
		}
		else
		{
			std::string v1, v2;
			float weight;

			if (!(iss >> v1 >> v2 >> weight))
			{
				PrintError("Fajl nije validan, nisu lepo ucitane grane.\n\n");
				FreeMemory();
				return;
			}

			int v1Index = GetVertexIndexByName(v1);
			int v2Index = GetVertexIndexByName(v2);

			if (v1Index < 0 || v2Index < 0)
			{
				PrintError("Fajl nije validan, u granama zadati nepostojeci cvorovi.\n\n");
				FreeMemory();
				return;
			}

			m_Adjacency[v1Index][v2Index] = weight;
			edgeCount--;

			if (edgeCount < 0)
			{
				PrintError("Fajl nije validan, vise zadatih grana od navedenog broja grana.\n\n");
				FreeMemory();
				return;
			}
		}

		lineCounter++;
	}

	if (edgeCount > 0)
	{
		PrintError("Fajl nije validan, manje zadatih grana od navedenog broja grana.\n\n");
		FreeMemory();
		return;
	}
}

int Graph::AddVertex(const std::string& name)
{
	for (int i = 0; i < m_N; i++)
	{
		if (m_Vertices[i] == name)
			return -1;
	}

	float** newAdjacency = new float* [m_N + 1];
	for (int i = 0; i < m_N + 1; i++)
	{
		newAdjacency[i] = new float[m_N + 1];

		for (int j = 0; j < m_N + 1; j++)
		{
			if (i < m_N && j < m_N)
				newAdjacency[i][j] = m_Adjacency[i][j];
			else
				newAdjacency[i][j] = -1;
		}

		if(i < m_N)
			delete[] m_Adjacency[i];
	}

	delete[] m_Adjacency;
	m_Adjacency = newAdjacency;

	std::string* newVertices = new std::string[m_N + 1];
	for (int i = 0; i < m_N + 1; i++)
	{
		if (i < m_N)
			newVertices[i] = m_Vertices[i];
		else
			newVertices[i] = name;
	}

	delete[] m_Vertices;
	m_Vertices = newVertices;

	m_N++;
	return 0;
}

int Graph::RemoveVertex(const std::string& name)
{
	int removeIndex = GetVertexIndexByName(name);
	if (removeIndex < 0)
	{
		return -1;
	}

	if (m_N == 1)
	{
		FreeMemory();
		return 0;
	}

	float** newAdjacency = new float* [m_N - 1];
	for (int i = 0; i < m_N - 1; i++)
	{
		newAdjacency[i] = new float[m_N - 1];
		for (int j = 0; j < m_N - 1; j++)
		{
			int copyI = (i >= removeIndex ? i + 1 : i);
			int copyJ = (j >= removeIndex ? j + 1 : j);
			newAdjacency[i][j] = m_Adjacency[copyI][copyJ];
		}

		delete[] m_Adjacency[i];
	}

	delete[] m_Adjacency[m_N - 1];
	delete[] m_Adjacency;
	m_Adjacency = newAdjacency;

	std::string* newVertices = new std::string[m_N - 1];
	for (int i = 0; i < m_N - 1; i++)
	{
		int copyI = (i >= removeIndex ? i + 1 : i);
		newVertices[i] = m_Vertices[copyI];
	}

	delete[] m_Vertices;
	m_Vertices = newVertices;

	m_N--;
	return 0;
}

int Graph::AddEdge(const std::string& from, const std::string& to, float weight)
{
	if (weight < 0 || weight > 1)
	{
		return -1;
	}

	int fromIndex = GetVertexIndexByName(from);
	int toIndex = GetVertexIndexByName(to);

	if (fromIndex < 0 || toIndex < 0)
	{
		return -2;
	}

	if (m_Adjacency[fromIndex][toIndex] < 0)
	{
		m_Adjacency[fromIndex][toIndex] = weight;
		return 0;
	}
	else
	{
		m_Adjacency[fromIndex][toIndex] = weight;
		return 1;
	}
}

int Graph::RemoveEdge(const std::string& from, const std::string& to)
{
	int fromIndex = GetVertexIndexByName(from);
	int toIndex = GetVertexIndexByName(to);

	if (fromIndex < 0 || toIndex < 0)
	{
		return -1;
	}

	if (m_Adjacency[fromIndex][toIndex] < 0)
	{
		return -2;
	}
	else
	{
		m_Adjacency[fromIndex][toIndex] = -1;
		return 0;
	}
}

int Graph::GetVertexIndexByName(const std::string& name) const
{
	for (int i = 0; i < m_N; i++)
	{
		if (m_Vertices[i] == name)
			return i;
	}

	return -1;
}

void Graph::FreeMemory()
{
	for (int i = 0; i < m_N; i++)
	{
		delete[] m_Adjacency[i];
	}

	delete[] m_Adjacency;
	delete[] m_Vertices;

	m_N = -1;
}

std::ostream& operator<<(std::ostream& ostream, const Graph& rhs)
{
	if (rhs.m_N == 0)
	{
		Print("Graf je prazan.\n", ORANGE_TXT, ostream);
		return ostream;
	}

	std::stringstream sstream;

	sstream << "CVOROVI[" << rhs.m_N << "]:\n";
	Print(sstream.str(), ORANGE_TXT, ostream);
	for (int i = 0; i < rhs.m_N; i++)
	{
		sstream.str(std::string());
		sstream << "\t" << rhs.m_Vertices[i] << "\n";
		Print(sstream.str(), LIGHT_ORANGE_TXT, ostream);
	}

	Print("GRANE:\n", ORANGE_TXT, ostream);
	for (int i = 0; i < rhs.m_N; i++)
	{
		for (int j = 0; j < rhs.m_N; j++)
		{
			float weight = rhs.m_Adjacency[i][j];
			if (weight >= 0)
			{
				sstream.str(std::string());
				sstream << "\t" <<  rhs.m_Vertices[i] << "-(" << weight << ")->" << rhs.m_Vertices[j] << "\n";
				Print(sstream.str(), LIGHT_ORANGE_TXT, ostream);
			}
		}
	}

	return ostream;
}