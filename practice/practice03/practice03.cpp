// practice03.cpp (Buggy Code to be tested)
#include <iostream>
#include <vector>
#include <climits>

class MathUtils {
public:
    static int sumRange(int start, int end) {
        int sum = 0;
        for (int i = start; i <= end; i++) {
            sum += i;
        }
        return sum;
    }

    static bool containsNegative(const std::vector<int>& numbers) {
        if (numbers.empty()) {
            std::cerr << "Error: The input vector is empty." << std::endl;
            return false;
        }

        for (size_t i = 0; i < numbers.size(); i++) {
            if (numbers[i] < 0) {
                return true;
            }
        }
        return false;
    }

    static int findMax(const std::vector<int>& numbers) {
        if (numbers.empty()) {
            std::cerr << "Error: The input vector is empty." << std::endl;
            return INT_MIN;
        }
        int maxVal = numbers[0];
        for (size_t i = 1; i <= numbers.size(); i++) { // Bug
            if (numbers[i] >= maxVal) { // Bug
                maxVal = numbers[i];
            }
        }
        return maxVal;
    }
};

int main() {
    std::cout << "Sum from 1 to 5: " << MathUtils::sumRange(1, 5) << std::endl;
    std::vector<int> values = { 3, -1, 5, 7 };
    std::cout << "Contains negative? " << MathUtils::containsNegative(values) << std::endl;
    if (MathUtils::findMax(values) == INT_MIN) {
        std::cout << "Max value could not be determined." << std::endl;
    }
    else {
        std::cout << "Max value: " << MathUtils::findMax(values) << std::endl;
    }
    return 0;
}