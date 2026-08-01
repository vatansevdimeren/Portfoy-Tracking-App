#include "ConsoleColors.h"
#include <iostream>





int main() {

	
	std::cout << Colors::BG_GREEN << "hello \n" << Colors::RESET << std::endl;
	std::cout << Colors::BG_RED << "World \n" << Colors::RESET << std::endl;
	std::cout << Colors::RED << "Test \n" << Colors::RESET << std::endl;


	
	return 0;
}