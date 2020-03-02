//
// Created by heeve on 2020-03-01.
//

#include <mutex>


void integrate(double &data, params parameters);

struct params {
    double deltaX;
    double deltaY;
    double lowerX;
    double lowerY;
    double highX;
    double highY;
} ;