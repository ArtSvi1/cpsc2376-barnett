#include <iostream>
#include <vector>

void addNum(std::vector<int>& nums)
{
	std::cout << "Integer: ";
	int num;
	while (!(std::cin >> num)) 
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Please enter an integer: ";
	}
	nums.push_back(num);
	std::cout << "Number successfuly added to vector!" << std::endl;
}

void printVec(const std::vector<int>& nums)
{
	if (nums.empty())
	{
		std::cout << "Your vector is currently empty!" << std::endl;
	}
	else
	{
		int index = 1;
		for (const auto& num : nums)
		{
			std::cout << "Number " << index << ": " << num << std::endl;
			index++;
		}
	}
}

void doubleVec(std::vector<int>& nums)
{
	if (nums.empty())
	{
		std::cout << "Your vector is currently empty!" << std::endl;
	}
	else
	{
		for (auto& num : nums)
		{
			num *= 2;
		}
		std::cout << "Numbers successfully doubled!" << std::endl;
	}
	
}

void sumVec(const std::vector<int>& nums)
{
	if (nums.empty())
	{
		std::cout << "Your vector is currently empty!" << std::endl;
	}
	else
	{
		int sum = 0;
		for (const auto& num : nums)
		{
			sum += num;
		}
		std::cout << "Sum of numbers in vector: " << sum << std::endl;
	}
}

void vecMultiples(const std::vector<int>& nums)
{
	if (nums.empty())
	{
		std::cout << "Your vector is currently empty!" << std::endl;
	}
	else
	{
		std::cout << "Enter a number: ";
		int multiple;

		while (!(std::cin >> multiple))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter an integer: ";
		}
		std::cout << "Multiples: " << std::endl;
		int count = 0;

		for (const auto& num : nums)
		{
			if (multiple % num == 0)
			{
				std::cout << num << std::endl;
				count++;
			}
		}
		if (count == 0)
		{
			std::cout << "No multiples found." << std::endl;
		}
	}
}

int main()
{
	std::vector<int> nums;
	int choice;

	while (true)
	{
		std::cout << 
			"\nMenu Options:\n"
			"1. Add integer to vector\n"
			"2. Print vector\n"
			"3. Double vector\n"
			"4. Sum of vector\n"
			"5. Check multiples from vector\n"
			"6. Exit\n"
			"Enter a number: ";
		std::cin >> choice;

		if (choice < 1 || choice > 6)
		{
			std::cout << "Error: invalid input." << std::endl;
		}

		if (choice == 1)
		{
			addNum(nums);
		}

		if (choice == 2)
		{
			printVec(nums);
		}

		if (choice == 3)
		{
			doubleVec(nums);
		}

		if (choice == 4)
		{
			sumVec(nums);
		}

		if (choice == 5)
		{
			vecMultiples(nums);
		}

		if (choice == 6)
		{
			std::cout << "Exiting...";
			break;
		}
	}
}
