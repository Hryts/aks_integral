//
// Created by heeve on 2020-03-01.
//

#include "calculator.h"
#include <mutex>
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

void integrate(double start, double end, double &data, const double div) {
    double res = 0.0;
    double j = 0.0;
    while (start < end) {
        while (j < 50) {
            res += f(start, j) * div * div;
            j += div;
        }
        start += div;
        j = -50.0;
    }

    data = res;
}


