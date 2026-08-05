#include "MarketManager.h"
#include <iostream>
#include "Algorithm.h"
#include "APIManager.h"
#include "ConsoleColors.h"
#include <iostream>
#define BufferMaximumSize 100
void MarketManager::InitCryptoMarket() {
	std::vector<MarketAsset> CryptoAssests = APIManager::FetchCryptoData();

	if (CryptoAssests.empty()) {
		std::cerr << Colors::RED << "The size of crypto assest is zero!\nLoading Operation unsuccessfull!" << Colors::RESET << std::endl;
		return;
	}

	MainCryptoVector = std::move(CryptoAssests);
	Algorithm::InsertionSort(MainCryptoVector);
}

void MarketManager::AddAsset(AssetType Type, const std::string& Symbol, double Price) {
	if (Type == AssetType::Crypto) {
		unsigned short int BufferSize = BufferCryptoVector.size();

		if (BufferSize < BufferMaximumSize) {
			BufferCryptoVector.push_back(MarketAsset(Symbol, Price));
		}
		else{
			BufferCryptoVector.push_back(MarketAsset(Symbol, Price));
			Algorithm::InsertionSort(BufferCryptoVector);
			
			//Then it is gonne be merged by the merge function two sorted vectors will be sorted...
			BufferCryptoVector.clear();
		}
	}
	else if (Type == AssetType::Stock) {
		unsigned short int BufferSize = BufferStockVector.size();
		if (BufferSize < BufferMaximumSize) {
			BufferStockVector.push_back(MarketAsset(Symbol, Price));
		}
		else {
			BufferStockVector.push_back(MarketAsset(Symbol, Price));
			Algorithm::InsertionSort(BufferStockVector);

			//Merge sort here too
			BufferStockVector.clear();
		}
	}
	//here might be added some other parametres such as money (EURO/DOLAR/YEN,etc...)
	//or Gold Silver Uraninum can be added.11111111
}
double MarketManager::GetPrice(AssetType Type, const std::string Symbol) {

}
void MarketManager::TrackAsset(AssetType Type, const std::string Symbol) {
	if (Type == AssetType::Crypto) {
		for (size_t i = 0; TrackedCryptoVector.size() > i; i++) {
			if (TrackedCryptoVector[i] == Symbol) { return; }
		}
		TrackedCryptoVector.push_back(Symbol);
	}
	else if (Type == AssetType::Stock) {
		for (size_t i = 0; TrackedStockVector.size() > i; i++) {
			if (TrackedStockVector[i] == Symbol) { return; }
		}
		TrackedStockVector.push_back(Symbol);
	}
}