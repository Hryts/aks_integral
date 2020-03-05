//
// Created by heeve on 2020-03-01.
//
#include <string>
#include <unordered_map>
#include <functional>


typedef std::unordered_map<std::string, double> myMap;
typedef const std::function<double(const double, const double)> myFunc;

double integrate(myMap parameters, double deltaY, myFunc &f);

double integrate4Real(myMap parameters, myFunc &f);


void multithread_integrate(myMap parameters, double &data, myFunc& f);
