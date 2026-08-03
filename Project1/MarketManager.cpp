#include "MarketManager.h"
#include <iostream>
#include "Algorithm.h"


void MarketManager::AddAsset(AssetType Type, const std::string& Symbol, double Price) {
	if (Type == AssetType::Crypto) {
		unsigned short int BufferSize = BufferCryptoVector.size();

		if (BufferSize < 100) {
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
		if (BufferSize < 100) {
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
	//or Gold Silver Uraninum can be added.
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