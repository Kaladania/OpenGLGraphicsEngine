//Task 2 function definitions

//#define LENGTHOF(x) (sizeof(x) / sizeof(x[0])) // calculates array size

/// <summary>
/// Returns the largest number in the given array
/// </summary>
/// <param name="intergerArray">array to search</param>
/// <returns>largest number found in array</returns>
int FindHighestValue(int (*intergerArray))
{
	int largestNumber = 0;

	for (int i = 0; i < 10; i++)
	{
		if (intergerArray[i] > largestNumber) {
			largestNumber = intergerArray[i];
		}
	}

	return largestNumber;
}