//
// Created by Farnam on 6/2/2026.
//

#ifndef CMAKESFMLPROJECT_VISUALCOMPUTER_H
#define CMAKESFMLPROJECT_VISUALCOMPUTER_H
#include "VisualComputer.h"
#include "Mandelbrot.h"
#include <SFML/Graphics.hpp>
class VisualComputer {
    public:
    sf::Image computeImage(Mandelbrot mb);
    private:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;
    static constexpr double SCALE = 4.0;
};


#endif //CMAKESFMLPROJECT_VISUALCOMPUTER_H
