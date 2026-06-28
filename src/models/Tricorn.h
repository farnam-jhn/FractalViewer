#pragma once

#include "Fractal.h"

class Tricorn : public Fractal {
public:
    int iterationsCount(std::complex<double> c) const override {
        std::complex<double> z(0, 0);
        int iteration = 0;

        while (iteration < MAX_ITERATIONS) {

            z = std::conj(z) * std::conj(z) + c;

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
    const std::string NAME = "Tricorn";

};