#include <iostream>
#include <sstream>

#include "Graph.h"
#include "Utility.h"

Graph graph;

bool GraphLoadedCheck()
{
	if (!graph.IsLoaded())
	{
		PrintError("Graf je obrisan ili nije ucitan!\n\n");
		return false;
	}

	return true;
}

void LoadGraphFromFile()
{
	PrintMenuHeader("\nUCITAVANJE GRAFA IZ FAJLA\n");
	std::cout
		<< "Unesite putanju fajla: ";

	std::string input;
	std::cin >> input;

	graph.LoadFromFile(input);

	if (!graph.IsLoaded())
	{
		return;
	}

	PrintSuccess("Graf uspesno ucitan!\n\n");
}

void AddVertexToGraph()
{
	PrintMenuHeader("\nDODAVANJE CVORA U GRAF\n");

	if (!GraphLoadedCheck())
		return;

	std::cout
		<< "Unesite ime novog cvora: ";

	std::string input;
	std::cin >> input;

	int operationResult = graph.AddVertex(input);

	std::stringstream sstream;
	if (operationResult == 0)
	{
		sstream << "Cvor \"" << input << "\" uspesno dodat u graf!\n\n";
		PrintSuccess(sstream.str());
	}
	else if(operationResult == -1)
	{
		sstream << "Cvor \"" << input << "\" vec postoji u grafu!\n\n";
		PrintError(sstream.str());
	}
}

void RemoveVertexFromGraph()
{
	PrintMenuHeader("\nBRISANJE CVORA IZ GRAFA\n");

	if (!GraphLoadedCheck())
		return;

	std::cout
		<< "Unesite ime cvora koji zelite da obrisete: ";

	std::string input;
	std::cin >> input;

	int operationResult = graph.RemoveVertex(input);

	std::stringstream sstream;
	if (operationResult == 0)
	{
		sstream << "Cvor \"" << input << "\" uspesno obrisan iz grafa!\n\n";
		PrintSuccess(sstream.str());
	}
	else if(operationResult == -1)
	{
		sstream << "Cvor \"" << input << "\" ne postoji u grafu!\n\n";
		PrintError(sstream.str());
	}
}

void AddEdgeToGraph()
{
	PrintMenuHeader("\nDODAVANJE GRANE U GRAF\n");

	if (!GraphLoadedCheck())
		return;

	std::cout
		<< "Unesite ime prvog cvora: ";
	std::string inputFrom;
	std::cin >> inputFrom;

	std::cout
		<< "Unesite ime drugog cvora: ";
	std::string inputTo;
	std::cin >> inputTo;

	std::cout
		<< "Unesite tezinu grane: ";
	float inputWeight;
	std::cin >> inputWeight;
	if (std::cin.fail())
	{
		PrintError("Unos tezine mora biti realan broj u opsegu od 0 do 1!\n\n");
		std::cin.clear();
		std::cin.ignore(256, '\n');
		return;
	}

	int operationResult = graph.AddEdge(inputFrom, inputTo, inputWeight);

	std::stringstream sstream;
	if (operationResult == -1)
	{
		PrintError("Unos tezine mora biti realan broj u opsegu od 0 do 1!\n\n");
	}
	else if (operationResult == -2)
	{
		sstream << "Neki od unetih cvorova (\"" << inputFrom << "\" i " << "\"" << inputTo << "\") ne postoji u grafu!\n\n";
		PrintError(sstream.str());
	}
	else if(operationResult == 0)
	{
		PrintSuccess("Grana uspesno dodata!\n\n");
	}
	else if (operationResult == 1)
	{
		PrintSuccess("Grana vec postoji u grafu, tezina uspesno azurirana!\n\n");
	}
}

void RemoveEdgeFromGraph()
{
	PrintMenuHeader("\nBRISANJE GRANE IZ GRAFA\n");

	if (!GraphLoadedCheck())
		return;

	std::cout
		<< "Unesite ime prvog cvora: ";
	std::string inputFrom;
	std::cin >> inputFrom;

	std::cout
		<< "Unesite ime drugog cvora: ";
	std::string inputTo;
	std::cin >> inputTo;

	int operationResult = graph.RemoveEdge(inputFrom, inputTo);

	std::stringstream sstream;
	if (operationResult == -1)
	{
		sstream << "Neki od unetih cvorova (\"" << inputFrom << "\" i " << "\"" << inputTo << "\") ne postoji u grafu!\n\n";
		PrintError(sstream.str());
	}
	else if (operationResult == -2)
	{
		PrintError("Ne postoji uneta grana!\n\n");
	}
	else if (operationResult == 0)
	{
		PrintSuccess("Grana uspesno obrisana!\n\n");
	}
}

void PrintGraph()
{
	PrintMenuHeader("\nISPIS GRAFA\n");

	if (!GraphLoadedCheck())
		return;

	std::cout << graph;
	PrintSuccess("Graf uspesno ispisan!\n\n");
}

