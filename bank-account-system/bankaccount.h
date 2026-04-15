#include <iostream>
#include <iomanip>
#include <sstream>
#include "json.hpp"
#include <fstream>

class BankAccount {
    private:
        std::string username;
        std::string password;
        std::string accountHolderName;
        long long balance = 0;
    public:
    BankAccount() {
        username = "Unknown";
        password = "Password";
        accountHolderName = "Unknown";
        balance = 0;
    }

    BankAccount(std::string Username, std::string Password, std::string holderName, long long InitialDeposit) {
        username = Username;
        password = Password;
        accountHolderName = holderName;
        balance = InitialDeposit;
    }

    void saveToJSON() {
        nlohmann::json j;
        std::ifstream inFile("users.json");

        if (inFile.is_open() && inFile.peek() != std::ifstream::traits_type::eof()) {
            inFile >> j;
        }
        inFile.close();

        j[std::to_string(j.size() + 1)] = {{"username", username}, {"password", password}, {"accountHolderName", accountHolderName}, {"balance", balance}};
        std::ofstream outFile("users.json");
        outFile << j.dump(4);
        outFile.close();
        
    }

    void deposit(int amount) {
        balance += amount;
    }

    void withdraw(int amount) {
        balance -= amount;
    }

    std::string getAccountHolderName() {
        return accountHolderName;
    }
    
    std::string getUsername() {
        return username;
    }

    std::string getBalance() {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << balance / 100.00;
        return oss.str();
    }

    void accountMenu(BankAccount account) {
        std::cout << "Menu" << std::endl;
        std::cout << "--------------------------------" << std::endl;
        std::cout << "Username: " << account.getUsername() << std::endl;
        std::cout << "Account Holder: " << account.getAccountHolderName() << std::endl;
        std::cout << "Account Balance: $" << account.getBalance() << std::endl;
        std::cout << "--------------------------------" << std::endl;
    }
};