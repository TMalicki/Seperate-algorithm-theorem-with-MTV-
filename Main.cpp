#include <iostream>
#include <SFML/Graphics.hpp>
#include "RectObj.h"
#include "SAT.h"

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(60);

	RectObj obj1(sf::Color::Red);
	RectObj obj2(sf::Color::Green);
	obj2.getObjShape().setPosition(400, 300);

	SAT sat;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		obj1.getObjShape().setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

		sat.collisionSAT(obj1, obj2);

		obj1.getObjShape().rotate(2);
		obj2.getObjShape().rotate(-2);

		window.clear();
		window.draw(obj1.getObjShape());
		window.draw(obj2.getObjShape());
		window.display();
	}

	return 0;
}