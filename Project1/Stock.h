#ifndef STOCK_H
#define STOCK_H
#include "Asset.h"
#include "Cleaner.h"
#include <string>
class Stock : public Asset {
	private:
		double DividendYield;//Temettü verimi yýllýk hesaplanýyor | The effecient of the stock that proivedes you to gain money per year.

		std::string Broker = "";//aracý kurum 
		//It's a name name that you buy or sell on this platform.like ziraat , iþ bank

		bool IsIPO;//Halka arz durumu 

	public:
		//Constructer.
		Stock(std::string Symbol, double Amount, double AvaragePrice, double DividendYield, std::string Broker, bool IsIPO);

		//Get Functions
		double GetDividendYield();
		std::string GetBroker();
		bool GetIsIPO();


		//Set Funcitons
		void SetDividendYield(double NewDividendYield);
		void SetBroker(std::string NewBroker);
		void SetIsIPO(bool NewIpoStatus);

		void PrintAssetInfo() override;
};

#endif
#pragma once
