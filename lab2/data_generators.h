//
// Created by angel on 2022-04-26.
//

#ifndef LAB2_DATA_GENERATORS_H
#define LAB2_DATA_GENERATORS_H
#include <vector>
#include <iostream>
#include <random>

enum series{
    random, constant, falling, rising
};

template<typename T, typename ForwardIt>
ForwardIt generate(ForwardIt first, ForwardIt last, series order){
    std::random_device rand;
    T element = rand();
    for(ForwardIt it = first; it != last; it++) {
        switch (order) {
            case series::random:
                *it = rand();
                break;
            case series::constant:
                *it = element;
                break;
            case series::falling:
                *it = element--;
                break;
            case series::rising:
                *it = element++;
                break;
            default:
                throw std::runtime_error("not a series type");
        }
    }
    return first;
}

#endif //LAB2_DATA_GENERATORS_H
