#include "Crypto.h"
#include "ConsoleColors.h"
#include "Cleaner.h"
Crypto::Crypto(std::string AssetSymbol, double AssetAmount, double AssetAvaragePrice,
	std::string CryptoNetwork, bool StakedStatus) :Asset(AssetSymbol,AssetAmount,AssetAvaragePrice){
	this->Network = CryptoNetwork;
	this->IsStaked = StakedStatus;
}

//Get Functions

std::string Crypto::GetNetwork() { return this->Network; }

bool Crypto::GetStakedStatus() { return this->IsStaked; }


//Set Funcitons

void Crypto::SetNetwork(std::string NewNetwork) { this->Network = NewNetwork; }

void Crypto::SetStakedStatus(bool NewStatus) { this->IsStaked = NewStatus; }

void Crypto::PrintAssetInfo() {
	CleanScreen();
	std::cout << Colors::YELLOW << "Symbol   |   " << GetSymbol() << std::endl;
	std::cout << "Amount   |   " << GetAmount() << std::endl;
	std::cout << "AvaragePrice   |   " << GetAvaragePrice() << std::endl;
	std::cout << "Network    |   " << GetNetwork() << std::endl;
	std::cout << "Staked Status   |   " << GetStakedStatus() << Colors::RESET<<std::endl;
}