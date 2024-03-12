//main function code

#include "Task1.h"
#include <iostream>

int main() {

	std::cout << "Enter the width of the rectangle: ";
	std::cin >> width;

	std::cout << "Enter the height of the rectangle: ";
	std::cin >> height;

	std::cout << "The area of the given rectangle is: " << CalculateArea(width, height) << std::endl;
	std::cout << "The area of the given rectangle is: " << CalculatePerimeter(width, height) << std::endl;

}