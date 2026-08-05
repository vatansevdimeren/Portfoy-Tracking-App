#ifndef APIMANAGER_H
#define APIMANAGER_H
#include <vector>
#include "MarketManager.h"
class APIManager {
	public:
		static std::vector<MarketAsset> FetchCryptoData();

		static std::vector<MarketAsset> FetchStockData();
};
#endif // !APIMANAGER_H
