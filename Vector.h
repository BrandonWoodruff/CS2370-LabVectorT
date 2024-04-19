#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>
#include <cstddef>
using std::size_t;

//Create a vector generic by using a class template
template <typename T>
class Vector
{
    enum
    {
        CHUNK = 10
    };
    size_t capacity; // Size of the current array allocation (total number of ints, in use or not)
    size_t n_elems;  // Number of int spaces currently in use, starting from position 0
    T *data_ptr;     // Pointer to the heap array
    void grow();

public:
    // Object Mgt.
    Vector();
    Vector(const Vector &v);            // Copy constructor
    Vector &operator=(const Vector &v); // Copy assignment operator
    ~Vector();

    // Accessors
    T front() const;        // Return the int in position 0, if any
    T back() const;         // Return last element (position n_elems-1)
    T at(size_t pos) const; // Return element in position "pos" (0-based)
    size_t size() const;    // Return n_elems
    bool empty() const;     // Return n_elems == 0

    // Mutators
    T &operator[](size_t pos);       // Same as at but no bounds checking
    void push_back(T item);          // Append a new element at the end of the array
    void pop_back();                 // --n_elems (nothing else to do; returns nothing)
    void erase(size_t pos);          // Remove item in position pos and shuffles following items left
    void insert(size_t pos, T item); // Shuffle items right to make room for a new element
    void clear();                    // n_elems = 0 (nothing else to do; keep the current capacity)

    // Iterators
    T *begin(); // Return a pointer to 1st element, or nullptr if n_elems == 0
    T *end();   // Return a pointer to 1 past last element, or nullptr if n_elems == 0

    // Comparators
    bool operator==(const Vector &v) const;
    bool operator!=(const Vector &v) const;
};

#endif

template <typename T>
void Vector<T>::grow()
{
    size_t new_capacity = capacity + CHUNK;
    T *new_data_ptr = new T[new_capacity];
    for (size_t i = 0; i < n_elems; ++i)
        new_data_ptr[i] = data_ptr[i];
    delete[] data_ptr;
    data_ptr = new_data_ptr;
    capacity = new_capacity;
}

template <typename T>
Vector<T> ::Vector()
{
    capacity = CHUNK;
    n_elems = 0;
    data_ptr = new T[capacity];
}

template <typename T>
Vector<T> ::Vector(const Vector &v)
{
    capacity = v.capacity;
    n_elems = v.n_elems;
    data_ptr = new T[capacity];
    for (size_t i = 0; i < n_elems; ++i)
        data_ptr[i] = v.data_ptr[i];
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &v)
{
    if (this != &v)
    {
        delete[] data_ptr;
        capacity = v.capacity;
        n_elems = v.n_elems;
        data_ptr = new T[capacity];
        for (size_t i = 0; i < n_elems; ++i)
            data_ptr[i] = v.data_ptr[i];
    }
    return *this;
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] data_ptr;
}

template <typename T>
T Vector<T>::front() const
{
    if (n_elems == 0)
        throw std::range_error("Vector::front");
    return data_ptr[0];
}

template <typename T>
T Vector<T>::back() const
{
    if (n_elems == 0)
        throw std::range_error("Vector::back");
    return data_ptr[n_elems - 1];
}

template <typename T>
T Vector<T>::at(size_t pos) const
{
    if (pos >= n_elems)
        throw std::range_error("Vector::at");
    return data_ptr[pos];
}

// Create the size method
template <typename T>
size_t Vector<T>::size() const {
    return n_elems;
}

// Create the empty method
template <typename T>
bool Vector<T>::empty() const {
    return n_elems == 0;
}

// Create the operator[] method
template <typename T>
T& Vector<T>::operator[](size_t pos) {
    return data_ptr[pos];
}

// Create the pop_back method
template <typename T>
void Vector<T>::pop_back() {
    if (n_elems == 0)
        throw std::range_error("Vector::pop_back");
    --n_elems;
}

// Create the erase method
template <typename T>
void Vector<T>::erase(size_t pos) {
    if (pos >= n_elems)
        throw std::range_error("Vector::erase");
    for (size_t i = pos; i < n_elems - 1; ++i)
        data_ptr[i] = data_ptr[i + 1];
    --n_elems;
}

// Create the insert method
template <typename T>
void Vector<T>::insert(size_t pos, T item) {
    if (n_elems == capacity)
        grow();
    for (size_t i = n_elems; i > pos; --i)
        data_ptr[i] = data_ptr[i - 1];
    data_ptr[pos] = item;
    ++n_elems;
}

// Create the clear method
template <typename T>
void Vector<T>::clear() {
    n_elems = 0;
}

// Create the begin method
template <typename T>
T* Vector<T>::begin() {
    return n_elems == 0 ? nullptr : data_ptr;
}



// Create the end method
template <typename T>
T* Vector<T>::end() {
    return n_elems == 0 ? nullptr : data_ptr + n_elems;
}


// Create the operator== method
template <typename T>
bool Vector<T>::operator==(const Vector<T>& v) const {
    if (n_elems != v.n_elems)
        return false;
    for (size_t i = 0; i < n_elems; ++i)
        if (data_ptr[i] != v.data_ptr[i])
            return false;
    return true;
}


// Create the operator!= method
template <typename T>
bool Vector<T>::operator!=(const Vector<T>& v) const {
    return !(*this == v);
}

template <typename T>
void Vector<T>::push_back(T item) {
    if (n_elems == capacity)
        grow();
    data_ptr[n_elems++] = item;
}




// ELEPHANT CODE GRAVEYARD

//class Vector
// {
//     enum
//     {
//         CHUNK = 10
//     };
//     size_t capacity; // Size of the current array allocation (total number of ints, in use or not)
//     size_t n_elems;  // Number of int spaces currently in use, starting from position 0
//     int *data_ptr;   // Pointer to the heap array
//     void grow();

// public:
//     // Object Mgt.
//     Vector();
//     Vector(const Vector &v);            // Copy constructor
//     Vector &operator=(const Vector &v); // Copy assignment operator
//     ~Vector();

//     // Accessors
//     int front() const;        // Return the int in position 0, if any
//     int back() const;         // Return last element (position n_elems-1)
//     int at(size_t pos) const; // Return element in position "pos" (0-based)
//     size_t size() const;      // Return n_elems
//     bool empty() const;       // Return n_elems == 0

//     // Mutators
//     int &operator[](size_t pos);       // Same as at but no bounds checking
//     void push_back(int item);          // Append a new element at the end of the array
//     void pop_back();                   // --n_elems (nothing else to do; returns nothing)
//     void erase(size_t pos);            // Remove item in position pos and shuffles following items left
//     void insert(size_t pos, int item); // Shuffle items right to make room for a new element
//     void clear();                      // n_elems = 0 (nothing else to do; keep the current capacity)

//     // Iterators
//     int *begin(); // Return a pointer to 1st element, or nullptr if n_elems == 0
//     int *end();   // Return a pointer to 1 past last element, or nullptr if n_elems == 0

//     // Comparators
//     bool operator==(const Vector &v) const;
//     bool operator!=(const Vector &v) const;
// };