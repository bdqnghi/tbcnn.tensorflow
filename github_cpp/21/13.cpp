#pragma once
#include "SFML\Graphics.hpp"
#include "SelectionSort.h"

class SelectionSortWindow {
public:
	int WIDTH = 1024;
	int HEIGHT = 768;
	int openWindow() {
		sf::RenderWindow selectionSortWindow(sf::VideoMode(WIDTH, HEIGHT), "Sorting Algorithm Visualisation: Selection Sort!");
		SelectionSort drawSelectionSort(selectionSortWindow);
		selectionSortWindow.setVisible(false);
		selectionSortWindow.setFramerateLimit(60);

		while (selectionSortWindow.isOpen())
		{
			sf::Event event;
			while (selectionSortWindow.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					selectionSortWindow.close();
			}
			selectionSortWindow.clear(sf::Color(250, 240, 230));
			drawSelectionSort.animation();
			drawSelectionSort.draw();
			selectionSortWindow.display();
			selectionSortWindow.setVisible(true);
		}
		return 0;
	}

};
