#include "sum_printer.h"
#include <iostream>

void sum_printer::start() {
    while (true) {
        unsigned long sum = recipient.get_next();

        if (sum >= 100 && sum % 32 == 0) {
            std::cout << "Sum: " << sum << std::endl;
        } else {
            std::cout << "Error: Sum should be 32n : 32n >= 100" << std::endl;
        }
    }

}