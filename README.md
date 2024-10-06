# SmartArray Library

`SmartArray` is a dynamic array class template in C++ that provides an easy-to-use interface for managing arrays of any data type. It supports various functionalities such as adding, removing, and searching for elements while handling memory management internally.

## Features

- **Dynamic Resizing**: Automatically resizes the array when needed.
- **Append Elements**: Easily add elements to the end of the array.
- **Pop Elements**: Remove elements from the array.
- **Find Elements**: Check if an element exists in the array.
- **Support for Static Arrays**: Append elements from static or dynamic arrays.
- **Initializer List Support**: Initialize the array using an initializer list.

## Installation

1. Clone the repository or download the `SmartArray.h` file.
2. Include the `SmartArray.h` file in your project.

```cpp
#include "SmartArray.h"
```

## Usage Examples

Here are some examples to demonstrate how to use the `SmartArray` class:

### Basic Operations

```cpp
#include <iostream>
#include "SmartArray.h"

int main() {
    SmartArray<int> intArray;

    // Append elements to the array
    intArray.append(10);
    intArray.append(20);
    intArray.append(30);
    intArray.append(40);
    intArray.append(50);

    // Display the elements in the array
    std::cout << "intArray: ";
    for (size_t i = 0; i < intArray.getSize(); i++) {
        std::cout << intArray.at(i) << " ";
    }
    std::cout << std::endl;

    // Pop an element from the array
    intArray.pop(2); // Removes the element at index 2

    // Display the elements after popping
    std::cout << "intArray after pop: ";
    for (size_t i = 0; i < intArray.getSize(); i++) {
        std::cout << intArray.at(i) << " ";
    }
    std::cout << std::endl;

    // Search for an element
    int elementToFind = 20;
    if (intArray.find(elementToFind)) {
        std::cout << "Element " << elementToFind << " found in the intArray." << std::endl;
    } else {
        std::cout << "Element " << elementToFind << " not found in intArray." << std::endl;
    }
    
    return 0;
}
```

### Working with Different Data Types

```cpp
// Using SmartArray with double type
SmartArray<double> doubleArray;
doubleArray.append(1.1);
doubleArray.append(2.2);

std::cout << "doubleArray: ";
for (size_t i = 0; i < doubleArray.getSize(); i++) {
    std::cout << doubleArray.at(i) << " ";
}
std::cout << std::endl;
```

### Appending Static Arrays

```cpp
// Appending elements from a static array
int staticArray[] = { 100, 200, 300 };
SmartArray<int> staticSmartArray;
staticSmartArray.append(staticArray);

std::cout << "Static array appended to smartArray: ";
for (size_t i = 0; i < staticSmartArray.getSize(); i++) {
    std::cout << staticSmartArray.at(i) << " ";
}
std::cout << std::endl;
```

### Using Initializer Lists

```cpp
// Initializing SmartArray using initializer lists
SmartArray<int> smartArrayList = { 10, 20, 40 };

// Displaying elements of smartArrayList
std::cout << "Initialized smartArrayList: ";
for (size_t i = 0; i < smartArrayList.getSize(); i++) {
    std::cout << smartArrayList.at(i) << " ";
}
std::cout << std::endl;
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contributions

Contributions are welcome! Please feel free to submit a pull request or open an issue for any suggestions or improvements.
