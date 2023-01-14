#ifndef SUM_PRINTER_H_
#define SUM_PRINTER_H_

#include "one_value_recipient.h"

class sum_printer {
public:
    sum_printer() = default;
    void start();
private:
    one_value_recipient<unsigned long> recipient;
};

#endif