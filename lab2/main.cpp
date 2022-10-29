#include "measure.h"

int main() {
    int sample = 10;

    std::cout << "std_sort:" << std::endl;
    measure(std_sort, random, sample);
    measure(std_sort, falling, sample);
    measure(std_sort, constant, sample);
    measure(std_sort, rising, sample);

    std::cout << "selectionsort:" << std::endl;
    measure(selection_sort, random, sample);
    measure(selection_sort, falling, sample);
    measure(selection_sort, constant, sample);
    measure(selection_sort, rising, sample);

    std::cout << "insertionsort:" << std::endl;
    measure(insertion_sort, random, sample);
    measure(insertion_sort, falling, sample);
    measure(insertion_sort, constant, sample);
    measure(insertion_sort, rising, sample);

    std::cout << "quicksort:" << std::endl;
    measure(quick_sort, random, sample);
    measure(quick_sort, falling, sample);
    measure(quick_sort, constant, sample);
    measure(quick_sort, rising, sample);

    std::cout << "quicksort median of three:" << std::endl;
    measure(quick_sort_M_O_T, random, sample);
    measure(quick_sort_M_O_T, falling, sample);
    measure(quick_sort_M_O_T, constant, sample);
    measure(quick_sort_M_O_T, rising, sample);

    return 0;
}
