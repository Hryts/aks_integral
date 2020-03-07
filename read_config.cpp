//
// Created by heeve on 2020-03-05.
//

#include "read_config.h"
#include <fstream>
#include <iostream>

#define MIN_RELATIVE        0.001
#define REQUIRED_ARG_NUMBER 7

std::unordered_map<std::string, double> read_file(const std::string &filename) {
    std::ifstream in;
    in.open(filename);
    myMap m;
    try {
        if (in.is_open()) {
            std::string s;
            while (getline(in, s)) {
                s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());
                auto eq = s.find('=');

                if (s.empty() || eq == std::string::npos) {
                    continue;
                }

                auto name = s.substr(0, eq);
                auto value = s.substr(eq + 1);
                m[name] = std::stod(value);
            }

        } else {
            std::cerr << "Couldn't open config file for reading. \n";
            exit(5);
        }
    }
    catch (...) {
        std::cerr << "Wrong configuration file arguments. \n";
        exit(2);
    }

    if (m["expRelErr"] > MIN_RELATIVE || m["lowX"] > m["highX"] || m["lowY"] > m["highY"] || m["expRelErr"] < 0 ||
        m["expAbsErr"] < 0 || m["threads"] <= 0) {
        std::cerr << "Wrong configuration file arguments. \n";
        exit(3);
    }
    if (m.size() != REQUIRED_ARG_NUMBER) {
        std::cerr << "There should be 7 arguments. See the example. \n";
        exit(4);
    }
    in.close();
    return m;
}