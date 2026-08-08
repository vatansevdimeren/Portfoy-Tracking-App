#ifndef APIMANAGER_H
#define APIMANAGER_H
#include <iostream>
#include <vector>
#include "MarketManager.h"
#include "Asset.h"
class APIManager {
	public:
		HistoricalData FetchHistoricalData(const std::string& Symbol, const std::string& Interval);


		static std::vector<MarketAsset> FetchCryptoData();



		static std::vector<MarketAsset> FetchStockData();
};
#endif // !APIMANAGER_H
