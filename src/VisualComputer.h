#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <complex>
#include <cstdint>
#include <thread>
#include <vector>

#include "models/Fractal.h"

class VisualComputer {
public:
    void computeImage(const Fractal &fractal, unsigned int width, unsigned int height, unsigned int startWidth, unsigned int startHeight, sf::Image &currentImage) const {
        std::vector<std::uint8_t> pixels(static_cast<std::size_t>(width) * height * 4, 0);

        if (startHeight >= height || startWidth >= width) {
            currentImage = sf::Image({width, height}, pixels.data());
            return;
        }

        const unsigned int rowsToCompute = height - startHeight;
        const unsigned int requestedThreadCount = std::max(10u, std::thread::hardware_concurrency());
        const unsigned int threadCount = std::min(requestedThreadCount, rowsToCompute);
        const unsigned int rowsPerThread = (rowsToCompute + threadCount - 1) / threadCount;

        std::vector<std::thread> workers;
        workers.reserve(threadCount);

        /* Creates a new thread (in anonymous form) and adds it to workers vector
         * this is beneficial for joining the threads.
         */
        for (unsigned int threadIndex = 0; threadIndex < threadCount; threadIndex++) {
            const unsigned int yBegin = startHeight + threadIndex * rowsPerThread;
            const unsigned int yEnd = std::min(yBegin + rowsPerThread, height);

            workers.emplace_back([&, yBegin, yEnd]() {
            // Loops through this thread's rows and checks if each pixel is in the set.
                for (unsigned int y = yBegin; y < yEnd; y++) {
                    for (unsigned int x = startWidth; x < width; x++) {
                        /* Pixels in the image are saved in an array;
                         * this means that coordinating system in the image and cartesian coordinating
                         * systems are distinct
                         */
                        double realC = (x - WIDTH / 2.0) * SCALE + fractal.getCenterX();
                        double imagC = (y - HEIGHT / 2.0) * SCALE;

                        std::complex<double> inputNumber(realC, imagC); // This number would be the input for iterationsCount function inside Mandelbrot and Julia model classes

                        int iteration = fractal.iterationsCount(inputNumber);
                        sf::Color color = smoothColor(colorPalette, iteration, fractal.getMaxIterations());

                        const std::size_t pixelIndex = (static_cast<std::size_t>(y) * width + x) * 4;
                        pixels[pixelIndex]     = color.r;
                        pixels[pixelIndex + 1] = color.g;
                        pixels[pixelIndex + 2] = color.b;
                        pixels[pixelIndex + 3] = color.a;
                    }
                }
            });
        }

        for (std::thread &worker : workers) {
            worker.join();
        }

        currentImage = sf::Image({width, height}, pixels.data());
    }

    unsigned int getWidth() const { return static_cast<unsigned int>(WIDTH); }
    unsigned int getHeight() const { return static_cast<unsigned int>(HEIGHT); }

private:
    // Gives a color for each iteration amount
    sf::Color smoothColor(const std::vector<sf::Color> &palette, int iteration, int maxIterations) const {
        if (iteration >= maxIterations) {
            return palette.back();
        }

        double t = static_cast<double>(iteration) / static_cast<double>(maxIterations);
        double scaled = t * (palette.size() - 1);

        std::size_t i = static_cast<std::size_t>(scaled);
        std::size_t j = std::min(i + 1, palette.size() - 1); // next index after i but bounded
        double fraction = scaled - i;

        // Generates a color between palette[i] and palette[j]
        return lerpColor(palette[i], palette[j], fraction);
    }

    sf::Color lerpColor(sf::Color color1, sf::Color color2, double t) const {
        auto lerp = [t](std::uint8_t x, std::uint8_t y) {
            return static_cast<std::uint8_t>(x + (y - x) * t);
        };

        return sf::Color(
            lerp(color1.r, color2.r),
            lerp(color1.g, color2.g),
            lerp(color1.b, color2.b),
            lerp(color1.a, color2.a)
        );
    }

    static constexpr double WIDTH  = 1440;
    static constexpr double HEIGHT = 900;
    static constexpr double SCALE = 4.0 / WIDTH;

    inline static const std::vector<sf::Color> colorPalette = {
        sf::Color(8, 10, 25),
        sf::Color(15, 20, 45),
        sf::Color(25, 35, 70),
        sf::Color(35, 55, 100),
        sf::Color(50, 80, 130),
        sf::Color(70, 105, 160),
        sf::Color(95, 130, 185),
        sf::Color(120, 155, 205),
        sf::Color(145, 180, 220),
        sf::Color(170, 200, 230),
        sf::Color(190, 215, 235),
        sf::Color(210, 225, 230),
        sf::Color(235, 210, 180),
        sf::Color(245, 180, 130),
        sf::Color(250, 145, 90),
        sf::Color(250, 110, 60),
        sf::Color(245, 80, 45),
        sf::Color(235, 55, 40),
        sf::Color(210, 40, 40),
        sf::Color(170, 30, 45),
        sf::Color(120, 22, 42),
        sf::Color(70, 15, 35),
        sf::Color(30, 8, 25),
        sf::Color(0, 0, 0)
    };
};