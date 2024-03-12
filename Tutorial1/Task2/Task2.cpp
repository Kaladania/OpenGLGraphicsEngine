//main function code

#include "Task2.h"
#include <iostream>

int main()
{
	int numberInput = 0;

	for (int i = 0; i < 10; i++)
	{
		std::cout << "Enter a number: ";
		std::cin >> numberInput;

		userInputs[i] = numberInput;
	}

	std::cout << "The largest number you entered was: " << FindHighestValue(userInputs) << std::endl;

}