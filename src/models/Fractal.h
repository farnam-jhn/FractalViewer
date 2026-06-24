#pragma once

#include <complex>

class Fractal{
public:
    virtual ~Fractal() = default;
    virtual int iterationsCount(std::complex<double> c) const = 0;
    virtual std::string getName() = 0;
    virtual double getCenterX() const { return 0.0; }
    int getMaxIterations() const{
        return MAX_ITERATIONS;
    }
protected:
    static constexpr int    MAX_ITERATIONS = 180;
    static constexpr double MAX_MAGNITUDE  = 2.0;
};
