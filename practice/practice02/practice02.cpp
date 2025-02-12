#include <iostream>
#include <fstream>
#include <iomanip>

double checkBalance()
{
    std::ifstream fin{ "account_balance.txt" };
    if (!fin)
    {
        std::cerr << "File failed to open.";
        return;
    }
    std::string balance;
    fin >> balance;

    std::cout << "Your current balance is: " << balance << std::endl;
}

void withdraw()
{

}

void deposit()
{

}

int main()
{
    std::ofstream fout{ "account_balance.txt" };
    fout << "$100.00";
    return 0;
}