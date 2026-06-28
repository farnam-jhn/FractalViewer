#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "models/Mandelbrot.h"
#include "models/BurningShip.h"
#include "VisualComputer.h"
#include "models/Julia.h"

sf::Vector2i clampToWindow(sf::Vector2i position, unsigned int width, unsigned int height) {
	return {
		std::clamp(position.x, 0, static_cast<int>(width)),
		std::clamp(position.y, 0, static_cast<int>(height))
	};
}

sf::IntRect makeZoomRectangle(sf::Vector2i start, sf::Vector2i end, double aspectRatio) {
	int dx = end.x - start.x;
	int dy = end.y - start.y;

	if (dx == 0) {
		return {{start.x, start.y}, {0, 0}};
	}

	int widthSign = dx < 0 ? -1 : 1;
	int heightSign = dy < 0 ? -1 : 1;
	int width = std::abs(dx);
	int height = 0;

	if (dy == 0 || static_cast<double>(std::abs(dx)) / std::abs(dy) <= aspectRatio) {
		height = static_cast<int>(std::round(width / aspectRatio));
	}
	else {
		height = std::abs(dy);
		width = static_cast<int>(std::round(height * aspectRatio));
	}

	width *= widthSign;
	height *= heightSign;

	int left = width < 0 ? start.x + width : start.x;
	int top = height < 0 ? start.y + height : start.y;

	return {{left, top}, {std::abs(width), std::abs(height)}};
}

Viewport viewportFromRectangle(const Viewport &viewport, sf::IntRect rectangle, unsigned int width, unsigned int height) {
	const double realSpan = viewport.maxReal - viewport.minReal;
	const double imagSpan = viewport.maxImag - viewport.minImag;

	return {
		viewport.minReal + (static_cast<double>(rectangle.position.x) / width) * realSpan,
		viewport.minReal + (static_cast<double>(rectangle.position.x + rectangle.size.x) / width) * realSpan,
		viewport.minImag + (static_cast<double>(rectangle.position.y) / height) * imagSpan,
		viewport.minImag + (static_cast<double>(rectangle.position.y + rectangle.size.y) / height) * imagSpan
	};
}

int main(int argc, char *argv[]) {
	std::string mode = "mandelbrot"; // default mode

	if (argc > 1) {
		mode = argv[1];
	}

	Fractal *fractal = nullptr;

	if (mode == "mandelbrot") {
		fractal = new Mandelbrot();
	} else if (mode == "burning-ship") {
		fractal = new BurningShip();
	} else if (mode == "julia") {
		double real = -0.7, imag = 0.27; // defaults
		if (argc > 3) {
			real = std::stod(argv[2]);
			imag = std::stod(argv[3]);
		}
		fractal = new Julia(std::complex<double>(real, imag));
	} else {
		std::cerr << "Unknown mode: " << mode << "\n";
		std::cerr << "Usage: fracv [mandelbrot|burning-ship|julia] [real] [imag]\n";
		return 1;
	}
	const VisualComputer vc;
	Viewport viewport = vc.getDefaultViewport(*fractal);

	sf::RenderWindow window( sf::VideoMode( {vc.getWidth(),vc.getHeight()} ), "Fractal Viewer" );
	sf::Image image({vc.getWidth(),vc.getHeight()}, sf::Color::Black);
	vc.computeImage(*fractal, vc.getWidth(), vc.getHeight(), viewport, 0, 0, image);


	sf::Texture texture(image);
	sf::Sprite sprite(texture);

	bool isDragging = false;
	sf::Vector2i dragStart;
	sf::Vector2i dragEnd;

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
			else if (const auto *mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mousePressed->button == sf::Mouse::Button::Left) {
					isDragging = true;
					dragStart = clampToWindow(mousePressed->position, vc.getWidth(), vc.getHeight());
					dragEnd = dragStart;
				}
			}
			else if (const auto *mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
				if (isDragging) {
					dragEnd = clampToWindow(mouseMoved->position, vc.getWidth(), vc.getHeight());
				}
			}
			else if (const auto *mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
				if (mouseReleased->button == sf::Mouse::Button::Left && isDragging) {
					dragEnd = clampToWindow(mouseReleased->position, vc.getWidth(), vc.getHeight());
					isDragging = false;

					sf::IntRect zoomRectangle = makeZoomRectangle(dragStart, dragEnd, static_cast<double>(vc.getWidth()) / vc.getHeight());

					if (zoomRectangle.size.x > 5 && zoomRectangle.size.y > 5) {
						viewport = viewportFromRectangle(viewport, zoomRectangle, vc.getWidth(), vc.getHeight());
						vc.computeImage(*fractal, vc.getWidth(), vc.getHeight(), viewport, 0, 0, image);
						texture.update(image);
					}
				}
			}
		}
		window.clear();
		window.draw(sprite);

		if (isDragging) {
			sf::IntRect zoomRectangle = makeZoomRectangle(dragStart, dragEnd, static_cast<double>(vc.getWidth()) / vc.getHeight());
			sf::RectangleShape selection;

			selection.setPosition(sf::Vector2f(zoomRectangle.position));
			selection.setSize(sf::Vector2f(zoomRectangle.size));
			selection.setFillColor(sf::Color::Transparent);
			selection.setOutlineColor(sf::Color::White);
			selection.setOutlineThickness(2.0f);

			window.draw(selection);
		}

		window.display();
	}
}
