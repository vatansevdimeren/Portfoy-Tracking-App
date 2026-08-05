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
