#include <iostream>
#include <fstream>
#include "json.hpp"
#include "bankaccount.h"

using json = nlohmann::json;

inline bool exists (const std::string& name) {
    std::ifstream file(name);
    if (file.is_open()) {
        return true;
    }
    std::ofstream newFile(name);
    newFile << "{}";
    return false;
}

void await() {
    std::cin.ignore();
    std::cin.get();
}

int accountRegister() {
    system("CLS");
    if (exists("users.json")) {
        std::cout << "User data found! Press enter to continue" << std::endl;
        await();
    } else {
        std::cout << "User data not found. Creating data..." << std::endl;
        await();
    }
    
    system("CLS");
    json j;

    std::string username;
    while (true) {
        std::cout << "Enter your username:" << std::endl;
        std::cin >> username;
        std::ifstream inFile("users.json");
        if (inFile.is_open() && inFile.peek() != std::ifstream::traits_type::eof()) {
            inFile >> j;
        }
        inFile.close();
        bool usernameTaken = false;
        for (auto& [key, user] : j.items()) {
            if (user["username"] == username) {
                std::cout << "Username was already taken!" << std::endl;
                usernameTaken = true;
            }
        }

        if (!usernameTaken) {
            break;
        }
    }

    std::string password;
    while (true) {
        std::cout << "Enter your password:" << std::endl;
        std::cin >> password;

        std::string confirmPassword;
        std::cout << "Confirm password:" << std::endl;
        std::cin >> confirmPassword;

        if (password == confirmPassword) {
            break;
        } else {
            std::cout << "Passwords do not match." << std::endl;
        }
    }

    std::string accountHolderName;
    while (true) {
        std::string firstName;
        while (true) {
            std::cout << "Enter your first name:" << std::endl;
            std::cin >> firstName;
            std::cin.ignore();
            if (firstName.length() == 0) {
                std::cout << "Please enter a name." << std::endl;
            } else {
                break;
            }
        }

        std::string lastName;
        while (true) {
            std::cout << "Enter your last name:" << std::endl;
            std::getline(std::cin, lastName);
            if (lastName.length() == 0) {
                std::cout << "Please enter a last name." << std::endl;
            } else {
                break;
            }
        }
        
        accountHolderName = firstName + " " + lastName;
        break;
    }

    long long balance;
    while (true) {
        std::cout << "Enter your initial deposit:" << std::endl;
        if (!(std::cin >> balance)) {
            std::cout << "Invalid amount.";
        } else {
            break;
        }
    }

    BankAccount newAccount(username, password, accountHolderName, balance);

    newAccount.saveToJSON();
    std::cout << "Registered succesfully!";
    await();

    return 0;
}

int accountLogin() {
    system("CLS");

    std::ifstream file("users.json");

    json j = json::parse(file);
    
    while (true) {
        std::cout << "Enter your username:" << std::endl;
        std::string username;
        std::cin >> username;

        std::cout << "Enter your password:" << std::endl;
        std::string password;
        std::cin >> password;
        
        bool login = false;

        for (auto& [key, user] : j.items()) {
            if (user["username"] == username && user["password"] == password) {
                login = true;
            }
        }
        
        if (login == true) {
            std::cout << "Login succesfull!";
            await();
            system("CLS");
            break;
        } else {
            std::cout << "Invalid login!";
            await();
            system("CLS");
        }
    }
    return 0;
}

int main() {
    while (true) {
        system("CLS");
        int choice;
        std::cout << "Would you like to login or register?\n1.Login\n2.Register\n3.Exit\n";

        while (true) {
            std::cin >> choice;
            if (choice == 1) {
                accountLogin();
                break;
            } else if (choice == 2) {
                accountRegister();
                break;
            } else if (choice == 3) {
                abort();
            } else {
                std::cout << "Invalid option\n";
            }
        }
    }
    return 0;
}
