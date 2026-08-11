#ifndef USER_H
#define USER_H
#include "Crypto.h"
#include "Stock.h"
#include <iostream>
#include <string>
#include <vector>
struct CashBalance {
	std::string CurrencyCode = "";
	double Amount = 0;
};
class User {
	private:
		std::string NickName = "";
		unsigned long long int PasswordHash = 5381;
		std::string Currency = "USD";
		//The Function provides to you to calculate its Hash by using DJB2 algorithm.
		//Dont forget The number that calculated is on base 10
		static unsigned long long int DJB2(std::string CurrentPassword);

		std::vector<Crypto> CryptoWallet;
		std::vector<Stock> StockWallet;
		std::vector<CashBalance> CashWallet;
	public:
		
		User(std::string Username, unsigned long long int UserHash);
		User(std::string Username, std::string RawPassword);

		std::string GetNickname();
		unsigned long long int GetPasswordHash();
		std::string GetCurrency();


		//For vector's get functions....
		std::vector<Crypto>& GetCryptoWallet();
		std::vector<Stock>& GetStockWallet();
		std::vector<CashBalance>& GetCashWallet();

		void SetNickname(std::string NewNickname);
		void SetPasswordHash(unsigned long long int NewHash);
		void SetCurrency(std::string NewCurrency);
		static void SignIn();

		static User* LogIn();

		void SaveUser(std::string Tag);
		void LoadUser(std::string Tag);
};


#endif 


