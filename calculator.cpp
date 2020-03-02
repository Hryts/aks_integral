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

void integrate(double &data, params parameters) {
    double res = 0;
    double x = parameters.lowerX;
    while (x < parameters.highX) {
        y = parameters.lowerY;
        while (y < parameters.highY) {
            res += f(x, y) * parameters.deltaY * parameters.deltaX;
            y += parameters.deltaX;
        }
        x += parameters.deltaY;
    }
    data = res;
}

double integrate4Real(params parameters, double expAbsErr, double expRelErr){
    int parts = 500;
    double resPrev;
    double resCurrent;
    parameters.deltaX = (parameters.highX - parameters.lowerX) / parts;
    parameters.deltaY = (parameters.highY - parameters.lowerY) / parts;
    integrate(resPrev, parameters);
    double absErr;
    double relErr;
    do {
        parts *= 2;
        parameters.deltaX = (parameters.highX - parameters.lowerX) / parts;
        parameters.deltaY = (parameters.highY - parameters.lowerY) / parts;
        integrate(resCurrent, parameters);
        resPrev = resCurrent;
        absErr = abs(resCurrent - resPrev);
        relErr = absErr / resPrev;
    } while (absErr > expAbsErr && relErr > expRelErr);
    return res;
}
