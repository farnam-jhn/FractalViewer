//
// Created by Farnam on 6/2/2026.
//

#include "VisualComputer.h"
#include "Mandelbrot.h"
#include <SFML/Graphics.hpp>
class VisualComputer {
public:
    sf::Image computeImage(Mandelbrot mb) {
        sf::Image image({WIDTH,HEIGHT}, sf::Color::Blue);
        // loops through the image and check if each pixel is in the set or not
        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                double realC = (x - WIDTH / 2) * SCALE;
                double imagC = (y - HEIGHT / 2) * SCALE;

                std::complex<double> c(realC, imagC);

                bool inSet = mb.isDivergent(c);
                if (inSet) {
                    image.setPixel(x, y, sf::Color::Black);
                }else {
                    image.setPixel(x, y, sf::Color::White);
                }

            }
        }

        return image;
    }

private:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;
    static constexpr double SCALE = 4.0;
};
