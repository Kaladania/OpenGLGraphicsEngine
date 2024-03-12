#include "AccountExperiment.h"
#include <iostream>

/// <summary>
/// Outputs user's current balance totla
/// </summary>
void AccountExperiment::PrintBalance() 
{
	std::cout << "Your current balance is: " << AccountExperiment::totalBalance << "\n" << std::endl;
}


/// <summary>
/// Initialises User's balance total
/// </summary>
void AccountExperiment::SetBalance()
{
	float newBalance = 0;

	std::cout << "Enter your starting balance: ";
	std::cin >> newBalance;

	totalBalance = newBalance;
	std::cout << "Your balance has been set. \n" << std::endl;
}


/// <summary>
/// Adds an amount to the total balance
/// </summary>
void AccountExperiment::AddToBalance()
{
	float amountToAdd = 0;

	std::cout << "How much would you like to add to your balance: ";
	std::cin >> amountToAdd;

	totalBalance += amountToAdd;
	std::cout << "Your balance has been updated. \n" << std::endl;
}

/// <summary>
/// Sets the intrest rate of the account
/// </summary>
void AccountExperiment::SetIntrestRate()
{
	float newIntrestRate = 0;

	std::cout << "Enter your account's intrest rate: ";
	std::cin >> newIntrestRate;

	if (newIntrestRate != 0) 
	{
		intrestRate = newIntrestRate / 100;
	}

	std::cout << "Your intrest rate has been set. \n" << std::endl;
}


/// <summary>
/// Applys intrest to the account and adds the intrest earned to the total balance
/// </summary>
void AccountExperiment::ApplyIntrestRate()
{
	float intrestEarned = totalBalance * intrestRate;
	totalBalance += intrestEarned;
	
	std::cout << "You earned intrest of " << intrestEarned << " has now been added to your account. Your balance has been updated. \n" << std::endl;
}