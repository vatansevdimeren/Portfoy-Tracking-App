#ifndef APIMANAGER_H
#define APIMANAGER_H
#include <iostream>
#include <vector>
#include "MarketManager.h"
#include "Asset.h"
#include <string>
class APIManager {
	public:
		HistoricalData FetchHistoricalData(const std::string& Symbol, const std::string& Interval);


		static std::vector<MarketAsset> FetchCryptoData();

		static std::vector<MarketAsset> FetchWalletCryptoData(const std::vector<std::string>& Symbols);

		static double FetchCryptoPrice(const std::string& Symbol);

		static double FetchStockPrice(const std::string& Symbol);

		static std::vector<MarketAsset> FetchWalletStockData(const std::vector<std::string>& Symbols);

		static double GetFiatMultiplierToUSD(const std::string& CurrencyCode);
};
#endif // !APIMANAGER_H
