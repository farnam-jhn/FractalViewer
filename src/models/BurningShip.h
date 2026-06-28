#pragma once

#include "Fractal.h"

class BurningShip : public Fractal {
public:
    int iterationsCount(std::complex<double> c) const override {
        std::complex<double> z(0, 0);
        int iteration = 0;

        while (iteration < MAX_ITERATIONS) {
            std::complex<double> temp(std::abs(z.real()), std::abs(z.imag()));
            z = temp * temp + c;

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
    const std::string NAME = "Burning Ship";
};
