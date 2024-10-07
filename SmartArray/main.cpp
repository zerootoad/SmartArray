#include <iostream>
#include "SmartArray.h"

int main() {
	SmartArray<int> array1;

	array1.append(10);
	array1.append(20);
	array1.append(50);
	array1.append(40);
	array1.append(60);

	std::cout << "array1: ";
	for (int x : array1) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	SmartArray<int> array2 = { 20, 30, 40, 50, 60 };
	std::cout << "array2: ";
	for (int x : array2) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	array1 = array2;

	std::cout << "array2 moved to array1: ";
	for (int x : array1) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	std::cout << "array2 after: ";
	for (int x : array2) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	return 0;
}