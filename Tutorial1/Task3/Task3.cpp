//main function code

#include "Task3.h"
#include <iostream>

int main() 
{
	//loops the menu screen until the user decides to exit the application
	do 
	{
		std::cout << "What is the weather like today?"
			"\n1. Sunny \n2. Cloudy \n3. Raining \n4. Exit Application" << std::endl;
		std::cin >> userChoice;

		OutputMessage(userChoice);

	} while (userChoice != 4);

}