#include <SFML/Graphics.hpp>
#include <iostream>
#include "models/Mandelbrot.h"
#include "VisualComputer.h"
#include "models/Julia.h"

int main(int argc, char *argv[]) {
	std::string mode = "mandelbrot"; // default mode

	if (argc > 1) {
		mode = argv[1];
	}

	Fractal *fractal = nullptr;

	if (mode == "mandelbrot") {
		fractal = new Mandelbrot();
	} else if (mode == "julia") {
		double real = -0.7, imag = 0.27; // defaults
		if (argc > 3) {
			real = std::stod(argv[2]);
			imag = std::stod(argv[3]);
		}
		fractal = new Julia(std::complex<double>(real, imag));
	} else {
		std::cerr << "Unknown mode: " << mode << "\n";
		std::cerr << "Usage: fracv [mandelbrot|julia] [real] [imag]\n";
		return 1;
	}
	const VisualComputer vc;

	sf::RenderWindow window( sf::VideoMode( {vc.getWidth(),vc.getHeight()} ), "Fractal Viewer" );
	sf::Image image({vc.getWidth(),vc.getHeight()}, sf::Color::Black);
	vc.computeImage(*fractal, vc.getWidth(), vc.getHeight(), 0, 0, image);


	sf::Texture texture(image);
	sf::Sprite sprite(texture);

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}
		window.clear();
		window.draw(sprite);
		window.display();
	}
}
