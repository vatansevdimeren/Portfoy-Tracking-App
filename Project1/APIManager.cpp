#include "APIManager.h"
#include "ConsoleColors.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

std::vector<MarketAsset> APIManager::FetchCryptoData() {

	std::vector<MarketAsset> FetchedData;//Here I create a vector to store all coins

	cpr::Response CprResponse = cpr::Get(cpr::Url{ "https://api.binance.com/api/v3/ticker/price" });
	//in here the program sends a request to get coins infos.

	if (CprResponse.status_code != 200) {
		std::cerr << "The Connection is not succesfull!\nError Code : " << CprResponse.status_code << std::endl;
		return FetchedData;
		//if the status code is not equel to 200 ,then the program will work,but if it is not 200 we give  user a message to say its error code.

	}
	
	nlohmann::json ParsedData = nlohmann::json::parse(CprResponse.text);
	//in here I used parsing library to parse the long string response 
	//it divides the string parses
	
	size_t TotalAssetAmount = ParsedData.size();
	//in here , I give the size of parsed data.
	
	FetchedData.reserve(TotalAssetAmount);
	//normally in here I shoudlt do that because vector is dynamic list we know,
	//but if we know that there are so many assests, we need to get some space from the ram.
	
	for (size_t i = 0; TotalAssetAmount > i; i++) {
		std::string Symbol = ParsedData[i]["symbol"];
		//In here, I got the string next to Symbol it related to its string connection I mean after the symbol the next string is symbol
		//also parsing operation where it is.
		std::string Price_But_As_A_string = ParsedData[i]["price"];
		//Most of the time the values come as a string so we need to convert it to double.
		double Price = std::stod(Price_But_As_A_string);

		MarketAsset CurrentAsset;
		CurrentAsset.Symbol = Symbol;
		CurrentAsset.CurrentPrice = Price;
		//Asset created as a succesfully so we can push it in the vector.
		FetchedData.push_back(CurrentAsset);
	}

	std::cout << Colors::RED << TotalAssetAmount << " Assets added the market." << Colors::RESET << std::endl;

	return FetchedData;

}