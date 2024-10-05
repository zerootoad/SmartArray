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

    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
public:
    SmartArray() : size(0), capacity(5) {
        data = new T[capacity];
    }

    SmartArray(std::initializer_list<T> init) : size(init.size()), capacity(init.size() * 2) {
        data = new T[capacity];
        
        size_t index = 0;
        for (const auto& element : init) {
            data[index++] = element;
        }
    }

    ~SmartArray() {
        delete[] data;
    }

    SmartArray& operator=(const SmartArray<T>& smartArray) {
        if (this != &smartArray) {
            delete[] data;

            this->size = smartArray.size;
            this->capacity = smartArray.capacity;

            data = new T[capacity];
            for (size_t i = 0; i < size; i++) {
                data[i] = smartArray[i];
            }
        }
        return *this;
    }

    template <size_t N>
    SmartArray& operator=(T const (&array)[N]) {
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
    void append(const SmartArray<T>& smartArray);

    template <size_t N>
    void append(T const (&array)[N]); // for static arrays
    void append(T* array, size_t arraySize); // for dynamic arrays

    void pop(size_t index);
    T at(size_t index);
    bool find(T element);
};

template <typename T>
void SmartArray<T>::append(T element)
{
    if (getSize() == getCapacity()) {
        resize();
    }

    getData()[getSize()] = element;
    setSize(getSize() + 1);
}

template <typename T>
void SmartArray<T>::append(const SmartArray<T>& smartArray)
{
    if (getSize() + smartArray.getSize() > getCapacity()) {
        resize();
    }

    for (size_t i = 0; i < smartArray.getSize(); i++) {
        getData()[getSize()] = smartArray[i];
        setSize(getSize() + 1);
    }
}

template <typename T>
template <size_t N>
void SmartArray<T>::append(T const (&array)[N])
{
    if (getSize() + N > getCapacity()) {
        resize();
    }

    for (size_t i = 0; i < N; i++) {
        getData()[getSize()] = array[i];
        setSize(getSize() + 1);
    }
}

template <typename T>
void SmartArray<T>::append(T* array, size_t arraySize)
{
    if (getSize() + arraySize > getCapacity()) {
        resize();
    }

    for (size_t i = 0; i < arraySize; i++) {
        getData()[getSize()] = array[i];
        setSize(getSize() + 1);
    }
}

template<typename T>
void SmartArray<T>::pop(size_t index)
{
    if (getSize() <= 0) throw std::out_of_range("Cannot pop from an empty smart array");
    if (index >= getSize()) throw std::out_of_range("Index out of bounds");

    for (size_t i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }

    setSize(getSize() - 1);
}

template<typename T>
T SmartArray<T>::at(size_t index)
{
    if (index >= getSize()) throw std::out_of_range("Index out of bounds");
    return getData()[index];
}

template<typename T>
bool SmartArray<T>::find(T element)
{
    if (getSize() <= 0) throw std::out_of_range("Cannot find elements within an empty smart array");

    for (size_t i = 0; i < getSize(); i++) {
        if (getData()[i] == element) return true;
    }

    return false;
}