#include "TerminalUI.h"
#include "MarketManager.h"
#include <iostream>
#include "Convert.h"
int main() {
     ConvertTxtToBinary();
    
     MarketManager CoreMarket;

    CoreMarket.LoadDatabaseFromBinary();
   
    TerminalUI TexTerminal(CoreMarket, nullptr);


    TexTerminal.Start();

    return 0;
}