#ifndef RECTOBJ_H
#define RECTOBJ_H

#include <SFML/Graphics.hpp>

class RectObj
{
private:
	sf::RectangleShape object;

	sf::Vector2f topLeftCorner;
	sf::Vector2f topRightCorner;
	sf::Vector2f bottomRightCorner;
	sf::Vector2f bottomLeftCorner;

	sf::VertexArray* collisionArea;

public:
	RectObj(sf::Color color, float x = 100.0f, float y = 100.0f);
	sf::RectangleShape& getObjShape() { return object; }
	
	void calculateCornersPos();
	void showCollisionArea();
	sf::VertexArray* getCollisionArea() { return collisionArea; }
};


#endif
