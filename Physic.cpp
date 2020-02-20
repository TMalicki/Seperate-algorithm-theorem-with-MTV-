#include "Physic.h"

Physic::Physic() : obj1{ sf::Color::Red }, obj2{ sf::Color::Green }, temp{ sf::Color::Green }
{
	obj2.getObjShape().setPosition(400, 300);	// set obj2 in the middle possition
	temp.getObjShape().setPosition(obj2.getObjShape().getPosition());	// temp object has to have the same position as obj2
	delay = 0.0;
}

void Physic::play(sf::RenderWindow& window)
{
	dt = clock.restart().asSeconds();
	obj1.getObjShape().setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

	sf::Vector2i windowSize = sf::Vector2i(window.getSize());
	
	// update position of temp object
	if (delay > 0.5)
	{
		temp.getObjShape().setPosition(obj2.getObjShape().getPosition());
		temp.getObjShape().setFillColor(sf::Color::Green);
		delay = 0.0;
	}
	// check if collision is detected if yes than:
	if (sat.collisionSAT(obj1, obj2))
	{
		sf::Vector2f obj2pos = obj2.getObjShape().getPosition();
		sf::Vector2f tempPos = temp.getObjShape().getPosition();
		
		// check if position of obj2 is greater than temp object by 50. 
		// thanks to this temp object is showing as previous state of obj2
		if(abs(obj2pos.x - tempPos.x) + abs(obj2pos.y - tempPos.y) > 50)
			temp.getObjShape().setPosition(obj2pos);

		// moveValue - destination of obj2 calculated based on MTV (depth during collision)
		sf::Vector2f moveValue = calculateMoveValue(obj1, obj2, sat);
		obj2.getObjShape().move(moveValue.x * dt * 62, moveValue.y * dt * 62);
		temp.getObjShape().setFillColor(sf::Color(3, 252, 165, 100));
		obj2.getObjShape().setOutlineColor(sf::Color::Red);
		boarderCheck(obj1, obj2, windowSize, moveValue);
	}

	obj1.getObjShape().rotate(2 * dt * 62);
	obj2.getObjShape().rotate(-2 * dt * 62);
	temp.getObjShape().rotate(-2 * dt * 62);
	delay += dt;
}

void Physic::update(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	window.draw(obj1.getObjShape());
	window.draw(obj2.getObjShape());
	window.draw(temp.getObjShape());
	window.display();
}

sf::Vector2f Physic::calculateMoveValue(RectObj& obj1, RectObj& obj2, SAT& sat)
{
	float distance = sat.getDepthCollision(); // minimum depth of collision between obj1 and obj2
	int vect = sat.getVectorOfCollision();	  // vector in which collision is detected (it could be 
						  // normal to AB or BC of obj1 or obj2
	
	sf::Vector2f moveCoord = sat.getVectorProjection()[vect - 1];

	sat.normalize(moveCoord);

	// calculate direction in which obj2 should move (it is for correct sign)
	sf::Vector2f posObj1 = obj1.getObjShape().getPosition();
	sf::Vector2f posObj2 = obj2.getObjShape().getPosition();
	int dirX = -(posObj1.x - posObj2.x) / abs(posObj1.x - posObj2.x);
	int dirY = -(posObj1.y - posObj2.y) / abs(posObj1.y - posObj2.y);
	// ----------------------------------------------------------------------
	
	// final destination of obj2 based on MTV 
	moveCoord.x = moveCoord.x * dirX * distance;
	moveCoord.y = moveCoord.y * dirY * distance;
	// ---------------------------------------------
	
	return moveCoord;
}

// check if obj2 is inside window borders
void Physic::boarderCheck(RectObj& obj1, RectObj& obj2, sf::Vector2i windowSize, sf::Vector2f moveValue)
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
