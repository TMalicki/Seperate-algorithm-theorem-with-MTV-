#include <iostream>
#include <SFML/Graphics.hpp>
#include "RectObj.h"
#include "SAT.h"

using namespace std;

sf::Vector2f calculateMoveValue(RectObj& obj1, RectObj& obj2, SAT& sat);
void boarderCheck(RectObj& obj1, RectObj& obj2, sf::Vector2f moveValue);

const sf::Vector2i windowSize = sf::Vector2i(800, 600);

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML works!");
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
		
		if (sat.collisionSAT(obj1, obj2))
		{
			sf::Vector2f moveValue = calculateMoveValue(obj1, obj2, sat);
			obj2.getObjShape().move(moveValue.x, moveValue.y);

			boarderCheck(obj1, obj2, moveValue);
		}

		obj1.getObjShape().rotate(2);
		obj2.getObjShape().rotate(-2);

		window.clear();
		window.draw(obj1.getObjShape());
		window.draw(obj2.getObjShape());
		window.display();
	}

	return 0;
}

sf::Vector2f calculateMoveValue(RectObj& obj1, RectObj& obj2, SAT& sat)
{
	float distance = sat.getDepthCollision();
	int vect = sat.getVectorOfCollision();

	sf::Vector2f moveCoord = sat.getVectorProjection()[vect - 1];

	sat.normalize(moveCoord);

	sf::Vector2f posObj1 = obj1.getObjShape().getPosition();
	sf::Vector2f posObj2 = obj2.getObjShape().getPosition();

	int dirX = -(posObj1.x - posObj2.x) / abs(posObj1.x - posObj2.x);
	int dirY = -(posObj1.y - posObj2.y) / abs(posObj1.y - posObj2.y);


	moveCoord.x = moveCoord.x * dirX * distance;
	moveCoord.y = moveCoord.y * dirY * distance;

	return moveCoord;
}

void boarderCheck(RectObj& obj1, RectObj& obj2, sf::Vector2f moveValue)
{
	if (obj2.getObjShape().getPosition().x + obj2.getObjShape().getGlobalBounds().height / 2 > windowSize.x ||
		obj2.getObjShape().getPosition().x - obj2.getObjShape().getGlobalBounds().height / 2 < 0)
	{
		obj2.getObjShape().move(-moveValue.x, 0);
	}
	if (obj2.getObjShape().getPosition().y + obj2.getObjShape().getGlobalBounds().height / 2 > windowSize.y ||
		obj2.getObjShape().getPosition().y - obj2.getObjShape().getGlobalBounds().height / 2 < 0)
	{
		obj2.getObjShape().move(0, -moveValue.y);
	}

}