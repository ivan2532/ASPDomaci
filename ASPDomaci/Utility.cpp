#include <iostream>

#include "Utility.h"

void Print(const std::string& message, const std::string& colorCode, std::ostream& ostream)
{
	ostream << ESC << colorCode << "m" << message << RESET;
}

void PrintError(const std::string& message, std::ostream& ostream)
{
	Print(message, RED_TXT, ostream);
}

void PrintSuccess(const std::string& message, std::ostream& ostream)
{
	Print(message, GREEN_TXT, ostream);
}

void PrintMenuHeader(const std::string& message, std::ostream& ostream)
{
	Print(message, BLUE_TXT, ostream);
}
