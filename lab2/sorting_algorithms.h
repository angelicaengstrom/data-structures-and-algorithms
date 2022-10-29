//
// Created by angel on 2022-04-21.
//
#ifndef LAB2_SORTING_ALGORITHMS_H
#define LAB2_SORTING_ALGORITHMS_H
#include <algorithm>
#include <iostream>

enum algorithm{
    selection_sort,
    insertion_sort,
    quick_sort,
    quick_sort_M_O_T,
    std_sort
};

enum pivot{ last, medianOfThree };

namespace alg {
    template<typename ForwardIt, typename Compare = std::less<>>
    ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp = Compare{}) {
        ForwardIt min = first;
        for (; first != last; first++) {
            if(comp(*first, *min)){
                min = first;
            }
        }
        return min;
    }

    template<typename ForwardIt>
    void iter_swap(ForwardIt a, ForwardIt b){
        *a = (*a)^(*b);
        *b = (*a)^(*b);
        *a = (*a)^(*b);
    }

    template<typename ForwardIt, typename Compare = std::less<>>
    void selection_sort(ForwardIt first, ForwardIt last, Compare comp = Compare{}) {
        for (; first != last; first++) {
            auto selection = alg::min_element(first, last, comp);
            alg::iter_swap(selection, first);
        }
    }

    template<typename ForwardIt, typename T, typename Compare = std::less<T>>
    ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp = Compare{}){
        auto middle = first + (std::distance(first, last) / 2);
        if(*middle == value){ return middle; }
        if(!std::distance(first, last)){
            return middle;
        }
        if(comp(*middle, value)){
            if(*std::next(middle) == value){
                return std::next(middle); }
            return alg::upper_bound(middle, last, value, comp);
        }else{
            if(comp(*std::prev(middle), value)){
                return middle;
            }
            return alg::upper_bound(first, middle, value, comp);
        }
    }

    template<typename ForwardIt>
    ForwardIt rotate(ForwardIt first, ForwardIt new_first, ForwardIt last){
        for(;first != std::prev(last); first++){
            alg::iter_swap(first, new_first);
        }
    }

    template<typename ForwardIt, typename Compare = std::less<>>
    void insertion_sort(ForwardIt first, ForwardIt last, Compare comp = Compare{}) {
        for (auto it = first; it != last; ++it){
            auto insertion = alg::upper_bound(first, it, *it, comp);
            alg::rotate(insertion, it, std::next(it));
        }
    }

    template<typename RandomAccessIt, typename Compare = std::less<>>
    void std_sort(RandomAccessIt first, RandomAccessIt last, Compare comp = Compare{}){
        std::sort(first, last, comp);
    }

    template<typename RandomAccessIt, typename Compare = std::less<>>
    RandomAccessIt median_of_three(RandomAccessIt first, RandomAccessIt last, Compare comp = Compare{}){
        auto middle = first + (std::distance(first, std::next(last)) / 2);

        if(comp(*last, *first)){ alg::iter_swap(last, first); }
        if(comp(*middle, *first)){ alg::iter_swap(middle, first); }
        if(comp(*middle, *last)){ alg::iter_swap(last, middle); }

        return last;
    }

    template<typename RandomAccessIt, typename T, typename Compare = std::less<>>
    RandomAccessIt partition(RandomAccessIt first, RandomAccessIt last, const T& pivot, Compare comp = Compare{}){
        RandomAccessIt l_it = first;
        RandomAccessIt r_it = std::prev(last);

        while(l_it != r_it){
            if(comp(pivot, *l_it)){
                if(comp(*r_it, pivot)){
                    iter_swap(l_it, r_it);
                }else{
                    r_it--;
                }
            }else{
                l_it++;
            }
        }
        iter_swap(l_it, std::prev(last));
        return l_it;
    }

    template<typename RandomAccessIt, typename Compare = std::less<>>
    void quick_sort(RandomAccessIt first, RandomAccessIt last, pivot pivot, Compare comp = Compare{}){
        if(first < last) {
            RandomAccessIt middle;
            switch(pivot){
                case pivot::last:
                    middle = alg::partition(first, last, *std::prev(last), comp);
                    break;
                case pivot::medianOfThree:
                    middle = alg::partition(first, last, *median_of_three(first, std::prev(last), comp), comp);
                    break;
            }
            quick_sort(first, middle, pivot, comp);
            quick_sort(std::next(middle), last, pivot, comp);
        }
    }
}
#endif //LAB2_SORTING_ALGORITHMS_H
