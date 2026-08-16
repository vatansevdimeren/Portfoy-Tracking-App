#include "TerminalUI.h"
#include "APIManager.h"
#include "ConsoleColors.h"
#include "User.h"
#include <iomanip>//input output manipilation lib.
#include <iostream>
#include <conio.h>  
#include <thread>   
#include <chrono> 
TerminalUI::TerminalUI(MarketManager Market, User* CurrentUser) {
	this->CurrentUser = nullptr;
	this->Market = Market;
}
std::string TerminalUI::ShowFirstTerminalMenu() {
    CleanScreen();
    std::cout << Colors::CYAN << Colors::BOLD << "=================================\n" << Colors::RESET;
    std::cout << Colors::YELLOW << Colors::BOLD << "     WELCOME TO TEX TERMINAL     \n" << Colors::RESET;
    std::cout << Colors::CYAN << Colors::BOLD << "=================================\n" << Colors::RESET;
    std::cout << Colors::GREEN << "[1] " << Colors::RESET << "Log In\n";
    std::cout << Colors::GREEN << "[2] " << Colors::RESET << "Sign Up\n";
    std::cout << Colors::RED << "[3] " << Colors::RESET << "Exit\n";
    std::cout << Colors::CYAN << "\nSelect an option: " << Colors::RESET;

    std::string Choice = "";

    std::getline(std::cin, Choice);

    if (Choice !="1" && Choice != "2" && Choice != "3") {
        std::cout << Colors::RED << "PLEASE ENTER AVAILABLE CHOOSEN NUMBER !" << Colors::RESET << std::endl;
        return ShowFirstTerminalMenu();//recursion tuzaðýna burada düþmez eðer aþýrý salak deðilse kullanýcý yani maymun olmasý lazým
    }
    return Choice;
}
void TerminalUI::Start() {
    bool IsRunning = true;

    while (IsRunning) {

        if (CurrentUser == nullptr) {

            int UserChoice = std::stoi(ShowFirstTerminalMenu());

            switch (UserChoice) {
            case 1:
                {
                User* CurrentUserT = User::LogIn();
                if (CurrentUserT != nullptr) {
                    std::cout << Colors::GREEN << "\nLogin Successful!" << Colors::RESET << "\n";
                    this->CurrentUser = CurrentUserT;
                    CurrentUser->LoadUser("Crypto");
                    CurrentUser->LoadUser("Stock");
                    CurrentUser->LoadUser("Cash");
                    std::cout << Colors::GREEN << "Data loaded successfully!\n" << Colors::RESET;
                    Pause();
                }
                break;
                }
            case 2:
                User::SignIn();
                
                break;
            case 3:
                std::cout << "\n" << Colors::BG_RED << Colors::WHITE << " Shutting down TEX Terminal. Goodbye! " << Colors::RESET << "\n";
                //Save Functions is gonna be put here by me
                IsRunning = false;
                break;
            default:
                std::cout << Colors::RED << "\nInvalid choice! Please try again." << Colors::RESET << "\n";
                Pause();
                break;
            }
        }
        else {
            CleanScreen();
            std::cout << Colors::CYAN << "=================================\n" << Colors::RESET;
            std::cout << Colors::YELLOW << "      LOGGED IN AS: " << CurrentUser->GetNickname() << "\n" << Colors::RESET;
            std::cout << Colors::CYAN << "=================================\n" << Colors::RESET;

            std::cout << Colors::GREEN << "[1] " << Colors::RESET << "Show Portfolio (Live API PnL)\n";
            std::cout << Colors::GREEN << "[2] " << Colors::RESET << "Deposit / Withdraw Cash\n";
            std::cout << Colors::GREEN << "[3] " << Colors::RESET << "Add Asset Manually\n";
            std::cout << Colors::GREEN << "[4] " << Colors::RESET << "Trade Market \n";
            std::cout << Colors::GREEN << "[5] " << Colors::RESET << "Settings (Change Base Currency)\n";
            std::cout << Colors::RED << "[6] " << Colors::RESET << "Log Out & Save\n";
            std::cout << Colors::CYAN << "\nSelect an option: " << Colors::RESET;
            std::string LoggedInChoice = "";
            std::getline(std::cin, LoggedInChoice);

            if (LoggedInChoice == "1") {
                ShowAllPortfolio();
            }
            else if (LoggedInChoice == "2") {
                TerminalUI::DepositAndWithdrawMenu();
            }
            else if (LoggedInChoice == "3") {
                TerminalUI::ManageAssetsMenu();
            }
            else if (LoggedInChoice == "4") {
                TerminalUI::TradeMarketMenu();
                Pause();
            }
            else if (LoggedInChoice == "5") {
                SettingsMenu();
                Pause();
            }
            else if (LoggedInChoice == "6") {
                std::cout << Colors::YELLOW << "\nSaving and logging out...\n" << Colors::RESET;
               
                CurrentUser->SaveUser("Crypto");
                CurrentUser->SaveUser("Stock");
                CurrentUser->SaveUser("Cash");

                std::cout << Colors::GREEN << "All data saved securely.\n" << Colors::RESET;
                std::cout << Colors::YELLOW << "Logging out...\n" << Colors::RESET;

                delete CurrentUser;
                CurrentUser = nullptr;//!!!!
            }
            else {
                std::cout << Colors::RED << "Invalid choice!" << Colors::RESET << std::endl;
                Pause();
            }
        }
    }
}
void TerminalUI::ShowAllPortfolio() {
    APIManager API;

    std::vector<std::string> cryptoSymbols;
    for (size_t i = 0; i < CurrentUser->GetCryptoWallet().size(); i++) {
        cryptoSymbols.push_back(CurrentUser->GetCryptoWallet()[i].GetSymbol() + "USDT");
    }

    std::vector<std::string> stockSymbols;
    for (size_t i = 0; i < CurrentUser->GetStockWallet().size(); i++) {
        stockSymbols.push_back(CurrentUser->GetStockWallet()[i].GetSymbol());
    }
    CleanScreen();
    std::cout << Colors::CYAN << "========================================================================================\n" << Colors::RESET;
    std::cout << Colors::YELLOW << "                             TEX LIVE DASHBOARD - LOADING...                            \n" << Colors::RESET;
    std::cout << Colors::CYAN << "========================================================================================\n" << Colors::RESET;
    std::cout << Colors::BLUE << "\n[*] Connecting to Binance & Yahoo Finance API...\n";
    std::cout << "[*] Fetching live market data for your assets. Please wait a moment...\n" << Colors::RESET;

    while (!_kbhit()) {
        std::ostringstream ScreenBuffer;

        std::string UserCurrency = CurrentUser->GetCurrency();
        double DisplayMultiplier = 1.0;

        if (UserCurrency != "USD") {
            double toUsd = API.GetFiatMultiplierToUSD(UserCurrency);
            if (toUsd > 0) {
                DisplayMultiplier = 1.0 / toUsd;
            }
        }
        std::vector<MarketAsset> LiveCryptoPrices = API.FetchWalletCryptoData(cryptoSymbols);
        std::vector<MarketAsset> LiveStockPrices = API.FetchWalletStockData(stockSymbols);
        ScreenBuffer << Colors::CYAN << "========================================================================================\n" << Colors::RESET;
        ScreenBuffer << Colors::YELLOW << "                                TEX LIVE DASHBOARD                                      \n" << Colors::RESET;
        ScreenBuffer << Colors::CYAN << "========================================================================================\n" << Colors::RESET;
        ScreenBuffer << Colors::MAGENTA << " Base Currency: " << UserCurrency << " | Live Refresh: 3s\n\n" << Colors::RESET;

        ScreenBuffer << Colors::BLUE
            << std::left << std::setw(15) << "ASSET"
            << std::setw(15) << "AMOUNT"
            << std::setw(20) << "AVG PRICE"
            << std::setw(20) << "LIVE PRICE"
            << std::setw(20) << "TOTAL VALUE"
            << "PnL (%)" << "\n" << Colors::RESET;

        ScreenBuffer << "----------------------------------------------------------------------------------------------------\n";

        double TotalPortfolioValue = 0.0;
        double TotalPortfolioCost = 0.0;

        for (size_t i = 0; i < CurrentUser->GetCryptoWallet().size(); i++) {
            std::string currentSymbol = CurrentUser->GetCryptoWallet()[i].GetSymbol();
            double amount = CurrentUser->GetCryptoWallet()[i].GetAmount();
            double avgPriceUSD = CurrentUser->GetCryptoWallet()[i].GetAvaragePrice();

            double livePriceUSD = 0.0;
            std::string searchSymbol = currentSymbol + "USDT";

            for (size_t j = 0; j < LiveCryptoPrices.size(); j++) {
                if (LiveCryptoPrices[j].Symbol == searchSymbol) {
                    livePriceUSD = LiveCryptoPrices[j].CurrentPrice;
                    break;
                }
            }

            double displayLivePrice = livePriceUSD * DisplayMultiplier;
            double displayAvgPrice = avgPriceUSD * DisplayMultiplier;

            double totalValue = amount * displayLivePrice;
            double totalCost = amount * displayAvgPrice;
            TotalPortfolioValue += totalValue;
            TotalPortfolioCost += totalCost;

            double pnl = 0.0;
            if (displayAvgPrice > 0 && displayLivePrice > 0) {
                pnl = ((displayLivePrice - displayAvgPrice) / displayAvgPrice) * 100.0;
            }
            std::string PnLColor = (pnl >= 0) ? Colors::GREEN : Colors::RED;

            ScreenBuffer << PnLColor
                << std::left << std::setw(15) << ("(C) " + currentSymbol)
                << std::setw(15) << std::fixed << std::setprecision(4) << amount
                << std::setw(20) << std::fixed << std::setprecision(2) << displayAvgPrice
                << std::setw(20) << displayLivePrice
                << std::setw(20) << totalValue
                << pnl << "\n" << Colors::RESET;
        }
        for (size_t i = 0; i < CurrentUser->GetStockWallet().size(); i++) {
            std::string currentSymbol = CurrentUser->GetStockWallet()[i].GetSymbol();
            double amount = CurrentUser->GetStockWallet()[i].GetAmount();
            double avgPriceUSD = CurrentUser->GetStockWallet()[i].GetAvaragePrice();

            double livePriceRaw = 0.0;

            for (size_t j = 0; j < LiveStockPrices.size(); j++) {
                if (LiveStockPrices[j].Symbol == currentSymbol) {
                    livePriceRaw = LiveStockPrices[j].CurrentPrice;
                    break;
                }
            }

            double livePriceUSD = livePriceRaw;

            if (currentSymbol.find(".IS") != std::string::npos && livePriceRaw > 0) {
                double TryToUsdMultiplier = API.GetFiatMultiplierToUSD("TRY");
                livePriceUSD = livePriceRaw * TryToUsdMultiplier;
            }

            double displayLivePrice = livePriceUSD * DisplayMultiplier;
            double displayAvgPrice = avgPriceUSD * DisplayMultiplier;

            double totalValue = amount * displayLivePrice;
            double totalCost = amount * displayAvgPrice;
            TotalPortfolioValue += totalValue;
            TotalPortfolioCost += totalCost;

            double pnl = 0.0;
            if (displayAvgPrice > 0 && displayLivePrice > 0) {
                pnl = ((displayLivePrice - displayAvgPrice) / displayAvgPrice) * 100.0;
            }
            std::string PnLColor = (pnl >= 0) ? Colors::GREEN : Colors::RED;

            ScreenBuffer << PnLColor
                << std::left << std::setw(15) << ("(S) " + currentSymbol)
                << std::setw(15) << std::fixed << std::setprecision(4) << amount
                << std::setw(20) << std::fixed << std::setprecision(2) << displayAvgPrice
                << std::setw(20) << displayLivePrice
                << std::setw(20) << totalValue
                << pnl << "\n" << Colors::RESET;
        }

        ScreenBuffer << "----------------------------------------------------------------------------------------------------\n";
        ScreenBuffer << Colors::YELLOW << "TOTAL COST: " << std::fixed << std::setprecision(2) << TotalPortfolioCost << " " << UserCurrency << "   |   "
            << "CURRENT VALUE: " << TotalPortfolioValue << " " << UserCurrency << "\n" << Colors::RESET;

        ScreenBuffer << "To return main menu " << Colors::RED << "PRESS ANY KEY." << Colors::RESET << "\n";

        CleanScreen();
        std::cout << ScreenBuffer.str();

        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    _getch();
}
void TerminalUI::DepositAndWithdrawMenu() {
    CleanScreen();
    std::cout << Colors::CYAN << "=================================\n" << Colors::RESET;
    std::cout << Colors::YELLOW << "      CASH MANAGEMENT MENU       \n" << Colors::RESET;
    std::cout << Colors::CYAN << "=================================\n" << Colors::RESET;

    std::cout << Colors::GREEN << "[1] " << Colors::RESET << "Deposit Cash \n";
    std::cout << Colors::GREEN << "[2] " << Colors::RESET << "Withdraw Cash \n";
    std::cout << Colors::RED << "[3] " << Colors::RESET << "Back to Main Menu\n";
    std::cout << Colors::CYAN << "\nSelect an option: " << Colors::RESET;

    std::string Choice = "";
    std::getline(std::cin, Choice);

    if (Choice == "3") {
        return; 
    }

    if (Choice != "1" && Choice != "2") {
        std::cout << Colors::RED << "Invalid choice!" << Colors::RESET << "\n";
        Pause();
        return DepositAndWithdrawMenu(); 
    }

    
    std::string CurrencyInput = "";
    std::string AmountInput = "";

    std::cout << Colors::BLUE << "Enter currency code (e.g., TRY, USD): " << Colors::RESET;
    std::getline(std::cin, CurrencyInput);

    std::cout << Colors::BLUE << "Enter amount: " << Colors::RESET;
    std::getline(std::cin, AmountInput);

    double TargetAmount = 0.0;
    try {
        TargetAmount = std::stod(AmountInput);
    }
    catch (...) {
        std::cout << Colors::RED << "Invalid amount entered!" << Colors::RESET << "\n";
        Pause();
        return;
    }

    if (TargetAmount <= 0) {
        std::cout << Colors::RED << "Amount must be greater than zero!" << Colors::RESET << "\n";
        Pause();
        return;
    }

    bool Found = false;

    
    if (Choice == "1") {
        for (size_t i = 0; CurrentUser->GetCashWallet().size() > i; i++) {
            if (CurrentUser->GetCashWallet()[i].CurrencyCode == CurrencyInput) {
                CurrentUser->GetCashWallet()[i].Amount += TargetAmount;
                Found = true;
                break;
            }
        }
        if (!Found) {
            CashBalance NewCash;
            NewCash.CurrencyCode = CurrencyInput;
            NewCash.Amount = TargetAmount;
            CurrentUser->GetCashWallet().push_back(NewCash);
        }
        std::cout << Colors::GREEN << "\nSuccessfully deposited " << TargetAmount << " " << CurrencyInput << "!\n" << Colors::RESET;
    }

    
    else if (Choice == "2") {
        for (size_t i = 0; CurrentUser->GetCashWallet().size() > i; i++) {
            if (CurrentUser->GetCashWallet()[i].CurrencyCode == CurrencyInput) {
                Found = true;
                
                if (CurrentUser->GetCashWallet()[i].Amount < TargetAmount) {
                    std::cout << Colors::RED << "\nInsufficient balance! You only have "
                        << CurrentUser->GetCashWallet()[i].Amount << " " << CurrencyInput << ".\n" << Colors::RESET;
                    Pause();
                    return;
                }
                CurrentUser->GetCashWallet()[i].Amount -= TargetAmount;
                std::cout << Colors::GREEN << "\nSuccessfully withdrew " << TargetAmount << " " << CurrencyInput << "!\n" << Colors::RESET;
                break;
            }
        }
        if (!Found) {
            std::cout << Colors::RED << "\nYou don't have any " << CurrencyInput << " wallet to withdraw from!\n" << Colors::RESET;
            Pause();
            return;
        }
    }
    CurrentUser->SaveUser("Cash");
    Pause();
}
void TerminalUI::ManageAssetsMenu() {
    CleanScreen();
    std::cout << Colors::CYAN << "=================================\n" << Colors::RESET;
    std::cout << Colors::YELLOW << "       ASSET MANAGEMENT MENU     \n" << Colors::RESET;
    std::cout << Colors::CYAN << "=================================\n" << Colors::RESET;

    std::cout << Colors::GREEN << "[1] " << Colors::RESET << "Add / Update Asset \n";
    std::cout << Colors::GREEN << "[2] " << Colors::RESET << "Remove Asset \n";
    std::cout << Colors::RED << "[3] " << Colors::RESET << "Back to Main Menu\n";
    std::cout << Colors::CYAN << "\nSelect an option: " << Colors::RESET;

    std::string Choice = "";
    std::getline(std::cin, Choice);

    if (Choice == "3") {
        return;
    }
    if (Choice != "1" && Choice != "2") {
        std::cout << Colors::RED << "Invalid choice!" << Colors::RESET << "\n";
        Pause();
        return ManageAssetsMenu();
    }

    std::cout << Colors::BLUE << "Select Asset Type - [1] Crypto, [2] Stock: " << Colors::RESET;
    std::string TypeChoice = "";
    std::getline(std::cin, TypeChoice);

    if (TypeChoice != "1" && TypeChoice != "2") {
        std::cout << Colors::RED << "Invalid asset type!" << Colors::RESET << "\n";
        Pause();
        return;
    }

    bool IsCrypto = (TypeChoice == "1");

    if (Choice == "1") {
        std::string Symbol, AmountStr, PriceStr;

        std::cout << Colors::BLUE << "Enter Asset Symbol (e.g., BTC, AAPL): " << Colors::RESET;
        std::getline(std::cin, Symbol);

        if (!IsCrypto) {
            std::string ValidatedSymbol = Market.GetApiSymbol(Symbol);
            if (ValidatedSymbol == "") {
                Pause();
                return;
            }
            Symbol = ValidatedSymbol;
        }
        bool isBist = false;
        if (!IsCrypto && Symbol.find(".IS") != std::string::npos) {
            isBist = true;
        }

        std::cout << Colors::BLUE << "Enter Amount: " << Colors::RESET;
        std::getline(std::cin, AmountStr);

        if (isBist) {
            std::cout << Colors::BLUE << "Enter Average Cost (in TRY): " << Colors::RESET;
        }
        else {
            std::cout << Colors::BLUE << "Enter Average Cost (in USD): " << Colors::RESET;
        }
        std::getline(std::cin, PriceStr);

        double Amount = 0.0, AvgPrice = 0.0;
        try {
            Amount = std::stod(AmountStr);
            double RawPrice = std::stod(PriceStr);
            if (isBist) {
                APIManager API;
                double TryToUsdMultiplier = API.GetFiatMultiplierToUSD("TRY");
                AvgPrice = RawPrice * TryToUsdMultiplier; 
                std::cout << Colors::YELLOW << "[INFO] " << RawPrice << " TRY dynamically converted to "
                    << AvgPrice << " USD for internal database storage.\n" << Colors::RESET;
            }
            else {
                AvgPrice = RawPrice;
            }
        }
        catch (...) {
            std::cout << Colors::RED << "Invalid number format entered!" << Colors::RESET << "\n";
            Pause();
            return;
        }

        if (Amount <= 0 || AvgPrice < 0) {
            std::cout << Colors::RED << "Amount must be > 0 and price cannot be negative!" << Colors::RESET << "\n";
            Pause();
            return;
        }

      
        bool Found = false;
        if (IsCrypto) {
            std::string NetworkInput = "";
            std::string StakeInput = "";

            std::cout << Colors::BLUE << "Enter Network (e.g., Solana, Ethereum, BSC): " << Colors::RESET;
            std::getline(std::cin, NetworkInput);

            std::cout << Colors::BLUE << "Is this asset staked? (y/n): " << Colors::RESET;
            std::getline(std::cin, StakeInput);
            bool StakedStatus = (StakeInput == "y" || StakeInput == "Y" || StakeInput == "yes" || StakeInput == "YES" || StakeInput == "Yes");

            for (size_t i = 0; CurrentUser->GetCryptoWallet().size() > i; i++) {
                if (CurrentUser->GetCryptoWallet()[i].GetSymbol() == Symbol) {
                   
                    double oldAmount = CurrentUser->GetCryptoWallet()[i].GetAmount();
                    double oldCost = CurrentUser->GetCryptoWallet()[i].GetAvaragePrice();

                    double totalAmount = oldAmount + Amount;
                    double weightedAvgPrice = ((oldAmount * oldCost) + (Amount * AvgPrice)) / totalAmount;

                    CurrentUser->GetCryptoWallet()[i].SetAmount(totalAmount);
                    CurrentUser->GetCryptoWallet()[i].SetAvaragePrice(weightedAvgPrice);
                    CurrentUser->GetCryptoWallet()[i].SetNetwork(NetworkInput);
                    CurrentUser->GetCryptoWallet()[i].SetStakedStatus(StakedStatus);
                    Found = true;
                    break;
                }
            }
            if (!Found) {
                CurrentUser->GetCryptoWallet().push_back(Crypto(Symbol, Amount, AvgPrice,NetworkInput,StakedStatus));
            }
            CurrentUser->SaveUser("Crypto");
        }
        else {
            double DivYieldInput = 0.0;
            std::string BrokerInput = "";
            std::string IPOInput = "";

            std::cout << Colors::BLUE << "Enter Dividend Yield (%): " << Colors::RESET;
            std::string DivStr;
            std::getline(std::cin, DivStr);
            try { DivYieldInput = std::stod(DivStr); }
            catch (...) { DivYieldInput = 0.0; }

            std::cout << Colors::BLUE << "Enter Brokerage Firm (e.g., Ziraat, Midas): " << Colors::RESET;
            std::getline(std::cin, BrokerInput);

            std::cout << Colors::BLUE << "Is it a recent IPO? (y/n): " << Colors::RESET;
            std::getline(std::cin, IPOInput);
            bool IPOStatus = (IPOInput == "y" || IPOInput == "Y" || IPOInput == "yes" || IPOInput == "YES" || IPOInput == "Yes");
            for (size_t i = 0; CurrentUser->GetStockWallet().size() > i; i++) {
                if (CurrentUser->GetStockWallet()[i].GetSymbol() == Symbol) {
                    double oldAmount = CurrentUser->GetStockWallet()[i].GetAmount();
                    double oldCost = CurrentUser->GetStockWallet()[i].GetAvaragePrice();

                    double totalAmount = oldAmount + Amount;
                    double weightedAvgPrice = ((oldAmount * oldCost) + (Amount * AvgPrice)) / totalAmount;

                    CurrentUser->GetStockWallet()[i].SetAmount(totalAmount);
                    CurrentUser->GetStockWallet()[i].SetAvaragePrice(weightedAvgPrice);
                    CurrentUser->GetStockWallet()[i].SetDividendYield(DivYieldInput);
                    CurrentUser->GetStockWallet()[i].SetBroker(BrokerInput);
                    CurrentUser->GetStockWallet()[i].SetIsIPO(IPOStatus);
                    Found = true;
                    break;
                }
            }
            if (!Found) {
                CurrentUser->GetStockWallet().push_back(Stock(Symbol, Amount, AvgPrice,DivYieldInput,BrokerInput,IPOStatus));
            }
            CurrentUser->SaveUser("Stock");
        }
        std::cout << Colors::GREEN << "\nAsset successfully added/updated!\n" << Colors::RESET;
    }
    //Asset Deleting Operation....
    else if (Choice == "2") {
        std::string Symbol;
        std::cout << Colors::BLUE << "Enter Asset Symbol to remove completely: " << Colors::RESET;
        std::getline(std::cin, Symbol);

        bool Deleted = false;

        if (IsCrypto) {
            
            for (size_t i = 0; CurrentUser->GetCryptoWallet().size() > i; i++) {
                if (CurrentUser->GetCryptoWallet()[i].GetSymbol() == Symbol) {
                    CurrentUser->GetCryptoWallet().erase(CurrentUser->GetCryptoWallet().begin() + i);

                    Deleted = true;
                    break; 
                }
            }
            CurrentUser->SaveUser("Crypto");
        }
        else {
            for (size_t i = 0; CurrentUser->GetStockWallet().size() > i; i++) {
                if (CurrentUser->GetStockWallet()[i].GetSymbol() == Symbol) {

                    CurrentUser->GetStockWallet().erase(CurrentUser->GetStockWallet().begin() + i);

                    Deleted = true;
                    break;
                }
            }
            CurrentUser->SaveUser("Stock");
        }

        if (Deleted) {
            std::cout << Colors::GREEN << "\nAsset " << Symbol << " removed from wallet!\n" << Colors::RESET;
        }
        else {
            std::cout << Colors::RED << "\nAsset not found in your wallet!\n" << Colors::RESET;
        }
    }

    Pause();
}
void TerminalUI::TradeMarketMenu() {
    CleanScreen();
    std::cout << Colors::CYAN << "=================================\n" << Colors::RESET;
    std::cout << Colors::YELLOW << "       TRADE MARKET (BUY/SELL)   \n" << Colors::RESET;
    std::cout << Colors::CYAN << "=================================\n" << Colors::RESET;

    std::cout << Colors::GREEN << "[1] " << Colors::RESET << "Buy Asset\n";
    std::cout << Colors::GREEN << "[2] " << Colors::RESET << "Sell Asset\n";
    std::cout << Colors::RED << "[3] " << Colors::RESET << "Back to Main Menu\n";
    std::cout << Colors::CYAN << "\nSelect an option: " << Colors::RESET;

    std::string Choice = "";
    std::getline(std::cin, Choice);

    if (Choice == "3") return;

    if (Choice != "1" && Choice != "2") {
        std::cout << Colors::RED << "Invalid choice!" << Colors::RESET << "\n";
        Pause();
        return TradeMarketMenu();
    }

    std::cout << Colors::BLUE << "Select Asset Type - [1] Crypto, [2] Stock: " << Colors::RESET;
    std::string TypeChoice = "";
    std::getline(std::cin, TypeChoice);

    if (TypeChoice != "1" && TypeChoice != "2") {
        std::cout << Colors::RED << "Invalid asset type!" << Colors::RESET << "\n";
        Pause();
        return;
    }

    bool IsCrypto = (TypeChoice == "1");
    APIManager API;

    // --- SATIN ALMA (BUY) ÝÞLEMÝ ---
    if (Choice == "1") {
        std::string BaseFiat, TargetAsset, SpendAmountStr;

        std::cout << Colors::BLUE << "Which fiat/cash will you use? (e.g., USDT, TRY): " << Colors::RESET;
        std::getline(std::cin, BaseFiat);

        int CashIndex = -1;
        for (size_t i = 0; CurrentUser->GetCashWallet().size() > i; i++) {
            if (CurrentUser->GetCashWallet()[i].CurrencyCode == BaseFiat) {
                CashIndex = i;
                break;
            }
        }

        if (CashIndex == -1 || CurrentUser->GetCashWallet()[CashIndex].Amount <= 0) {
            std::cout << Colors::RED << "\n[ERROR] You don't have any " << BaseFiat << " in your wallet!\n" << Colors::RESET;
            Pause();
            return;
        }

        std::cout << Colors::BLUE << "Enter the symbol of the asset you want to buy (e.g., BTC or AAPL): " << Colors::RESET;
        std::getline(std::cin, TargetAsset);

        if (!IsCrypto) {
            std::string ValidatedTarget = Market.GetApiSymbol(TargetAsset);
            if (ValidatedTarget == "") {
                Pause();
                return;
            }
            TargetAsset = ValidatedTarget; 
        }

        double LivePrice = 0.0;
        if (IsCrypto) {
            std::string PairSymbol = TargetAsset + BaseFiat;
            LivePrice = API.FetchCryptoPrice(PairSymbol);
        }
        else {
            LivePrice = API.FetchStockPrice(TargetAsset);
        }

        if (LivePrice <= 0) {
            std::cout << Colors::YELLOW << "\n[INFO] API could not fetch live price." << Colors::RESET << "\n";
            std::cout << Colors::BLUE << "Please enter the current market price manually (in " << BaseFiat << "): " << Colors::RESET;
            std::string ManualPriceStr;
            std::getline(std::cin, ManualPriceStr);
            try { LivePrice = std::stod(ManualPriceStr); }
            catch (...) { LivePrice = 0; }

            if (LivePrice <= 0) {
                std::cout << Colors::RED << "\n[ERROR] Invalid price entered!\n" << Colors::RESET;
                Pause();
                return;
            }
        }

        std::cout << Colors::YELLOW << "\n--- LIVE MARKET ---\n" << Colors::RESET;
        std::cout << TargetAsset << " Price: " << Colors::GREEN << LivePrice << " " << BaseFiat << Colors::RESET << "\n";
        std::cout << "Available Balance: " << CurrentUser->GetCashWallet()[CashIndex].Amount << " " << BaseFiat << "\n";

        std::cout << Colors::BLUE << "How much " << BaseFiat << " do you want to spend?: " << Colors::RESET;
        std::getline(std::cin, SpendAmountStr);

        double SpendAmount = 0.0;
        try { SpendAmount = std::stod(SpendAmountStr); }
        catch (...) { SpendAmount = 0; }

        if (SpendAmount <= 0 || SpendAmount > CurrentUser->GetCashWallet()[CashIndex].Amount) {
            std::cout << Colors::RED << "\n[ERROR] Insufficient balance or invalid amount!\n" << Colors::RESET;
            Pause();
            return;
        }

        double AssetBought = SpendAmount / LivePrice;
        CurrentUser->GetCashWallet()[CashIndex].Amount -= SpendAmount;

        bool FoundAsset = false;

        if (IsCrypto) {
            for (size_t i = 0; CurrentUser->GetCryptoWallet().size() > i; i++) {
                if (CurrentUser->GetCryptoWallet()[i].GetSymbol() == TargetAsset) {
                    double oldAmount = CurrentUser->GetCryptoWallet()[i].GetAmount();
                    double oldCost = CurrentUser->GetCryptoWallet()[i].GetAvaragePrice();

                    double totalAmount = oldAmount + AssetBought;
                    double weightedAvgPrice = ((oldAmount * oldCost) + SpendAmount) / totalAmount;

                    CurrentUser->GetCryptoWallet()[i].SetAmount(totalAmount);
                    CurrentUser->GetCryptoWallet()[i].SetAvaragePrice(weightedAvgPrice);
                    FoundAsset = true;
                    break;
                }
            }
            if (!FoundAsset) {
                Crypto NewCrypto(TargetAsset, AssetBought, LivePrice, "Default", false);
                CurrentUser->GetCryptoWallet().push_back(NewCrypto);
            }
            CurrentUser->SaveUser("Crypto");
        }
        else {
            for (size_t i = 0; CurrentUser->GetStockWallet().size() > i; i++) {
                if (CurrentUser->GetStockWallet()[i].GetSymbol() == TargetAsset) {
                    double oldAmount = CurrentUser->GetStockWallet()[i].GetAmount();
                    double oldCost = CurrentUser->GetStockWallet()[i].GetAvaragePrice();

                    double totalAmount = oldAmount + AssetBought;
                    double weightedAvgPrice = ((oldAmount * oldCost) + SpendAmount) / totalAmount;

                    CurrentUser->GetStockWallet()[i].SetAmount(totalAmount);
                    CurrentUser->GetStockWallet()[i].SetAvaragePrice(weightedAvgPrice);
                    FoundAsset = true;
                    break;
                }
            }
            if (!FoundAsset) {
                Stock NewStock(TargetAsset, AssetBought, LivePrice, 0.0, "Unknown Broker", false);
                CurrentUser->GetStockWallet().push_back(NewStock);
            }
            CurrentUser->SaveUser("Stock");
        }

        CurrentUser->SaveUser("Cash");
        std::cout << Colors::GREEN << "\n[SUCCESS] Bought " << AssetBought << " " << TargetAsset << " for "
            << SpendAmount << " " << BaseFiat << "!\n" << Colors::RESET;
    }
 
    else if (Choice == "2") {
        std::string TargetAsset, BaseFiat, SellAmountStr;

        std::cout << Colors::BLUE << "Enter the symbol of the asset you want to sell (e.g., BTC or AAPL): " << Colors::RESET;
        std::getline(std::cin, TargetAsset);

        if (!IsCrypto) {
            std::string ValidatedTarget = Market.GetApiSymbol(TargetAsset);
            if (ValidatedTarget == "") {
                Pause();
                return;
            }
            TargetAsset = ValidatedTarget; 
        }

        int AssetIndex = -1;
        double AvailableAsset = 0.0;

        if (IsCrypto) {
            for (size_t i = 0; CurrentUser->GetCryptoWallet().size() > i; i++) {
                if (CurrentUser->GetCryptoWallet()[i].GetSymbol() == TargetAsset) {
                    AssetIndex = i;
                    AvailableAsset = CurrentUser->GetCryptoWallet()[i].GetAmount();
                    break;
                }
            }
        }
        else {
            for (size_t i = 0; CurrentUser->GetStockWallet().size() > i; i++) {
                if (CurrentUser->GetStockWallet()[i].GetSymbol() == TargetAsset) {
                    AssetIndex = i;
                    AvailableAsset = CurrentUser->GetStockWallet()[i].GetAmount();
                    break;
                }
            }
        }

        if (AssetIndex == -1 || AvailableAsset <= 0) {
            std::cout << Colors::RED << "\n[ERROR] You don't have any " << TargetAsset << " to sell!\n" << Colors::RESET;
            Pause();
            return;
        }

        std::cout << Colors::BLUE << "Which fiat/cash do you want to receive? (e.g., USDT): " << Colors::RESET;
        std::getline(std::cin, BaseFiat);

        double LivePrice = 0.0;
        if (IsCrypto) {
            std::string PairSymbol = TargetAsset + BaseFiat;
            LivePrice = API.FetchCryptoPrice(PairSymbol);
        }
        else {
            LivePrice = API.FetchStockPrice(TargetAsset);
        }

        if (LivePrice <= 0) {
            std::cout << Colors::YELLOW << "\n[INFO] API could not fetch live price." << Colors::RESET << "\n";
            std::cout << Colors::BLUE << "Please enter the current market price manually (in " << BaseFiat << "): " << Colors::RESET;
            std::string ManualPriceStr;
            std::getline(std::cin, ManualPriceStr);
            try { LivePrice = std::stod(ManualPriceStr); }
            catch (...) { LivePrice = 0; }

            if (LivePrice <= 0) {
                std::cout << Colors::RED << "\n[ERROR] Invalid price entered!\n" << Colors::RESET;
                Pause();
                return;
            }
        }

        std::cout << Colors::YELLOW << "\n--- LIVE MARKET ---\n" << Colors::RESET;
        std::cout << TargetAsset << " Price: " << Colors::GREEN << LivePrice << " " << BaseFiat << Colors::RESET << "\n";
        std::cout << "Available Amount: " << AvailableAsset << " " << TargetAsset << "\n";

        std::cout << Colors::BLUE << "How much " << TargetAsset << " do you want to sell?: " << Colors::RESET;
        std::getline(std::cin, SellAmountStr);

        double SellAmount = 0.0;
        try { SellAmount = std::stod(SellAmountStr); }
        catch (...) { SellAmount = 0; }

        if (SellAmount <= 0 || SellAmount > AvailableAsset) {
            std::cout << Colors::RED << "\n[ERROR] Invalid amount or insufficient balance!\n" << Colors::RESET;
            Pause();
            return;
        }

        double FiatGained = SellAmount * LivePrice;

        if (IsCrypto) {
            if (SellAmount == AvailableAsset) {
                CurrentUser->GetCryptoWallet().erase(CurrentUser->GetCryptoWallet().begin() + AssetIndex);
            }
            else {
                double remaining = AvailableAsset - SellAmount;
                CurrentUser->GetCryptoWallet()[AssetIndex].SetAmount(remaining);
            }
            CurrentUser->SaveUser("Crypto");
        }
        else {
            if (SellAmount == AvailableAsset) {
                CurrentUser->GetStockWallet().erase(CurrentUser->GetStockWallet().begin() + AssetIndex);
            }
            else {
                double remaining = AvailableAsset - SellAmount;
                CurrentUser->GetStockWallet()[AssetIndex].SetAmount(remaining);
            }
            CurrentUser->SaveUser("Stock");
        }

        bool FoundCash = false;
        for (size_t i = 0; CurrentUser->GetCashWallet().size() > i; i++) {
            if (CurrentUser->GetCashWallet()[i].CurrencyCode == BaseFiat) {
                CurrentUser->GetCashWallet()[i].Amount += FiatGained;
                FoundCash = true;
                break;
            }
        }

        if (!FoundCash) {
            CashBalance NewCash;
            NewCash.CurrencyCode = BaseFiat;
            NewCash.Amount = FiatGained;
            CurrentUser->GetCashWallet().push_back(NewCash);
        }

        CurrentUser->SaveUser("Cash");
        std::cout << Colors::GREEN << "\n[SUCCESS] Sold " << SellAmount << " " << TargetAsset << " and gained "
            << FiatGained << " " << BaseFiat << "!\n" << Colors::RESET;
    }

    Pause();
}
void TerminalUI::SettingsMenu() {
    CleanScreen();
    std::cout << Colors::CYAN << "=================================\n" << Colors::RESET;
    std::cout << Colors::YELLOW << "         SETTINGS MENU           \n" << Colors::RESET;
    std::cout << Colors::CYAN << "=================================\n" << Colors::RESET;
    std::cout << "Current Display Currency: " << Colors::GREEN << CurrentUser->GetCurrency() << Colors::RESET << "\n\n";

    std::cout << Colors::GREEN << "[1] " << Colors::RESET << "Change Display Currency\n";
    std::cout << Colors::RED << "[2] " << Colors::RESET << "DANGER: Reset Entire Portfolio\n";
    std::cout << Colors::GREEN << "[3] " << Colors::RESET << "Back to Main Menu\n";
    std::cout << Colors::CYAN << "\nSelect an option: " << Colors::RESET;

    std::string Choice = "";
    std::getline(std::cin, Choice);

    if (Choice == "3") {
        return;
    }
    if (Choice == "1") {
        std::cout << Colors::BLUE << "\nEnter new display currency (e.g., USD, TRY, EUR): " << Colors::RESET;
        std::string NewCurrency = "";
        std::getline(std::cin, NewCurrency);

        if (NewCurrency != "") {
            for (size_t i = 0; i < NewCurrency.length(); i++) {
                if (NewCurrency[i] >= 'a' && NewCurrency[i] <= 'z') {
                    NewCurrency[i] = NewCurrency[i] - 32;
                }
            }

            CurrentUser->SetCurrency(NewCurrency);
            CurrentUser->SaveUser("Settings");
            std::cout << Colors::GREEN << "\n[SUCCESS] Display currency updated to " << NewCurrency << "!\n" << Colors::RESET;
        }
    }
    else if (Choice == "2") {
        std::cout << Colors::BG_RED << Colors::WHITE << "\n WARNING: THIS WILL DELETE ALL ASSETS AND CASH IN YOUR ACCOUNT! " << Colors::RESET << "\n";
        std::cout << Colors::RED << "Are you absolutely sure you want to reset your portfolio? (Type 'YES' to confirm): " << Colors::RESET;

        std::string Confirm = "";
        std::getline(std::cin, Confirm);

        if (Confirm == "YES") {
            CurrentUser->GetCryptoWallet().clear();
            CurrentUser->GetStockWallet().clear();
            CurrentUser->GetCashWallet().clear();

            CurrentUser->SaveUser("Crypto");
            CurrentUser->SaveUser("Stock");
            CurrentUser->SaveUser("Cash");

            std::cout << Colors::GREEN << "\n[SUCCESS] Portfolio has been completely wiped clean! You have $0.00.\n" << Colors::RESET;
        }
        else {
            std::cout << Colors::YELLOW << "\n[INFO] Portfolio reset cancelled. Your assets are safe.\n" << Colors::RESET;
        }
    }
    else {
        std::cout << Colors::RED << "Invalid choice!" << Colors::RESET << "\n";
    }

    Pause();
}