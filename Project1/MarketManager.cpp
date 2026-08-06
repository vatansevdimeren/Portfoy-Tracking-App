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
	Algorithm::MergeSort(CryptoAssests);
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

			size_t TotalSize = BufferCryptoVector.size() + MainCryptoVector.size();

			std::vector<MarketAsset> NewVector(TotalSize);

			Algorithm::Merge(MainCryptoVector, BufferCryptoVector, NewVector);

			MainCryptoVector = std::move(NewVector);
			
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

			size_t TotalSize = MainStockVector.size() + BufferStockVector.size();

			std::vector<MarketAsset> NewVector(TotalSize);
			

			Algorithm::Merge(MainStockVector, BufferStockVector, NewVector);

			MainStockVector = std::move(NewVector);

			BufferStockVector.clear();
		}
	}
	//here might be added some other parametres such as money (EURO/DOLAR/YEN,etc...)
	//or Gold Silver Uraninum can be added.11111111
}
double MarketManager::GetPrice(AssetType Type, const std::string Symbol) {
	//In this function, The data will be searched in the main vector by using Binary search because the main vector everytime will be sorted.
	//if it is not found in the main vector stock or crypto, it is gonna change the direction and it's gonna start to search on BufferVector,
	//BufferVector will be searched by using linear search algorithm because its size maximum can be 100 which is pre defined as a BufferMaximumSize
	//if it is not found in the two of them ,then, the user will encounter a error message that is gonna be "Ýt's not in our databases..."

	if (Type == AssetType::Crypto) {
		long long int  Index = -1;

		MarketAsset SymbolicAssest{ Symbol,1 };

		Index = Algorithm::BinarySearch(MainCryptoVector, SymbolicAssest);

		if (Index != -1) {
			return MainCryptoVector[Index].CurrentPrice;
		}

		//if it is not found in the main vector of crypto then search by the linear one.

		Index = Algorithm::LinearSearch(BufferCryptoVector, SymbolicAssest);

		if (Index != -1) {
			return BufferCryptoVector[Index].CurrentPrice;
		}

		std::cout << Colors::RED << "The assest : " << Symbol << " is not our data bases!" << Colors::RESET << std::endl;
		return -1;
		
	}
	else if (Type == AssetType::Stock) {
		long long int Index = -1;

		MarketAsset SymbolicAsset{ Symbol,1 };

		Index = Algorithm::BinarySearch(MainStockVector, SymbolicAsset);

		if (Index != -1) {
			return MainStockVector[Index].CurrentPrice;
		}

		Index = Algorithm::LinearSearch(BufferStockVector, SymbolicAsset);

		if (Index != -1) {
			return BufferStockVector[Index].CurrentPrice;
		}

		std::cout << Colors::RED << "The assest : " << Symbol << " is not our data bases!" << Colors::RESET << std::endl;
		return -1;
	}

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