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
	obj2.getObjShape().setRotation(45);
	obj1.getObjShape().setPosition(400, 0);///
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
			/// ---- depth moving
			cout << "Collision\n";
			float distance = sat.getDepthCollision();
			int vect = sat.getVectorOfCollision();

			std::vector<sf::Vector2f> vectProjection = sat.getVectorProjection();
			sf::Vector2f moveCoord = vectProjection[vect - 1];

			if(moveCoord.x != 0) moveCoord.x /= moveCoord.x;
			if(moveCoord.y != 0) moveCoord.y /= moveCoord.y;
	
			sf::Vector2f posObj1 = obj1.getObjShape().getPosition();
			sf::Vector2f posObj2 = obj2.getObjShape().getPosition();

			int dirX = -(posObj1.x - posObj2.x) / abs(posObj1.x - posObj2.x);
			int dirY = -(posObj1.y - posObj2.y) / abs(posObj1.y - posObj2.y);
			
			obj2.getObjShape().move(moveCoord.y * distance * dirX, moveCoord.x * distance * dirY);
			/// -----
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