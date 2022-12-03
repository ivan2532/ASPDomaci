#include <iostream>
#include <stdlib.h>

#include "Graph.h"
#include "Utility.h"

#include <filesystem>

Graph* graph = nullptr;

void LoadGraphFromFile()
{
	PrintMenuHeader("\nUCITAVANJE GRAFA IZ FAJLA\n");
	std::cout
		<< "Unesite putanju fajla: ";

	std::string input;
	std::cin >> input;

	graph = new Graph(input);
	if (!graph->IsLoaded())
	{
		return;
	}

	PrintSuccess("Graf uspesno ucitan!\n\n");
}

void PrintGraph()
{
	PrintMenuHeader("\nISPIS GRAFA\n");

	if (graph == nullptr || !graph->IsLoaded())
	{
		PrintError("Graf je obrisan ili nije ucitan!\n\n");
		return;
	}

	std::cout << *graph;
	PrintSuccess("Graf uspesno ispisan!\n\n");
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
		<< "7. Obrisi graf iz memorije\n";

	int input;
	std::cout << "Unesite broj operacije: ";
	std::cin >> input;
	while (std::cin.fail())
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
	case 6:
		PrintGraph();
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