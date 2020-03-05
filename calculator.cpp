//
// Created by heeve on 2020-03-01.
//

#include "calculator.h"


double integrate(myMap parameters, const double delta, myFunc& f) {
    double res = 0;
    double x = parameters["lowX"];
    double y;
    while (x < parameters["highX"]) {
        y = parameters["lowY"];
        while (y < parameters["highY"]) {
            res += f(x, y) * delta * delta;
            y += delta;
        }
        x += delta;
    }
    return res;
}

double integrate4Real(myMap parameters, myFunc &f) {
    int parts = 500;
    double resPrev;
    double resCurrent;
    double delta = (parameters["highY"] - parameters["lowY"]) / parts;
    resCurrent = integrate(parameters, delta, f);
    double absErr;
    double relErr;
    do {
        resPrev = resCurrent;
        parts *= 2;
        delta = (parameters["highY"] - parameters["lowY"]) / parts;
        resCurrent = integrate(parameters, delta, f);
        absErr = std::abs(resCurrent - resPrev);
        relErr = absErr / resCurrent;
    } while (absErr > parameters["expAbsErr"] && relErr > parameters["expRelErr"]);
    return resCurrent;
}


void multithread_integrate(myMap parameters, double &data, myFunc &f) {
    data = integrate4Real(parameters, f);
}