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


		void ShowAllPortfolio();
		void Start();

		void DepositAndWithdrawMenu();

		void ManageAssetsMenu();

		void TradeMarketMenu();

		void SettingsMenu();
};



#endif // !TERMINALUI_H
