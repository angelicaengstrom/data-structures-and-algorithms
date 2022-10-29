//
// Created by angel on 2022-04-26.
//

#ifndef LAB2_MEASURE_H
#define LAB2_MEASURE_H

#include "data_generators.h"
#include "sorting_algorithms.h"
#include "timer.h"
#include <vector>
#include <chrono>
#include <cmath>
#include <fstream>

namespace math {
    double mean(const double arr[], size_t size) {
        double sum = 0;
        for (int i = 0; i < size; i++)
            sum += arr[i];
        return (double) sum / (double) size;
    }
    //https://www.programiz.com/cpp-programming/examples/standard-deviation
    double std_dev(double arr[], double mean, int size) {
        double variance = 0;
        for (int i = 0; i < size; i++) {
            variance += pow(arr[i] - mean, 2);
        }
        variance = variance / size;
        return sqrt(variance);
    }
}

template<typename ForwardIt>
ForwardIt sort(ForwardIt first, ForwardIt last, algorithm algorithm){
    switch(algorithm){
        case algorithm::std_sort:
            alg::std_sort(first, last);
            break;
        case algorithm::selection_sort:
            alg::selection_sort(first, last);
            break;
        case algorithm::insertion_sort:
            alg::insertion_sort(first, last);
            break;
        case algorithm::quick_sort:
            alg::quick_sort(first, last, pivot::last);
            break;
        case algorithm::quick_sort_M_O_T:
             alg::quick_sort(first, last, pivot::medianOfThree);
            break;
        default:
            throw std::runtime_error("not a algorithm type");
    }
    return first;
}

struct measured_value{
    measured_value(size_t N, int samples, double time_stamps[]):N(N), samples(samples) {
        mean = math::mean(time_stamps, samples);
        std_dev = math::std_dev(time_stamps, mean, samples); }
    double mean;
    double std_dev;
    size_t N;
    size_t samples;
};

void write_to_file(const std::string& filename, const std::vector<measured_value>& measurements){
    std::ofstream file(R"(C:\Users\angel\OneDrive\Dokument\DT046G Datastrukturer och Algoritmer\lab2\data\)" + filename + ".csv");
    for(auto m : measurements){
        file << m.N << "," << m.mean << "," << m.std_dev << "," << m.samples << "\n";
    }
    file.close();
}

std::string filename(const algorithm& algorithm, const series& series){
    std::string filename;
    switch (algorithm) {
        case algorithm::std_sort:
            filename = "std_sort";
            break;
        case algorithm::selection_sort:
            filename = "selection_sort";
            break;
        case algorithm::insertion_sort:
            filename = "insertion_sort";
            break;
        case algorithm::quick_sort:
            filename = "quick_sort";
            break;
        case algorithm::quick_sort_M_O_T:
            filename = "quick_sort_mot";
            break;
    }
    switch (series) {
        case series::falling:
            filename = filename + "_falling";
            break;
        case series::rising:
            filename = filename + "_rising";
            break;
        case series::random:
            filename = filename + "_random";
            break;
        case series::constant:
            filename = filename + "_constant";
            break;
    }
    return filename;
}


enum N{ min = 20000, max = 200000 };
void measure(algorithm algorithm, series series, int sample){
    Timer timer;
    double time_stamps[sample];
    std::vector<measured_value> measurements;

    for(size_t N = min; N <= max; N = N + min){
        int buffer[N];

        for(size_t i = 0; i < sample; i++) {
            generate<int>(buffer, buffer + N, series);

            timer.start();
            sort(buffer, buffer + N, algorithm);
            timer.stop();

            time_stamps[i] = timer.get();
        }
        measurements.push_back(measured_value(N, sample, time_stamps));
        std::cout << N << std::endl;
    }
    write_to_file(filename(algorithm, series), measurements);
}


#endif //LAB2_MEASURE_H
