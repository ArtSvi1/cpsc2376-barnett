#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

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

int main()
{
    return 0;
}