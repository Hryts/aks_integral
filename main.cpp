//
// Created by heeve on 2020-03-01.
//

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "calculator.h"


int main() {

    double res = 0.0;
    std::mutex m;
    int thr_num = 2;
    std::vector<std::thread> v;
    std::vector<double> local_res(thr_num);

    for (int i = 0; i < thr_num; ++i) {
        v.emplace_back(integrate, std::ref(m), std::ref(local_res[i]), 0.1);
    }

    for (auto &t: v) {
        t.join();
    }
    for (auto x: local_res) {
        res += x;
    }
    std::cout << res;
    return 0;
}