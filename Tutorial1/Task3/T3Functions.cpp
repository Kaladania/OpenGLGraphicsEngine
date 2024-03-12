//Task 3 function Definitions
#include <iostream>

/// <summary>
/// Returns an appropriate message depending on user choice
/// </summary>
/// <param name="menuChoice">menu option selected</param>
void OutputMessage(int menuChoice) 
{
	switch (menuChoice) 
	{
	case(1):
		std::cout << "Don't forget your sunscreen!\n" << std::endl;
		break;
	case(2):
		std::cout << "It looks like it might rain. Better take your umbrella.\n" << std::endl;
		break;
	case(3):
		std::cout << "Don't forget your umbrealla!\n" << std::endl;
		break;
	case(4):
		std::cout << "Exiting Application. Goodbye.\n" << std::endl;
		break;

	default:
		std::cout << "That option is currently unavailible. Please choose a number from 1 - 4\n" << std::endl;
	}
}