void DeleteGraph()
{
	PrintMenuHeader("\nBRISANJE GRAFA\n");
	graph.FreeMemory();
	PrintSuccess("Graf uspesno obrisan!\n\n");
}

void FindKMostSimilar()
{
	PrintMenuHeader("\nNALAZENJE K NAJSLICNIJIH CVOROVA\n");

	if (!GraphLoadedCheck())
		return;

	std::cout
		<< "Unesite ime cvora: ";
	std::string inputVertex;
	std::cin >> inputVertex;

	std::cout
		<< "Unesite K: ";
	int inputK;
	std::cin >> inputK;
	if (std::cin.fail())
	{
		PrintError("Unos K mora biti nenegativan ceo broj!\n\n");
		std::cin.clear();
		std::cin.ignore(256, '\n');
		return;
	}

	int operationResult = graph.FindKMostSimilar(inputVertex, inputK);

	std::stringstream sstream;
	if (operationResult == -1)
	{
		PrintError("Unos K mora biti nenegativan ceo broj!\n\n");
	}
	else if (operationResult == -2)
	{
		sstream << "Cvor \"" << inputVertex << "\" ne postoji u grafu!\n\n";
		PrintError(sstream.str());
	}
	else if (operationResult == 0)
	{
		PrintSuccess("Operacija uspesna!\n\n");
	}
}

void FindShortestPath()
{
	PrintMenuHeader("\nNALAZENJE NAJKRACEG PUTA\n");

	if (!GraphLoadedCheck())
		return;

	std::cout
		<< "Unesite ime prvog cvora: ";
	std::string inputFrom;
	std::cin >> inputFrom;

	std::cout
		<< "Unesite ime drugog cvora: ";
	std::string inputTo;
	std::cin >> inputTo;

	int operationResult = graph.DijkstraShortestPath(inputFrom, inputTo);

	std::stringstream sstream;
	if (operationResult == -1)
	{
		sstream << "Neki od unetih cvorova (\"" << inputFrom << "\" i " << "\"" << inputTo << "\") ne postoji u grafu!\n\n";
		PrintError(sstream.str());
	}
	else if (operationResult == -2)
	{
		sstream << "Ne postoji put izmedju cvorova \"" << inputFrom << "\" i " << "\"" << inputTo << "\"!\n\n";
		PrintError(sstream.str());
	}
	else if (operationResult == 0)
	{
		PrintSuccess("Operacija uspesna!\n\n");
	}
}

void FindStronglyConnected()
{
	PrintMenuHeader("\nNALAZENJE JAKO POVEZANIH CVOROVA\n");

	if (!GraphLoadedCheck())
		return;

	std::cout
		<< "Unesite ime cvora: ";
	std::string input;
	std::cin >> input;

	int operationResult = graph.FindStronglyConnected(input);

	std::stringstream sstream;
	if (operationResult == -1)
	{
		sstream << "Cvor \"" << input << "\" ne postoji u grafu!\n\n";
		PrintError(sstream.str());
	}
	else if (operationResult == 0)
	{
		PrintSuccess("Operacija uspesna!\n\n");
	}
}

void MainMenu()
{
	PrintMenuHeader("GLAVNI MENI\n");
	std::cout
		<< "1. Ucitavanje grafa iz fajla\n"
		<< "2. Dodaj cvor u graf\n"
		<< "3. Ukloni cvor iz grafa\n"
		<< "4. Dodaj granu u graf\n"
		<< "5. Ukloni granu iz grafa\n"
		<< "6. Ispisi graf\n"
		<< "7. Obrisi graf iz memorije\n"
		<< "8. Pronadji K najslicnijih cvorova datom cvoru\n"
		<< "9. Pronadji najkraci put izmedju datih cvorova\n"
		<< "10. Pronadji sve cvorove koji su jako povezani sa datim cvorom\n"
		<< "11. Kraj rada\n";

	int input;
	std::cout << "Unesite broj operacije: ";
	std::cin >> input;
	if (std::cin.fail())
	{
		PrintError("Unos mora biti ceo broj!\n\n");
		std::cin.clear();
		std::cin.ignore(256, '\n');
		return;
	}

	switch (input)
	{
	case 1:
		LoadGraphFromFile();
		break;
	case 2:
		AddVertexToGraph();
		break;
	case 3:
		RemoveVertexFromGraph();
		break;
	case 4:
		AddEdgeToGraph();
		break;
	case 5:
		RemoveEdgeFromGraph();
		break;
	case 6:
		PrintGraph();
		break;
	case 7:
		DeleteGraph();
		break;
	case 8:
		FindKMostSimilar();
		break;
	case 9:
		FindShortestPath();
		break;
	case 10:
		FindStronglyConnected();
		break;
	case 11:
		exit(0);
		break;
	default:
		PrintError("Nevalidan broj operacije!\n\n");
		break;
	}
}

int main()
{
	while (true)
	{
		MainMenu();
	}

	return 0;
}