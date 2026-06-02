//
// Created by Farnam on 5/31/2026.
//

#include <complex>
#include "Mandelbrot.h"
class Mande lbrot {
public:

/* Checks if: Z(n+1) = Z^(n) + C diverges or not
 * This approach is approximate as it doesn't actually check for the sequence divergence.
 * see "C++ Implementation" in docs folder.
 */
bool isDivergent(std::complex<double> c) {
    std::complex<double> z (0,0); // Initial value for z (z(0)) should be 0 + 0i

    while (irritation < MAX_IRRITATION) {
        z = z * z + c; // the formula for mandelbrot function

        /* Approach bellow is used so we can skip using sqrt.
            * another slower approach is to check if :
            *      std::abs(z) >= MAX_MAGNITUDE
            * this is slower as the std::abs function uses square roots.
            */
        if (std::norm(z) >= MAX_MAGNITUDE * MAX_MAGNITUDE) {
            return false;
        }
        irritation++;
    }

    return true;
}

int getIrritation() const { return irritation; }

private:

const int MAX_IRRITATION = 200;
const double MAX_MAGNITUDE = 2;
int irritation = 0;

};
