#include <iostream>

void greet(std::string name = "Guest", std::string greet = "Hello") {
    std::cout << greet << ", " << name << "!";
}

int main()
{
    while (true) {
        std::cout << "1. Default greeting\n";
        std::cout << "2. Greet by name\n";
        std::cout << "3. Custom name and greeting\n";
        std::cout << "Select 1-3: ";

        int choice;

        std::cin >> choice;

        if (choice == 1) {
            greet();
            break;
        }
        else if (choice == 2) {
            std::cout << "Name: ";
            std::string name;
            std::cin >> name;
            greet(name);
            break;
        }
        else if (choice == 3) {
            std::cout << "Name: ";
            std::string name;
            std::cin >> name;
            std::cout << "Greeting: ";
            std::string greeting;
            std::cin >> greeting;
            greet(name, greeting);
            break;
        }
    }
}