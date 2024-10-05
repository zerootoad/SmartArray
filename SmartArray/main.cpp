#include <iostream>
#include "SmartArray.h" 

int main() {
    SmartArray<int> intArray;

    intArray.append(10);
    intArray.append(20);
    intArray.append(30);
    intArray.append(40);
    intArray.append(50);

    std::cout << "intArray: ";
    for (size_t i = 0; i < intArray.getSize(); i++) {
        std::cout << intArray.at(i) << " ";
    }
    std::cout << std::endl;

    intArray.pop(2); 

    std::cout << "intArray after pop: ";
    for (size_t i = 0; i < intArray.getSize(); i++) {
        std::cout << intArray.at(i) << " ";
    }
    std::cout << std::endl;

    int elementToFind = 20;
    if (intArray.find(elementToFind)) {
        std::cout << "Element " << elementToFind << " found in the intArray." << std::endl;
    }
    else {
        std::cout << "Element " << elementToFind << " not found in intArray." << std::endl;
    }

    SmartArray<double> doubleArray;
    doubleArray.append(1.1);
    doubleArray.append(2.2);

    std::cout << "doubleArray: ";
    for (size_t i = 0; i < doubleArray.getSize(); i++) {
        std::cout << doubleArray.at(i) << " ";
    }
    std::cout << std::endl;

    int staticArray[] = { 100, 200, 300 };
    SmartArray<int> staticSmartArray;
    staticSmartArray.append(staticArray); 

    std::cout << "Static array appended to smartArray: ";
    for (size_t i = 0; i < staticSmartArray.getSize(); i++) {
        std::cout << staticSmartArray.at(i) << " ";
    }
    std::cout << std::endl;

    SmartArray<int> smartArraySigma = { 10, 20, 40 };

    smartArraySigma = staticArray;
    std::cout << "Static array to smartArraySigma: ";
    for (size_t i = 0; i < smartArraySigma.getSize(); i++) {
        std::cout << smartArraySigma.at(i) << " ";
    }
    std::cout << std::endl << std::endl;
    printAllocationStats();

    return 0;
}
