//Task 3 function Definitions
#include <iostream>
#include <string>

/// <summary>
/// Outputs a left-aligned pyramid of numbers
/// </summary>
/// <param name="totalRows">Amount of rows in the pyramid</param>
void OutputNumberTriangle(int totalRows)
{
	int currentCollumn = 1;
	std::string pyramidRow = "";

	for (int i = 0; i < totalRows; i++)
	{
		pyramidRow += std::to_string(currentCollumn) + " ";
		std::cout << pyramidRow << "\n" << std::endl;

		currentCollumn++;
	}
}