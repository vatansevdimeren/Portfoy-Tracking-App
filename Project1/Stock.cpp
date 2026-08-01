#include "Stock.h"
#include "Cleaner.h"
#include "ConsoleColors.h"
Stock::Stock(std::string Symbol, double Amount, double AvaragePrice, double DividendYield, std::string Broker, bool IsIPO)
	:Asset(Symbol,Amount,AvaragePrice) {
	this->DividendYield = DividendYield;
	this->Broker = Broker;
	this->IsIPO = IsIPO;
}
double Stock::GetDividendYield() { return this->DividendYield; }

std::string Stock::GetBroker() { return this->Broker; }

bool Stock::GetIsIPO() { return this->IsIPO; }



void Stock::SetDividendYield(double NewDividendYield) {	this->DividendYield = NewDividendYield;}

void Stock::SetBroker(std::string NewBroker) { this->Broker = NewBroker; }

void Stock::SetIsIPO(bool NewIpoStatus) { this->IsIPO = NewIpoStatus; }


void Stock::PrintAssetInfo() {
	CleanScreen();
	std::cout << Colors::YELLOW << "Symbol   |   " << GetSymbol() << std::endl;
	std::cout << "Amount   |   " << GetAmount() << std::endl;
	std::cout << "AvaragePrice   |   " << GetAvaragePrice() << std::endl;
	std::cout << "DividendYield   |	  " << GetDividendYield() << std::endl;
	std::cout << "Broker   |   " << GetBroker() << std::endl;
	std::cout << "IsPO state   |   " << GetIsIPO() <<Colors::RESET <<std::endl;
}