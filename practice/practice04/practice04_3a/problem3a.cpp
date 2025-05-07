#include <iostream>
#include <list>
#include <string>

void showTasks(const std::list<std::string>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks to display.\n";
        return;
    }

    std::cout << "\nTasks:\n";
    int taskNumber = 1;
    for (const auto& task : tasks) {
        std::cout << taskNumber++ << ". " << task << '\n';
    }
    std::cout << std::endl;
}

void removeTask(std::list<std::string>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks to remove.\n";
        return;
    }

    int taskNumber;
    showTasks(tasks);
    std::cout << "Enter task number to remove: ";
    std::cin >> taskNumber;

    if (taskNumber < 1 || taskNumber > tasks.size()) {
        std::cout << "Invalid task number.\n";
        return;
    }

    auto it = tasks.begin();
    std::advance(it, taskNumber - 1);
    tasks.erase(it);

    std::cout << "Task removed!\n";
}

int main() {
    std::list<std::string> tasks;
    int choice;

    do {
        std::cout << "1. Add Task\n";
        std::cout << "2. Remove Task\n";
        std::cout << "3. Show Tasks\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            std::string task;
            std::cout << "Enter task: ";
            std::getline(std::cin, task);
            tasks.push_back(task);
            std::cout << "Task added!\n";
            break;
        }
        case 2:
            removeTask(tasks);
            break;
        case 3:
            showTasks(tasks);
            break;
        case 4:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}