#pragma once

#include "Fractal.h"

class Julia : public Fractal {
public:
    Julia(std::complex<double> c) {
        constant = c;
    }
    int iterationsCount(std::complex<double> z) const override {
        int iteration = 0;

        while (iteration < MAX_ITERATIONS) {
            z = z * z + constant;

            /* Approach bellow is used so we can skip using sqrt.
            * another slower approach is to check if :
            *      std::abs(z) >= MAX_MAGNITUDE
            * this is slower as the std::abs function uses square roots.
            */
            if (std::norm(z) >= MAX_MAGNITUDE * MAX_MAGNITUDE) {
                break;
            }
            iteration++;
        }

        return iteration;
    }

    std::string getName() override {
        return NAME;
    }
private:
    std::complex<double> constant;
    const std::string NAME = "Julia Set";
};