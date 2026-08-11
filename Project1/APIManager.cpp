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

HistoricalData APIManager::FetchHistoricalData(const std::string& Symbol, const std::string& Interval) {

	HistoricalData ResultData;

	ResultData.ClosedPrice = 0;
	ResultData.TimeFrame = Interval;
	
	cpr::Response CprResponse = cpr::Get(cpr::Url{ "https://api.binance.com/api/v3/klines" },
		cpr::Parameters{
			{"symbol", Symbol},
			{"interval", Interval},
			{"limit", "1"}//I limited the responses.
		});

	if (CprResponse.status_code != 200) {
		return ResultData;//if connection has wrong or smt happened then return to ResultData.
	}
	nlohmann::json ParsedData = nlohmann::json::parse(CprResponse.text);

	if (ParsedData.empty()) {
		return ResultData; //If There is not the coin which we defined, then return it itself as a 0 ClosedPrice.
	}
	std::string ClosePriceStr = ParsedData[0][4];//everytime it stays on the fourth index of the array
	ResultData.ClosedPrice = std::stod(ClosePriceStr);

}
double APIManager::FetchCurrentPrice(const std::string& Symbol) {
	std::string URL = "https://api.binance.com/api/v3/ticker/price?symbol=" + Symbol;

	cpr::Response CprResponse = cpr::Get(cpr::Url{ URL });

	if (CprResponse.status_code != 200) {
		return 0.0;
	}
	try {
	nlohmann::json ParsedData = nlohmann::json::parse(CprResponse.text);

	
	std::string PriceAsAString = ParsedData["price"];

	return std::stod(PriceAsAString);
	}
	catch (...) {
		return 0.0;
	}
}
double APIManager::GetFiatMultiplierToUSD(const std::string& CurrencyCode) {
	if (CurrencyCode == "TRY") {
		return 1.0/FetchCurrentPrice("USDTTRY");
	}
	else if (CurrencyCode == "EUR") {
		return 1.0/FetchCurrentPrice("EURUSDT");
	}
	else if(CurrencyCode == "USD"){
		return 1.0;
	}
	else {
		std::cerr << Colors::RED << "INVALID INPUT!" << Colors::RESET << std::endl;
		return 0.0;
	}
}
std::vector<MarketAsset> APIManager::FetchWalletCryptoData(const std::vector<std::string>& Symbols) {
	std::vector<MarketAsset> MarketData;

	if (Symbols.empty()) { return MarketData; }


	//Burada Türkçe acýklama yapýcam burayý direkt AI yaptý burada yaptýðý þey ise Binance APIsýna uygun formata getirmek Atacaðýmýz reqquesti.
	//in Here, we are redesign the all symbols and we create a string that Binance API can understand what we want.
	std::string SymbolsParam = "[";
	for (size_t i = 0; i < Symbols.size(); i++) {
		SymbolsParam += "\"" + Symbols[i] + "\"";
		if (i != Symbols.size() - 1) {
			SymbolsParam += ","; 
		}
	}
	SymbolsParam += "]";
	std::string URL = "https://api.binance.com/api/v3/ticker/price?symbols=" + SymbolsParam;

	cpr::Response CprResponse = cpr::Get(cpr::Url{ URL });

	if (CprResponse.status_code != 200) { return MarketData; }
	try {
		nlohmann::json ParsedData = nlohmann::json::parse(CprResponse.text);

		for (size_t i = 0; i < ParsedData.size(); i++) {
			MarketAsset asset;
			asset.Symbol = ParsedData[i]["symbol"];
			asset.CurrentPrice = std::stod(ParsedData[i]["price"].get<std::string>());

			MarketData.push_back(asset);
		}
	}
	catch (...) {
	}
	return MarketData;

}