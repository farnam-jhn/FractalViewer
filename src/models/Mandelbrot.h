#pragma once

#include "Fractal.h"

class Mandelbrot : public Fractal{
public:
    /* Checks if: Z(n+1) = Z^(n) + C diverges or not
    * This approach is approximate as it doesn't actually check for the sequence divergence.
    * see "C++ Implementation" in docs folder.
    */
    int iterationsCount(std::complex<double> c) const override {
        std::complex<double> z(0, 0);
        int iteration = 0;

        while (iteration < MAX_ITERATIONS) {
            z = z * z + c;
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

    double getCenterX() const override { return -0.5; }

private:
    const std::string NAME = "Mandelbrot Set";
};
