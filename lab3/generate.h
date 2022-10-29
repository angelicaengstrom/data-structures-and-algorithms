//
// Created by angel on 2022-05-09.
//

#ifndef LAB3_GENERATE_H
#define LAB3_GENERATE_H

#include <vector>
#include <cmath>
#include "algorithms.h"
#include "linked_list.h"

template <typename RandomAccessIt>
RandomAccessIt find_primes(RandomAccessIt first, size_t max){
    *first = false;
    *std::next(first) = false;
    int i = 2;

    while(i < max / 2){
        int divisor = i * 2;
        while(divisor < max){
            *(first + divisor) = false;
            divisor = divisor + i;
        }
        i++;
        while(!*(first + i)){
            i++;
        }
    }
    return first;
}

std::vector<int> generate_primes(size_t max){
    bool arr[max];
    for(int i = 0; i < max; i++){ arr[i] = true; }

    find_primes(arr, max);

    std::vector<int> primes;
    for(int i = 0; i < max; i++){
        if(arr[i]){
            primes.push_back(i);
        }
    }
    return primes;
}

template<typename RandomAccessIt, typename T>
void create_tree(RandomAccessIt first, RandomAccessIt last, std::vector<T>& result, int index){
    if(!(std::distance(first, last) / 2)){
        if(first < last){ result[index] = *first; }
        return;
    }

    RandomAccessIt middle = first + (std::distance(first, last) / 2);
    result[index] = *middle;
    create_tree(first, middle, result, (2 * index) + 1);
    create_tree(std::next(middle), last, result, (2 * index) + 2);
}

template<typename RandomAccessIt, typename T>
std::vector<T> generate_binary_tree(RandomAccessIt first, RandomAccessIt last){
    auto levels = log2((double)std::distance(first, last)) + 1;
    int capacity = (int)std::pow(2, levels) - 1;
    std::vector<T> tree(capacity);
    create_tree(first, last, tree, 0);
    return tree;
}

template<typename RandomAccessIt, typename T>
std::vector<linked_list<T>> generate_hash_table(RandomAccessIt first, RandomAccessIt last, int size){
    std::vector<linked_list<T>> hash_table(size);

    for(;first != last; first++){
        auto index = *first % size;
        hash_table[index].push_back(*first);
    }

    return hash_table;
}
#endif //LAB3_GENERATE_H
