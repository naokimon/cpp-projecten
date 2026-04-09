    #include <iostream>
    #include <fstream>
    #include "json.hpp"

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

    int userRegister() {
        system("CLS");
        if (exists("users.json")) {
            std::cout << "User data found! Press enter to continue" << std::endl;
            std::cin.ignore();
            std::cin.get();
        } else {
            std::cout << "User data not found. Creating data..." << std::endl;
            std::cin.ignore();
            std::cin.get();
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
            std:: cin >> password;

            std::string confirmPassword;
            std::cout << "Confirm password:" << std::endl;
            std::cin >> confirmPassword;

            if (password == confirmPassword) {
                break;
            } else {
                std::cout << "Passwords do not match." << std::endl;
            }
        }


        std::ifstream inFile("users.json");

        if (inFile.is_open() && inFile.peek() != std::ifstream::traits_type::eof()) {
            inFile >> j;
        }
        inFile.close();

        j[std::to_string(j.size() + 1)] = {{"password", password}, {"username", username}};
        std::ofstream outFile("users.json");
        outFile << j.dump(2);
        outFile.close();
        std::cout << "Registered succesfully" << std::endl;
        std::cin.ignore();
        std::cin.get(); 
        return 0;
    }

    int userLogin() {
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
                std::cin.ignore();
                std::cin.get();
                system("CLS");
                break;
            } else {
                std::cout << "Invalid login!";
                std::cin.ignore();
                std::cin.get();
                system("CLS");
            }
        }
        return 0;
    }

    int main() {
        system("CLS");
        int choice;
        std::cout << "Would you like to login or register?\n1.Login\n2.Register\n";

        while (true) {
            std::cin >> choice;
            if (choice == 1) {
                userLogin();
                break;
            } else if (choice == 2) {
                userRegister();
                break;
            } else {
                std::cout << "Invalid option\n";
            }
        }
        return 0;
    }
