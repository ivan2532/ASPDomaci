#ifndef _utility_h_
#define _utility_h_

#include <string>

#define ESC "\033["
#define LIGHT_BLUE_BKG "106"
#define RED_TXT "31"
#define GREEN_TXT "32"
#define ORANGE_TXT "33"
#define BLUE_TXT "36"
#define WHITE_TXT "37"
#define RESET "\033[m"

void Print(const std::string& message, const std::string& colorCode = WHITE_TXT, std::ostream& ostream = std::cout);
void PrintError(const std::string& message, std::ostream& ostream = std::cerr);
void PrintSuccess(const std::string& message, std::ostream& ostream = std::cout);
void PrintMenuHeader(const std::string& message, std::ostream& ostream = std::cout);

#endif //_utility_h_
