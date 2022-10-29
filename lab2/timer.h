//
// Created by angel on 2022-05-09.
//
#ifndef LAB2_TIMER_H
#define LAB2_TIMER_H
#include <chrono>

class Timer{
public:
    void start(){ t_start = std::chrono::system_clock::now(); }
    void stop(){ elapsed_seconds = std::chrono::system_clock::now() - t_start; }
    double get(){ return elapsed_seconds.count(); }
private:
    std::chrono::time_point<std::chrono::system_clock> t_start;
    std::chrono::duration<double> elapsed_seconds;
};

#endif //LAB2_TIMER_H
