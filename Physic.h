#ifndef PHYSIC_H
#define PHYSIC_H

#include <SFML/Graphics.hpp>
#include "RectObj.h"
#include "SAT.h"

class Physic 
{
private:
	RectObj obj1;
	RectObj obj2;
	RectObj temp;
	SAT sat;
	sf::Clock clock;
	float dt;
	float delay;
public:
	Physic();

	void play(sf::RenderWindow&);
	void update(sf::RenderWindow&);

	sf::Vector2f calculateMoveValue(RectObj& obj1, RectObj& obj2, SAT& sat);
	void boarderCheck(RectObj& obj1, RectObj& obj2, sf::Vector2i windowSize, sf::Vector2f moveValue);
};


#endif