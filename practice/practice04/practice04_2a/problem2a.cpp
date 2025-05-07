#include <iostream>
#include <string>
#include <limits>
template <typename T> 
T calculate(T num1, T num2, char operation) {

	if (operation == '+') {
        return num1 + num2;
	}
    else if (operation == '-') {
        return num1 - num2;
    }
    else if (operation == '*') {
        return num1 * num2;
    }
    else if (operation == '/') {
        if (num2 != 0) {
            return num1 / num2;
        }
        else {
            std::cout << "Error: Division by zero!" << std::endl;
            return 0;
        }
    }
    else {
        std::cout << "Invalid operation!";
        return 0;
    }
}
int main() {
    std::string input;
    std::cout << "Enter first number: ";
    std::getline(std::cin, input);

    bool isDouble = input.find('.') != std::string::npos;
    double firstNumber = (isDouble) ? std::stod(input) : std::stoi(input);

    std::cout << "Enter second number: ";
    std::getline(std::cin, input);
    isDouble = input.find('.') != std::string::npos;
    double secondNumber = (isDouble) ? std::stod(input) : std::stoi(input);

    std::cout << "Enter operation (+, -, *, /): ";
    char operation;
    std::cin >> operation;

    if (isDouble) {
        double result = calculate(firstNumber, secondNumber, operation);
        std::cout << "Result: " << result << std::endl;
    }
    else {
        int result = calculate(static_cast<int>(firstNumber), static_cast<int>(secondNumber), operation);
        std::cout << "Result: " << result << std::endl;
    }

    return 0;
}
