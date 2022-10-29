#include <ctime>
#include <algorithm>
#include "measure.h"

int main() {
    srand(time(nullptr));
    int samples = 50;

    measure(binary, samples);
    measure(linear, samples);
    measure(interpolation, samples);
    measure(tree, samples);
    measure(hash, samples);

    return 0;
}
