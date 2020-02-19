#include <iostream>
#include <SFML/Graphics.hpp>
#include "Physic.h"

int main()
{
	const sf::Vector2i windowSize = sf::Vector2i(800, 600);

	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML works!");
	Physic physic;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		physic.play(window);
		physic.update(window);
	}

	return 0;
}