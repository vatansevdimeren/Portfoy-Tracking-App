#include "User.h"
#include "ConsoleColors.h"
#include <fstream>
#include "Cleaner.h"
#include <filesystem>
#include <stdexcept>
//-3 Error code is UNSUCCESFULL READING OR WRITING OPERATIN in fstream lib.
//It occurs when they dont work.

//For the first consturctor, My aim is to transferses the all users from ssd to the main memory to make any operation on it.

User::User(std::string Username, unsigned long long int UserHash) {
	this->NickName = Username;
	this->PasswordHash = UserHash;
}
//for the second Consturctor, My aim is To create any person by using it. It also Provides to you
//Create a user as easy as possible because the programming knows that which constuctor it needs to use.

User::User(std::string Username, std::string RawPassword) {
	this->NickName = Username;
	this->PasswordHash = User::DJB2(RawPassword);
}
unsigned long long int User::DJB2(std::string CurrentPassword) {
	unsigned long long int Hash = 5381;
	for (unsigned short int i = 0; CurrentPassword.size() > i; i++) {
		Hash = ((Hash << 5) + Hash )+CurrentPassword[i];
	}
	return Hash;
}
std::string User::GetCurrency() { return this->Currency; }
std::string User::GetNickname() {
	return this->NickName;
}
std::vector<Crypto>& User::GetCryptoWallet() { return this->CryptoWallet; }
std::vector<Stock>& User::GetStockWallet() { return this->StockWallet; }
std::vector<CashBalance>& User::GetCashWallet() { return this->CashWallet; }
unsigned long long int User::GetPasswordHash() {
	return this->PasswordHash;
}
void User::SetNickname(std::string NewNickname) {
	this->NickName = NewNickname;
}
void User::SetPasswordHash(unsigned long long int NewHash) {
	this->PasswordHash = NewHash;
}
void User::SetCurrency(std::string NewCurrency) {
	this->Currency = NewCurrency;
}
void User::SignIn() {
	std::string UserNickname;


	std::cout << Colors::BLUE << "Please enter your nickname : " << Colors::RESET << std::endl;

	std::getline(std::cin, UserNickname);


	std::fstream Read("UserNickname.txt", std::ios::in);

	if (Read.is_open()) {
		std::string TempUserNameInfile = "";
		while (Read >> TempUserNameInfile) {
			if (UserNickname == TempUserNameInfile)
			{
				std::cerr << Colors::RED << "The username is taken please try again !" << Colors::RESET << std::endl;
				Read.close();
				return SignIn();
			}
		}
		Read.close();
	}
	Read.close();
	short int Counter = 0;
	std::string UserPassword = "";
	while (true) {
		if (Counter > 3) { std::cout << Colors::RED << "You have tried so many times please try again!" << Colors::RESET << std::endl; return; }
		std::cout << Colors::BG_RED << "Hint 1 : Your password must be longer than eight characters.\n";
		std::cout << "Hint 2 : Your password must have at least one bigger and one smaller character.\n" << Colors::RESET << std::endl;

		std::cout << Colors::BLUE << "Please enter your password : ";

		

		std::getline(std::cin, UserPassword);
		bool IsLength = false;
		bool SmallChar = false;
		bool BigChar = false;
		if (UserPassword.length() >= 8)IsLength = true;

		for (short int i = 0; UserPassword.size() > i; i++) {
			if (UserPassword[i] >= 'a' && UserPassword[i] <= 'z')SmallChar = true;
			if (UserPassword[i] >= 'A' && UserPassword[i] <= 'Z')BigChar = true;
		}
		if (IsLength && SmallChar && BigChar) {
			break;
		}
		Counter++;
		system("cls");
	}


	std::fstream Write("UserNickname.txt", std::ios::app | std::ios::out);

	if (!Write.is_open()) {
		std::cerr << Colors::RED << "The UserNickname.txt file was not oppened !!!" << Colors::RESET << std::endl;
		exit(-3);
	}


	Write << UserNickname << std::endl;

	Write.close();

	//Okey then the person is okey to create.


	User CurrentUser(UserNickname,UserPassword);


	//lets save the user in a binary file.


	std::ofstream BinaryWrite("UsersVault.dat", std::ios::app | std::ios::binary);

	if (!BinaryWrite.is_open()) {
		std::cerr << Colors::RED << "The UsersVault for writing operation is unsuccesfull." << Colors::RESET << std::endl;
		exit(-3);
	}

	short int NameLength = CurrentUser.GetNickname().size();

	BinaryWrite.write((char*)&NameLength, sizeof(NameLength));

	BinaryWrite.write(CurrentUser.GetNickname().c_str(), NameLength);

	unsigned long long int SavedHash = CurrentUser.GetPasswordHash();

	BinaryWrite.write((char*)&SavedHash, sizeof(SavedHash));

	BinaryWrite.close();

	std::string CurrencType;
	std::string AmountAsString;
	double InitialBalance=0.0;

	std::cout <<Colors::BLUE <<"Please enter which type of money do you have (TRY,USD,EUR...)";
	std::getline(std::cin, CurrencType);

	std::cout << "Please enter the Amount of " << CurrencType << " : ";
	std::getline(std::cin, AmountAsString);
	std::cout << Colors::RESET;

	try {
		InitialBalance = std::stod(AmountAsString);
	}
	catch (const std::invalid_argument& e) {
        std::cout << Colors::RED << "[WARNING] You entered letters instead of numbers! Balance set to 0.0." << Colors::RESET << "\n";
        InitialBalance = 0.0;
    } 
    catch (const std::out_of_range& e) {
        std::cout << Colors::RED << "[WARNING] Number is too large! Balance set to 0.0." << Colors::RESET << "\n";
        InitialBalance = 0.0;
    }
	std::string UserCurrency = "";
	std::cout << Colors::BLUE << "Which currency do you want to see your portfolio in? (USD, TRY, EUR) : " << Colors::RESET;
	std::getline(std::cin, UserCurrency);

	CurrentUser.SetCurrency(UserCurrency);
	CurrentUser.SaveUser("Settings");

	std::cout << Colors::GREEN << "Confirmed Balance: " << InitialBalance << Colors::RESET << "\n";
	std::cout << Colors::GREEN << "The user is created succesfully!!!" << Colors::RESET << std::endl;

	CashBalance NewCash;
	NewCash.CurrencyCode = CurrencType;
	NewCash.Amount = InitialBalance;

	CurrentUser.CashWallet.push_back(NewCash);

	CurrentUser.SaveUser("Cash");

	

}
User* User::LogIn() {
	short int Counter = 3;
	while (Counter > 0) {
		CleanScreen();
		std::string UserNickName="";
		std::string UserPassword = "";
		std::cout << Colors::RED << "Attemp left : " << Counter << Colors::RESET << std::endl;
		
		std::cout << Colors::BLUE << "Please enter your name : ";
		std::getline(std::cin, UserNickName);

		std::cout << "Please enter your password : ";
		std::getline(std::cin, UserPassword);


		std::fstream Read("UsersVault.dat", std::ios::in | std::ios::binary);

		if (!Read.is_open()) {
			std::cerr << Colors::BG_RED << "The UsersVault.dat file for reading operation is unsuccesfull." << Colors::RESET << std::endl;
			exit(-3);
		}
		short int NameLength = 0;
		while (Read.read((char*)&NameLength, sizeof(NameLength))) {
			std::string CurrentName = "";
			CurrentName.resize(NameLength);
			Read.read(&CurrentName[0], NameLength);
			unsigned long long int CurrentHash = 0;

			Read.read((char*)&CurrentHash, sizeof(CurrentHash));

			if (UserNickName == CurrentName && User::DJB2(UserPassword)==CurrentHash) {
				Read.close();
				return new User(CurrentName, CurrentHash);
			}
		}
		Counter--;
		std::cout << Colors::RED << "Invalid Nickname or Password!" << Colors::RESET << "\n";


		Read.close();

	}
	return nullptr;
}
void User::SaveUser(std::string Tag) {
	std::string FolderPath = "Database/" + this->NickName;
	if (!std::filesystem::exists(FolderPath)) {
		std::filesystem::create_directories(FolderPath);
	}
	std::string FilePath = FolderPath + "/" + Tag + ".dat";

	std::fstream Write(FilePath, std::ios::out | std::ios::trunc);

	if (!Write.is_open()) {
		std::cerr << Colors::RED << "The Writing operation in" << FilePath << " is not succesfull!" << Colors::RESET << std::endl;
		exit(-3);
	}
	if (Tag == "Crypto") {
		for (size_t i = 0; this->CryptoWallet.size() > i; i++) {

			std::string CurrentSymbol = CryptoWallet[i].GetSymbol();
			size_t CurrentSymbolLength = CurrentSymbol.length();

			Write.write((char*)&CurrentSymbolLength, sizeof(CurrentSymbolLength));
			Write.write(CurrentSymbol.c_str(), CurrentSymbolLength);


			double CurrentAmount = CryptoWallet[i].GetAmount();
			Write.write((char*)&CurrentAmount, sizeof(CurrentAmount));


			double CurrentAvaragePrice = CryptoWallet[i].GetAvaragePrice();
			Write.write((char*)&CurrentAvaragePrice, sizeof(CurrentAvaragePrice));

			std::string CurrentNetwork = CryptoWallet[i].GetNetwork();
			size_t CurrentNetworkLength = CurrentNetwork.length();

			Write.write((char*)&CurrentNetworkLength, sizeof(CurrentNetworkLength));
			Write.write(CurrentNetwork.c_str(), CurrentNetworkLength);

			bool CurrentStakedStatus = CryptoWallet[i].GetStakedStatus();
			Write.write((char*)&CurrentStakedStatus, sizeof(CurrentStakedStatus));
		}
	}
	else if (Tag == "Stock") {
		for (size_t i = 0; i < this->StockWallet.size(); i++) {

			std::string sym = StockWallet[i].GetSymbol();
			size_t symLen = sym.size();
			Write.write((char*)&symLen, sizeof(symLen));
			Write.write(sym.c_str(), symLen);

			double amt = StockWallet[i].GetAmount();
			Write.write((char*)&amt, sizeof(amt));

			double avg = StockWallet[i].GetAvaragePrice();
			Write.write((char*)&avg, sizeof(avg));

			double div = StockWallet[i].GetDividendYield();
			Write.write((char*)&div, sizeof(div));

			std::string broker = StockWallet[i].GetBroker();
			size_t brokerLen = broker.size();
			Write.write((char*)&brokerLen, sizeof(brokerLen));
			Write.write(broker.c_str(), brokerLen);

			bool ipo = StockWallet[i].GetIsIPO();
			Write.write((char*)&ipo, sizeof(ipo));
		}
	}
	else if (Tag == "Cash") {
		for (size_t i = 0; i < this->CashWallet.size(); i++) {

			// Para biriminin uzunlugunu ve kendisini yaz (Orn: "TRY")
			std::string code = CashWallet[i].CurrencyCode;
			size_t codeLen = code.size();
			Write.write((char*)&codeLen, sizeof(codeLen));
			Write.write(code.c_str(), codeLen);

			// Bakiye miktarini yaz (Orn: 10000.50)
			double amt = CashWallet[i].Amount;
			Write.write((char*)&amt, sizeof(amt));
		}
	}
	else if (Tag == "Settings") {
		size_t LengthOftheCurrency = this->Currency.length();
		Write.write((char*)&LengthOftheCurrency, sizeof(LengthOftheCurrency));
		Write.write(this->Currency.c_str(), LengthOftheCurrency);
	}


	Write.close();
}
void User::LoadUser(std::string Tag) {
	std::string FilePath = "Database/" + this->NickName + "/" + Tag + ".dat";


	std::fstream Read(FilePath, std::ios::in);

	if (!Read.is_open()) {
		return;//Void Return when the reading operaion doesnt work.
	}

	//Here comes some reading operation after I write the other classes...

	if (Tag == "Crypto") {
		size_t symLen;
		while (Read.read((char*)&symLen, sizeof(symLen))) {

			
			std::string sym;
			sym.resize(symLen);
			Read.read(&sym[0], symLen); 

		
			double amt;
			Read.read((char*)&amt, sizeof(amt));

			
			double avg;
			Read.read((char*)&avg, sizeof(avg));

			
			size_t netLen;
			Read.read((char*)&netLen, sizeof(netLen));
			std::string net;
			net.resize(netLen);
			Read.read(&net[0], netLen);

			
			bool stk;
			Read.read((char*)&stk, sizeof(stk));

			
			Crypto loadedCrypto(sym, amt, avg, net, stk);
			this->CryptoWallet.push_back(loadedCrypto);
		}
	}
	else if (Tag == "Stock") {
		size_t symLen;
		while (Read.read((char*)&symLen, sizeof(symLen))) {

			std::string sym;
			sym.resize(symLen);
			Read.read(&sym[0], symLen);

			double amt;
			Read.read((char*)&amt, sizeof(amt));

			double avg;
			Read.read((char*)&avg, sizeof(avg));

			double div;
			Read.read((char*)&div, sizeof(div));

			size_t brokerLen;
			Read.read((char*)&brokerLen, sizeof(brokerLen));
			std::string broker;
			broker.resize(brokerLen);
			Read.read(&broker[0], brokerLen);

			bool ipo;
			Read.read((char*)&ipo, sizeof(ipo));

			Stock loadedStock(sym, amt, avg, div, broker, ipo);
			this->StockWallet.push_back(loadedStock);
		}
	}
	else if (Tag == "Cash") {
		size_t codeLen;
		while (Read.read((char*)&codeLen, sizeof(codeLen))) {

			
			std::string code;
			code.resize(codeLen);
			Read.read(&code[0], codeLen);

			
			double amt;
			Read.read((char*)&amt, sizeof(amt));

			CashBalance loadedCash;
			loadedCash.CurrencyCode = code;
			loadedCash.Amount = amt;

			this->CashWallet.push_back(loadedCash);
		}
	}
	else if (Tag == "Settings") {
		size_t CurrencyLength = 0;
		while (Read.read((char*)&CurrencyLength, sizeof(CurrencyLength))) {
			std::string CurrencyAsString="";
			CurrencyAsString.resize(CurrencyLength);
			Read.read(&CurrencyAsString[0], CurrencyLength);

			this->SetCurrency(CurrencyAsString);

		}
	}

	//////



	Read.close();
}
