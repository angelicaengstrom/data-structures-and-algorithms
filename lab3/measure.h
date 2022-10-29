//
// Created by angel on 2022-05-09.
//

#ifndef LAB3_MEASURE_H
#define LAB3_MEASURE_H

#include "generate.h"
#include "Timer.h"
#include <random>
#include <fstream>

std::vector<int> primes;
std::vector<int> bin_tree;
std::vector<linked_list<int>> hash_table;
using iterator_t = std::vector<int>::iterator;

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
        return sqrt(variance) / sqrt(size);
    }
}

void search(algorithm search){
    switch(search){
        case algorithm::linear:
            src::linear_search(primes.begin(), primes.end(),std::rand() % primes.back());
            break;
        case algorithm::binary:
            src::binary_search(primes.begin(), primes.end(), std::rand() % primes.back());
            break;
        case algorithm::interpolation:
            src::interpolation_search(primes.begin(), primes.end(), std::rand() % primes.back());
            break;
        case algorithm::tree:
            src::binary_search_tree(bin_tree, 0, std::rand() % primes.back());
            break;
        case algorithm::hash:
            src::hash_search(hash_table, std::rand() % primes.back());
            break;
    }
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
    std::ofstream file(R"(C:\Users\angel\OneDrive\Dokument\DT046G Datastrukturer och Algoritmer\lab3\data\)" + filename + ".csv");
    for(auto m : measurements){
        file << m.N << "," << m.mean << "," << m.std_dev << "," << m.samples << "\n";
    }
    file.close();
}

std::string filename(const algorithm& algorithm){
    std::string filename;
    switch (algorithm) {
        case algorithm::binary:
            filename = "binary_search";
            break;
        case algorithm::interpolation:
            filename = "interpolation_search";
            break;
        case algorithm::linear:
            filename = "linear_search";
            break;
        case algorithm::tree:
            filename = "binary_tree_search";
            break;
        case algorithm::hash:
            filename = "hash_table_search";
            break;
    }
    return filename;
}

enum elements{ min = 20000, max = 200000 };
void measure(algorithm algorithm, int samples){
    std::vector<measured_value> measurements;
    Timer timer;
    double time_stamps[samples];

    for(size_t N = elements::min; N <= elements::max; N = N + elements::min) {
        primes = generate_primes(N);

        if(algorithm == tree){
            bin_tree = generate_binary_tree<iterator_t, int>(primes.begin(), primes.end());
        }else if(algorithm == hash){
            //Vi utnyttjar att vi endast har primtal i vår array för att få en rimlig storlek till hashtabellen
            int capacity = *std::upper_bound(primes.begin(), primes.end(), primes.size());
            float load = ((float)primes.size() / (float)capacity);

            //Den bästa lastfaktorn hittades vid 60%, vid 70% var det inte en lika rak linje
            while(load > 0.50){
                capacity = *std::upper_bound(primes.begin(), primes.end(), ++capacity);
                load = ((float)primes.size() / (float)capacity);
            }
            hash_table = generate_hash_table<iterator_t, int>(primes.begin(), primes.end(), capacity);
        }

        for (int sample = 0; sample < samples; sample++) {

            int max = 100000;
            if(algorithm == linear){ max = 100; }

            timer.start();
            for(int i = 0; i < max; i++) {
                search(algorithm);
            }
            timer.stop();

            time_stamps[sample] = timer.get() / max;
        }

        measurements.emplace_back(measured_value(N, samples, time_stamps));

        if(algorithm == tree){
            bin_tree.clear();
        }else if(algorithm == hash){
            hash_table.clear();
        }
    }
    write_to_file(filename(algorithm), measurements);
}
#endif //LAB3_MEASURE_H
