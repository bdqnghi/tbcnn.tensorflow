#pragma once
#include "SFML\Graphics.hpp"
#include "Quicksort.h"

class QuicksortWindow {
public:
	int WIDTH = 1024;
	int HEIGHT = 768;
	int openWindow() {
		sf::RenderWindow quicksortWindow(sf::VideoMode(WIDTH, HEIGHT), "Sorting Algorithm Visualisation: Quicksort!");
		Quicksort drawQuicksort(quicksortWindow);
		quicksortWindow.setVisible(false);
		quicksortWindow.setFramerateLimit(60);

		while (quicksortWindow.isOpen())
		{
			sf::Event event;
			while (quicksortWindow.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					quicksortWindow.close();
			}
			quicksortWindow.clear(sf::Color(250, 240, 230));
			drawQuicksort.animation();
			drawQuicksort.draw();
			quicksortWindow.display();
			quicksortWindow.setVisible(true);
		}
		return 0;
	}

};
#pragma once
