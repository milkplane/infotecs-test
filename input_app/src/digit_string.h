#ifndef DIGIT_STRING_H_
#define DIGIT_STRING_H_

#include <cstring>
#include <iostream>
#include <algorithm>

template <size_t max_size>
class digit_string {
public:
    digit_string();

    void copy_from(const char* str, const size_t size);
    void input(std::istream& stream);
    void print(std::ostream& stream) const;
    unsigned long int get_sum_of_digits() const;
    bool is_correct_string() const;
    void replace_odds();
    void reverse_sort();
    const char* get_raw_sring() const;
    size_t get_size() const;
private:
    char raw_string[max_size * 2 + 1]; // to fit "KB" + '0'
    size_t size;

    bool is_only_digits() const;
    bool is_proper_size() const;
    bool is_odd(char) const;
    size_t get_odd_count() const;
    short get_digit_from(char) const;
};

template <size_t max_size>
digit_string<max_size>::digit_string() {
    size = 0;
}

template <size_t max_size>
void digit_string<max_size>::copy_from(const char* str, const size_t size) {
    std::memcpy(raw_string, str, size);
    this->size = size;
    raw_string[size] = '\0';
}

template <size_t max_size>
void digit_string<max_size>::input(std::istream& stream) {
    while (true) {
        stream.getline(raw_string, max_size + 1);

        // discarding
        if (!stream) {
            stream.clear();
            while (stream.get() != '\n');
            continue;
        }

        size = strlen(raw_string);
        if (is_only_digits()) break;
    }
}

template <size_t max_size>
void digit_string<max_size>::print(std::ostream& stream) const {
    for (size_t i = 0; i < size; i++) {
        stream << (char) raw_string[i];
    }
}

template <size_t max_size>
short digit_string<max_size>::get_digit_from(char ch) const {
    return (ch - '0');
}

template <size_t max_size>
unsigned long int digit_string<max_size>::get_sum_of_digits() const {
    unsigned long int sum = 0;

    for (size_t i = 0; i < size; i++) {
        if (!isdigit(raw_string[i])) continue;
        sum += get_digit_from(raw_string[i]);
    }

    return sum;
}

template <size_t max_size>
bool digit_string<max_size>::is_odd(char ch) const {
    return get_digit_from(ch) % 2 == 0;
}

template <size_t max_size>
size_t digit_string<max_size>::get_odd_count() const {
    size_t count = 0;

    for (size_t i = 0; i < size; i++) {
        if (!is_odd(raw_string[i])) continue;

        count++;
    }

    return count;
}

template <size_t max_size>
void digit_string<max_size>::replace_odds() {
    size_t unreplaced_odd_count = get_odd_count();
    size_t future_size = unreplaced_odd_count + size;

    for (size_t i = size; i > 0; i--) {
        if (is_odd(raw_string[i - 1])) {

            raw_string[i + unreplaced_odd_count - 2] = 'K';
            raw_string[i + unreplaced_odd_count - 1] = 'B';
            
            unreplaced_odd_count--;
            continue;
        }
        
        raw_string[i + unreplaced_odd_count - 1] = raw_string[i - 1];
    }

    size = future_size;
    raw_string[size] = '\0';
}

template <size_t max_size>
void digit_string<max_size>::reverse_sort() {
    std::sort(raw_string, raw_string + size, std::greater<char>());
}

template <size_t max_size>
bool digit_string<max_size>::is_only_digits() const {
    return std::all_of(raw_string, raw_string + size, isdigit);
}

template <size_t max_size>
bool digit_string<max_size>::is_proper_size() const {
    return size <= max_size;
}

template <size_t max_size>
bool digit_string<max_size>::is_correct_string() const {
    return is_only_digits() && is_proper_size();
}

template <size_t max_size>
size_t digit_string<max_size>::get_size() const {
    return size;
}

template <size_t max_size>
const char* digit_string<max_size>::get_raw_sring() const {
    return raw_string;
}

#endif