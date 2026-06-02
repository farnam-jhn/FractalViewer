//
// Created by Farnam on 5/31/2026.
//

#ifndef CMAKESFMLPROJECT_MANDELBROT_H
#define CMAKESFMLPROJECT_MANDELBROT_H

#include <complex>

class Mandelbrot {
public:
    bool isDivergent(std::complex<double> c);
    int getIrritation() const;

private:
    const int MAX_IRRITATION = 200;
    const double MAX_MAGNITUDE = 2.0;
    int irritation = 0;
};


#endif //CMAKESFMLPROJECT_MANDELBROT_H
