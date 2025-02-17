#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

double getDouble(const std::string& prompt) {
    double input;

    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                '\n');
            std::cout << "Invalid input. Please enter a float number.\n";
        }
        else if (input < 0) {
            std::cout << "Invalid input. Please enter a positive float number.\n";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }
    }
}

int getInt(const std::string& prompt) {
    int input;

    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || input <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a positive integer.\n";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }
    }
}

void checkFile()
{
    std::ifstream fin{ "account_balance.txt" };
    if (fin)
    {
        std::string balance;
        fin >> balance;
        std::cout << "Your current balance is: " << balance << std::endl;
    }
    else
    {
        fin.close();
        std::ofstream fout{ "account_balance.txt" };
        if (!fout)
        {
            std::cerr << "File failed to open.\n";
            return;
        }
        else
        {
            fout << "$100.00";
            std::cout << "Initializing account with $100.00...\n" << std::endl;
            fout.close();
        }
    }
}

void checkBalance()
{
    std::ifstream fin{ "account_balance.txt" };
    if (!fin)
    {
        std::cerr << "File failed to open.";
        return;
    }
    std::string balance;
    fin >> balance;
    fin.close();

    std::cout << "Your current balance is: " << balance << std::endl;
}

void deposit(double depo)
{
    std::ifstream fin{ "account_balance.txt" };
    if (!fin)
    {
        std::cerr << "File failed to open.";
        return;
    }
    std::string b;
    fin >> b;
    fin.close();
    double balance = 0;
    balance = std::stod(&b[1]);

    if (depo <= 0)
    {
        std::cout << "Deposit must be positive." << std::endl;
    }
    else
    {
        double newBalance = balance + depo;
        std::ofstream fout{ "account_balance.txt" };
        fout << "$" << std::fixed << std::setprecision(2) << newBalance;
        fout.close();
        std::cout << "Deposit successful. Your new balance is: $" << std::fixed << std::setprecision(2) << newBalance << std::endl;
    }
}

void withdraw(double with)
{
    std::ifstream fin{ "account_balance.txt" };
    if (!fin)
    {
        std::cerr << "File failed to open.";
        return;
    }
    std::string b;
    fin >> b;
    fin.close();
    double balance = 0;
    balance = std::stod(&b[1]);
    if (with > balance)
    {
        std::cout << "Insufficient funds. Your balance is: " << b << std::endl;
    }
    else if (with <= 0) 
    {
        std::cout << "Withdrawal must be positive." << std::endl;
    }
    else
    {
        double newBalance = balance - with;
        std::ofstream fout{ "account_balance.txt" };
        fout << "$" << std::fixed << std::setprecision(2) << newBalance;
        fout.close();
        std::cout << "Withdrawal successful. Your new balance is: $" << std::fixed << std::setprecision(2) << newBalance << std::endl;
    }
}

int main()
{
    while (true)
    {
        std::cout << "\nWelcome to Your Bank Account!\n";
        checkFile();
        std::cout << "\nMenu:\n";
        std::cout << "1. Check Balance\n";
        std::cout << "2. Deposit Money\n";
        std::cout << "3. Withdraw Money\n";
        std::cout << "4. Exit\n";

        int choice = getInt("Enter your choice: ");

        if (choice < 1 || choice > 4)
        {
            std::cout << "Invalid input. Please select a number 1-4.";
            continue;
        }

        if (choice == 1)
        {
            checkBalance();
        }

        if (choice == 2)
        {
            double depo = getDouble("Enter deposit amount: ");
            deposit(depo);
        }

        if (choice == 3)
        {
            double with = getDouble("Enter withdrawal amount: ");
            withdraw(with);
        }

        if (choice == 4)
        {
            std::cout << "Exiting...";
            break;
        }
    }
    return 0;
}