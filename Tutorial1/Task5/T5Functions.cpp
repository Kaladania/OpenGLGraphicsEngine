//Task 3 function Definitions

//void BeginMathsExperiement(){}

#include <iostream>
#include "MathsExperiment.h"
#include "AccountExperiment.h"

/// <summary>
/// Returns an appropriate message depending on user choice
/// </summary>
/// <param name="menuChoice">menu option selected</param>
void OutputMessage(int menuChoice, AccountExperiment &userAccount)
{
	switch (menuChoice)
	{
	case(1):
		
		userAccount.PrintBalance();
		break;

	case(2):

		userAccount.SetBalance();
		break;

	case(3):
		
		
		userAccount.AddToBalance();
		break;

	case(4):
		
		
		userAccount.SetIntrestRate();
		break;

	case(5):

		userAccount.ApplyIntrestRate();
		break;

	case(6):

		std::cout << "Exiting Application. Goodbye.";
		break;

	default:
		std::cout << "That option is currently unavailible. Please choose a number from 1 - 4\n" << std::endl;
	}
}


/// <summary>
/// Runs the math experiment task
/// </summary>
void BeginMathsExperiement() 
{
	MathsExperiment me;
	float a = 0;
	float b = 0;

	int userChoice = 0;

	MathsExperiment* pointerMe = new MathsExperiment();

	std::cout << "Enter a number: ";
	std::cin >> a;

	std::cout << "Enter another number: ";
	std::cin >> b;

	std::cout << "The total of your numbers added is: " << me.Add(a, b) << std::endl;
	std::cout << "The total of your numbers subtracted is: " << me.Subtract(a, b) << std::endl;
	std::cout << "The total of your numbers multiplied is: " << me.Multiply(a, b) << std::endl;
	std::cout << "The total of your numbers divided is: " << me.Divide(a, b) << std::endl;

	std::cout << "The total of your numbers added is: " << pointerMe->Add(a, b) << std::endl;
	std::cout << "The total of your numbers subtracted is: " << pointerMe->Subtract(a, b) << std::endl;
	std::cout << "The total of your numbers multiplied is: " << pointerMe->Multiply(a, b) << std::endl;
	std::cout << "The total of your numbers divided is: " << pointerMe->Divide(a, b) << std::endl;

	delete pointerMe;
}

/// <summary>
/// Runs the account experiment task
/// </summary>
void BeginAccountExperiment() 
{
	int userChoice = 0;
	AccountExperiment* userAccount = new AccountExperiment();

	//loops the menu screen until the user decides to exit the application
	do
	{
		std::cout << "What would you like to do with your account?"
			"\n1. Print Balance \n2. Set Balance \n3. Update Balance \n4. Set Intrest Rate \n5. ApplyIntrestRate \n6. Exit Application" << std::endl;
		std::cin >> userChoice;

		OutputMessage(userChoice, *userAccount);

	} while (userChoice != 6);
}