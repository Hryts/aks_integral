//
// Created by heeve on 2020-03-01.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include "read_config.h"
#include <cmath>
#include <iomanip>

#define REQUIRED_ARGC 2
#define INITIAL_PARTITION 200

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced() {
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
inline long long to_us(const D &d) {
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

double f(const double x, const double y) {
    double res = 0.002;
    for (int i = -2; i < 3; ++i) {
        for (int j = -2; j < 3; ++j) {
            res += pow(5 * i + 13 + j + pow((x - 16 * j), 6) + pow((y - 16 * i), 6), -1);
        }
    }
    return pow(res, -1);
}


int main(int argc, char **argv) {

    std::string filename("configuration_file.txt");

    if (argc > REQUIRED_ARGC) {
        std::cerr << "Number of required arguments is wrong. \n";
        exit(1);
    }

    if (argc == REQUIRED_ARGC) {
        filename = argv[1];
    }

    myMap parameters = read_file(filename);

    double resCurrent;
    double resPrev;

    int parts = INITIAL_PARTITION;
    double absErr;
    double relErr;

    parameters["delta"] = (parameters["highY"] - parameters["lowY"]) / parts;
    resCurrent = multithread_integrate(parameters, f);
    auto start_t = get_current_time_fenced();

    do {
        resPrev = resCurrent;
        parts *= 2;
        parameters["delta"] = (parameters["highY"] - parameters["lowY"]) / parts;
        resCurrent = multithread_integrate(parameters, f);
        absErr = std::abs(resCurrent - resPrev);
        relErr = absErr / resCurrent;

    } while (absErr > parameters["expAbsErr"] || relErr > parameters["expRelErr"]);
    auto end_t = get_current_time_fenced();


    std::cout << "Result : " << std::setprecision(10) << resCurrent;
    std::cout << "\nAbsolute error : " << absErr;
    std::cout << "\nRelative error : " << relErr;
    std::cout << "\nTime : " << to_us(end_t - start_t) / 1000000.0 << "s";


    return 0;
}