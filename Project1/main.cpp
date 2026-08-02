#include "ConsoleColors.h"
#include <iostream>
#include "Algorithm.h"




int main() {

	
	std::cout << Colors::BG_GREEN << "hello \n" << Colors::RESET << std::endl;
	std::cout << Colors::BG_RED << "World \n" << Colors::RESET << std::endl;
	std::cout << Colors::RED << "Test \n" << Colors::RESET << std::endl;
	std::cout << Colors::BG_GREEN << "Amcýk " << Colors::RESET << std::endl;

	
	return 0;
}