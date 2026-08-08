#ifndef TERMINALUI_H
#define TERMINALUI_H
#include "MarketManager.h"
#include "APIManager.h"
#include "User.h"
#include <iostream>
class TerminalUI {
	private:
		MarketManager Market;
		User* CurrentUser;

	public:

		TerminalUI(MarketManager Market, User* CurrentUser);

		std::string ShowFirstTerminalMenu();

		void Start();
};



#endif // !TERMINALUI_H
