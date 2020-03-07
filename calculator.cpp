//
// Created by heeve on 2020-03-01.
//

#include "calculator.h"

#include <iostream>
#include <thread>




void integrate(myMap parameters, double &data, myFunc &f) {
    double res = 0.0;
    double x = parameters["lowX"];
    double y;
    while (x < parameters["highX"]) {
        y = parameters["lowY"];
        while (y < parameters["highY"]) {
            res += f(x, y) * parameters["delta"] * parameters["delta"];
            y += parameters["delta"];
        }
        x += parameters["delta"];
    }
    data = res;
}


double multithread_integrate(myMap parameters, myFunc &f) {
    double res = 0.0;

    int step = (parameters["highX"] - parameters["lowX"]) / parameters["threads"];

    double highX = parameters["highX"];
    parameters["highX"] = parameters["lowX"] + step;

    std::vector<std::thread> v;
    std::vector<double> local_res(parameters["threads"]);

    for (int i = 0; i < parameters["threads"] - 1; ++i) {
        v.emplace_back(integrate, parameters, std::ref(local_res[i]), f);
        parameters["lowX"] += step;
        parameters["highX"] += step;
    }

    parameters["highX"] = highX;
    v.emplace_back(integrate, parameters, std::ref(local_res[parameters["threads"] - 1]), f);


    for (auto &t: v) {
        t.join();
    }


    for (auto x: local_res) {
        res += x;
    }
    return res;
}