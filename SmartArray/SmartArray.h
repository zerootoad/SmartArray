#pragma once
#include <iostream>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class SmartArray {
private:
	T* data;
	size_t size;
	size_t capacity;
	size_t growth;

	void resize() {
		capacity *= growth;
		T* newData = new T[capacity];
		for (size_t i = 0; i < size; i++) {
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
	}
public:
	class Iterator {
	public:
		Iterator(T* ptr) : ptr(ptr) {}
		Iterator operator++() { ++ptr; return *this; }
		bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
		const T& operator*() const { return *ptr; }
	private:
		T* ptr;
	};

	Iterator begin() const { return Iterator(data); }
	Iterator end() const { return Iterator(data + size); }

	SmartArray(size_t growth = 2) : size(0), capacity(5), growth(growth) {
		data = new T[capacity];
	}

	SmartArray(std::initializer_list<T> init, size_t growth = 2)
		: size(init.size()), capacity(init.size()* growth), growth(growth) {
		data = new T[capacity];

		size_t index = 0;
		for (const auto& element : init) {
			data[index++] = element;
		}
	}

	~SmartArray() {
		delete[] data;
	}

	SmartArray& operator=(const SmartArray<T>& smartArray) const {
		if (this != &smartArray) {
			delete[] data;

			data = new T[smartArray.capacity];
			for (size_t i = 0; i < smartArray.size; i++) {
				data[i] = smartArray[i];
			}

			this->size = smartArray.size;
			this->capacity = smartArray.capacity;

			smartArray.data = nullptr;
			smartArray.size = 0;
			smartArray.capacity = 0;
		}
		return *this;
	}

	bool operator==(const SmartArray<T>& smartArray) const {
		if (size != smartArray.size) return false;

		for (size_t i = 0; i < size; i++) {
			if (data[i] != smartArray.data[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator!=(const SmartArray<T>& smartArray) const {
		return !(*this == smartArray);
	}

	bool operator<(const SmartArray<T>& smartArray) const {
		size_t minSize = (size < smartArray.size) ? size : smartArray.size;

		for (size_t i = 0; i < minSize; i++) {
			if (data[i] < smartArray.data[i]) return true;
			if (data[i] > smartArray.data[i]) return false;
		}

		return size < smartArray.size;
	}

	bool operator<=(const SmartArray<T>& smartArray) const {
		return (*this < smartArray) || (*this == smartArray);
	}

	bool operator>=(const SmartArray<T>& smartArray) const {
		return !(*this < smartArray);
	}

	bool operator<=(const SmartArray<T>& smartArray) const {
		return (*this < smartArray) || (*this == smartArray);
	}

	template <size_t N>
	SmartArray& operator=(T const (&array)[N]) const {
		delete[] data;

		this->size = N;
		this->capacity = N;

		data = new T[capacity];
		for (size_t i = 0; i < size; i++) {
			data[i] = array[i];
		}

		return *this;
	}

	T operator[](size_t index) const {
		if (index >= size) throw std::out_of_range("Index out of bounds");
		return data[index];
	}

	// Setters
	void setSize(size_t newSize) { size = newSize; }
	void setCapacity(size_t newCapacity) { capacity = newCapacity; }
	void setData(T* newData) { data = newData; }

	// Getters
	size_t getSize() const { return size; }
	size_t getCapacity() const { return capacity; }
	T* getData() const { return data; }

	// Initialization
	void append(T element);
	void append(SmartArray<T>& smartArray);

	template <size_t N>
	void append(T(&array)[N]); // for static arrays
	void append(T* array, size_t arraySize); // for dynamic arrays

	void pop(size_t index);
	void remove(size_t index);

	T at(size_t index);
	T atIndex(size_t index);

	bool find(T element);
	void findAndPop(T element);
	void findAndRemove(T element);

	void clear();

	void insert(size_t index, T element);

	void copy(SmartArray<T>& smartArray);
	void swap(SmartArray<T>& smartArray);
};

template <typename T>
void SmartArray<T>::append(T element)
{
	if (size >= capacity) resize();

	data[size] = element;
	size += 1;
}

template <typename T>
void SmartArray<T>::append(SmartArray<T>& smartArray)
{
	if (size + smartArray.size >= capacity) resize();

	for (size_t i = 0; i < smartArray.size; i++) {
		data[size] = smartArray[i];
		size += 1;
	}
}

template <typename T>
template <size_t N>
void SmartArray<T>::append(T(&array)[N])
{
	if (size + N >= capacity) resize();

	for (size_t i = 0; i < N; i++) {
		data[size] = array[i];
		size += 1;
	}
}

template <typename T>
void SmartArray<T>::append(T* array, size_t arraySize)
{
	if (size + arraySize >= capacity) resize();

	for (size_t i = 0; i < arraySize; i++) {
		data[size] = array[i];
		size += 1;
	}
}

template<typename T>
void SmartArray<T>::pop(size_t index)
{
	if (size <= 0) throw std::out_of_range("Cannot pop from an empty smart array");
	if (index >= size) throw std::out_of_range("Index out of bounds");

	for (size_t i = index; i < size - 1; i++) {
		data[i] = data[i + 1];
	}

	size -= 1;
}

template<typename T>
void SmartArray<T>::remove(size_t index)
{
	if (size <= 0) throw std::out_of_range("Cannot pop from an empty smart array");
	if (index >= size) throw std::out_of_range("Index out of bounds");

	for (size_t i = index; i < size - 1; i++) {
		data[i] = data[i + 1];
	}

	size -= 1;
}

template<typename T>
T SmartArray<T>::at(size_t index)
{
	if (index >= size) throw std::out_of_range("Index out of bounds");
	return data[index];
}

template<typename T>
T SmartArray<T>::atIndex(size_t index)
{
	if (index >= size) throw std::out_of_range("Index out of bounds");
	return data[index];
}

template<typename T>
bool SmartArray<T>::find(T element)
{
	if (size <= 0) throw std::out_of_range("Cannot find within an empty smart array");

	for (size_t i = 0; i < size; i++) {
		if (data[i] == element) return true;
	}

	return false;
}

template<typename T>
void SmartArray<T>::findAndPop(T element)
{
	if (size <= 0) throw std::out_of_range("Cannot findAndPop within an empty smart array");

	bool found = false;

	for (size_t i = 0; i < size; i++) {
		if (data[i] == element) {
			found = true;
			for (size_t j = i; j < size - 1; j++) {
				data[j] = data[j + 1];
			}
			size -= 1;
			break;
		}
	}

	if (!found) {
		throw std::runtime_error("Element not found in the array.");
	}
}

template<typename T>
void SmartArray<T>::findAndRemove(T element)
{
	if (size <= 0) throw std::out_of_range("Cannot findAndRemove within an empty smart array");

	bool found = false;

	for (size_t i = 0; i < size; i++) {
		if (data[i] == element) {
			found = true;
			for (size_t j = i; j < size - 1; j++) {
				data[j] = data[j + 1];
			}
			size -= 1;
			break;
		}
	}

	if (!found) {
		throw std::runtime_error("Element not found in the array.");
	}
}

template<typename T>
void SmartArray<T>::clear()
{
	if (size <= 0) throw std::out_of_range("Cannot clear an empty smart array");

	delete[] data;

	size = 0;
	data = new T[capacity];

	std::cout << capacity << " " << size;
}

template<typename T>
inline void SmartArray<T>::insert(size_t index, T element)
{
	if (index >= size) throw std::out_of_range("Index out of bounds");
	if (size >= capacity) resize();

	for (size_t i = size; i > index; i--) {
		data[i] = data[i - 1];
	}
	data[index] = element;
	size += 1;
}

template<typename T>
inline void SmartArray<T>::copy(SmartArray<T>& smartArray)
{
	if (this != &smartArray) {
		delete[] data;

		data = new T[smartArray.capacity];
		for (size_t i = 0; i < smartArray.size; i++) {
			data[i] = smartArray[i];
		}

		this->size = smartArray.size;
		this->capacity = smartArray.capacity;
	}
	return *this;
}

template<typename T>
inline void SmartArray<T>::swap(SmartArray<T>& smartArray)
{
	if (this != &smartArray) {
		delete[] data;

		data = new T[smartArray.capacity];
		for (size_t i = 0; i < smartArray.size; i++) {
			data[i] = smartArray[i];
		}

		this->size = smartArray.size;
		this->capacity = smartArray.capacity;

		smartArray.data = nullptr;
		smartArray.size = 0;
		smartArray.capacity = 0;
	}
	return *this;
}
