#ifndef MARKETMANAGER_H
#define MARKETMANAGER_H
#define BufferLimit 100
#include <string>
#include <vector>
enum class AssetType {
	Crypto,
	Stock
};
struct MarketAsset {
	std::string Symbol = "";
	double CurrentPrice;
	bool operator<(const MarketAsset& diger) const {
		return this->Symbol < diger.Symbol;
	}
	//I added The boolen operation because in the algorithms I used just vectors or arrays I dont match them in a single type.
	//so when the complier sees the code it's going to understand what operation it does.
	//the some other boolen types...
	bool operator>(const MarketAsset& diger) const {
		return this->Symbol > diger.Symbol;
	}

	bool operator==(const MarketAsset& diger) const {
		return this->Symbol == diger.Symbol;
	}
};

class MarketManager {
	private:
		std::vector<MarketAsset> MainCryptoVector;
		std::vector<MarketAsset> BufferCryptoVector;
		std::vector<std::string> TrackedCryptoVector;


		std::vector<MarketAsset> MainStockVector;
		std::vector<MarketAsset> BufferStockVector;
		std::vector<std::string> TrackedStockVector;

	public:

		void InitCryptoMarket();

		void AddAsset(AssetType Type,const std::string& Symbol, double Price);

		double GetPrice(AssetType Type, const std::string Symbol);

		void TrackAsset(AssetType Type, const std::string Symbol);
};



#endif // !MARKETMANAGER_H
