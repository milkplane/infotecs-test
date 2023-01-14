#include "input_sum_transponder.h"

int main() {
    const size_t buffer_size = 128;
    input_sum_transponder<buffer_size> app;
    
    app.start();
}