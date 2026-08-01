#ifndef USER_H
#define USER_H
#include "Crypto.h"
#include "Stock.h"
#include <iostream>
#include <string>
#include <vector>
class User {
	private:
		std::string NickName = "";
		unsigned long long int PasswordHash = 5381;
		
		//The Function provides to you to calculate its Hash by using DJB2 algorithm.
		//Dont forget The number that calculated is on base 10
		static unsigned long long int DJB2(std::string CurrentPassword);

		std::vector<Crypto> CryptoWallet;
		std::vector<Stock> StockWallet;
	public:
		
		User(std::string Username, unsigned long long int UserHash);
		User(std::string Username, std::string RawPassword);

		std::string GetNickname();
		unsigned long long int GetPasswordHash();

		void SetNickname(std::string NewNickname);
		void SetPasswordHash(unsigned long long int NewHash);

		static void SignIn();

		static User* LogIn();

		void SaveUser(std::string Tag);
		void LoadUser(std::string Tag);
};


#endif 


