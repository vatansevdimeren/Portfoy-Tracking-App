#include "TerminalUI.h"
#include "ConsoleColors.h"
#include "User.h"
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
        return ShowFirstTerminalMenu();//recursion tuzağına burada düşmez eğer aşırı salak değilse kullanıcı yani maymun olması lazım
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
                User* CurrentUserT = User::LogIn();
                if (CurrentUser != nullptr) {
                    std::cout << Colors::GREEN << "\nLogin Successful!" << Colors::RESET << "\n";
                    this->CurrentUser = CurrentUserT;
                    Pause();
                }
                break;
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
           
        }
    }
}