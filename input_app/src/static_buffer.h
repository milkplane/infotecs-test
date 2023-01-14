#ifndef THREAD_BUFFER_H_
#define THREAD_BUFFER_H_

#include <cstring>
#include <mutex>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <cstring>

template<size_t max_size>
class static_buffer {
public:
    static_buffer();
    void copy_from(const char* arr, size_t size);
    const char* get_raw_buffer() const;
    void clear();
    void print(std::ostream& stream) const;
    size_t get_size() const;

private:
    char arr[max_size];
    size_t size;
};

template <size_t max_size>
static_buffer<max_size>::static_buffer() {
    size = 0;
}

template <size_t max_size>
void static_buffer<max_size>::copy_from(const char* arr, size_t size) {
    std::memcpy(this->arr, arr, size * sizeof(char));

    this->size = size;
}

template <size_t max_size>
size_t static_buffer<max_size>::get_size() const {
    return size;
}

template <size_t max_size>
const char* static_buffer<max_size>::get_raw_buffer() const {
    return arr;
}

template <size_t max_size>
void static_buffer<max_size>::clear() {
    std::fill(arr, arr + max_size, 0);
}

#endif