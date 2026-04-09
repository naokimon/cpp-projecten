#include <iostream>

int main() {
    int a, b;
    char op;
    int sum;

    std::cout << "Enter your first number: ";
    std::cin >> a;

    std::cout << "Enter your second number: ";
    std::cin >> b;

    std::cout << "Choose operator: ";
    std::cin >> op;

    switch (op) {
        case '+':
            sum = a + b;
            break;
        case '-':
            sum = a - b;
            break;
        case '*':
            sum = a * b;
            break;
        case '/':
            sum = a / b;
            break;
        case '%':
            sum = a % b;
            break;
        default:
            std::cout << "Unknown operator.";
            return 1;
    }

    std::cout << a << op << b << "=" << sum;
    
    int finish;
    std::cin >> finish;
    
    return 0;
}