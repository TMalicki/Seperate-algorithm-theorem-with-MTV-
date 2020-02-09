#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::RectangleShape shape(sf::Vector2f(100.f, 100.f));
	shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2);
	shape.setFillColor(sf::Color::Green);

	sf::RectangleShape shape2(sf::Vector2f(100.f, 100.f));
	shape2.setOrigin(shape2.getGlobalBounds().width / 2, shape2.getGlobalBounds().height / 2);
	shape2.setFillColor(sf::Color::Red);
	shape2.setPosition(400, 300);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		shape.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

		window.clear();
		window.draw(shape);
		window.draw(shape2);
		window.display();
	}

	return 0;
}