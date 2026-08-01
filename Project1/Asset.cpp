#include "Asset.h"
#include <string>

Asset::Asset(std::string AssetSymbol, double AssetAmount, double AssetAvaragePrice) {
	this->Symbol = AssetSymbol;
	this->Amount = AssetAmount;
	this->AveragePrice = AssetAvaragePrice;
}

//Get Functions Here!

std::string Asset::GetSymbol() { return this->Symbol; }

double Asset::GetAmount() { return this->Amount; }

double Asset::GetAvaragePrice() { return this->AveragePrice; }


//Set Functions Here

void Asset::SetSymbol(std::string NewSymbol) { this->Symbol = NewSymbol; }

void Asset::SetAmount(double NewAmount) { this->Amount = NewAmount; }

void Asset::SetAvaragePrice(double NewAvaragePrice) { this->AveragePrice = NewAvaragePrice; }

void Asset::UpdateAvaragePrice(double AdditinoalAmount, double BuyPrice) {
	double CurrentAmount = GetAmount();
	double CurrentAvaragePrice = GetAvaragePrice();

	double NewAvaragePrice = ((CurrentAmount * CurrentAvaragePrice) + (AdditinoalAmount * BuyPrice)) / (CurrentAmount + AdditinoalAmount);

	SetAvaragePrice(NewAvaragePrice);
	SetAmount(CurrentAmount + AdditinoalAmount);
}
double Asset::CalculateTotalValue(double CurrentPrice) {
	return this->Amount * CurrentPrice;
}