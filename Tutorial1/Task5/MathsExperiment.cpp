#include "MathsExperiment.h"
#include <iostream>

float MathsExperiment::Add(const float a, const float b)
{
	return a + b;
}

float MathsExperiment::Subtract(const float a, const float b)
{
	return a - b;
}

float MathsExperiment::Multiply(const float a, const float b)
{
	return a * b;
}

float MathsExperiment::Divide(const float a, const float b)
{
	if (a != 0 && b != 0) 
	{
		return a / b;
	}
	else 
	{
		return 0;
	}
}