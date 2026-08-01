#ifndef ASSET_H
#define ASSET_H
#include "Cleaner.h"
#include <string>

class Asset {
protected:
	std::string Symbol = "";
	double Amount = 0;
	double AveragePrice = 0;
public:

	Asset(std::string AssetSymbol, double AssetAmount, double AssetAvaragePrice);

	virtual ~Asset() {}

	//Get Functions
	std::string GetSymbol();
	double GetAmount();
	double GetAvaragePrice();


	//Set Functions
	void SetSymbol(std::string NewSymbol);
	void SetAmount(double NewAmount);
	void SetAvaragePrice(double NewAvaragePrice);

	void UpdateAvaragePrice(double AdditinoalAmount, double BuyPrice);

	double CalculateTotalValue(double CurrentPrice);

	virtual void PrintAssetInfo() = 0;


};

#endif
#pragma once
