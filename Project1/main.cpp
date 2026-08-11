#include "TerminalUI.h"
#include "MarketManager.h"
#include <iostream>

int main() {
    // 1. Piyasa yoneticisini (Arka plan motorunu) baslat
    MarketManager CoreMarket;

    // 2. Arayuzu (Terminali) baslat. Baslangicta giris yapmis kullanici yok (nullptr)
    TerminalUI TexTerminal(CoreMarket, nullptr);

    // 3. Kontagi cevir ve Terminali atesle!
    TexTerminal.Start();

    return 0;
}