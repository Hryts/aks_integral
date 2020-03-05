//
// Created by heeve on 2020-03-01.
//

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include "read_config.h"
#include <cmath>


double f(const double x, const double y) {
    double res = 0.002;
    for (int i = -2; i < 3; ++i) {
        for (int j = -2; j < 3; ++j) {
            res += pow(5 * i + 13 + j + pow((x - 16 * j), 6) + pow((y - 16 * i), 6), -1);
        }
    }
    return pow(res, -1);
}


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

int main() {

    myMap parameters = read_file("configuration_file.txt");

    for(std::unordered_map<std::string, double>::const_iterator it = parameters.begin();
            it != parameters.end(); ++it)
    {
        std::cout << it->first << " " << it->second << "\n";
    }

    double res = 0.0;

    int step = (abs(parameters["lowX"]) + abs(parameters["highX"])) / parameters["threads"];
    double highX = parameters["highX"];
    parameters["highX"] = parameters["lowX"] + step;

    std::vector<std::thread> v;
    std::vector<double> local_res(parameters["threads"]);

    auto start_t = get_current_time_fenced();
    for (int i = 0; i < parameters["threads"] - 1; ++i) {
        v.emplace_back(multithread_integrate, parameters, std::ref(local_res[i]), f);
        parameters["lowX"] += step;
        parameters["highX"] += step;
    }

    parameters["highX"] = highX;
    v.emplace_back(multithread_integrate, parameters, std::ref(local_res[parameters["threads"] - 1]), f);


    for (auto &t: v) {
        t.join();
    }
    auto end_t = get_current_time_fenced();


    for (auto x: local_res) {
        res += x;
    }
    std::cout << "Time : " << to_us(end_t - start_t) / 1000 << std::endl;
    std::cout << "Absolute : " << parameters["expAbsErr"] << " Relative : " << parameters["expRelErr"] << std::endl << "Result : " << res;

    return 0;
}