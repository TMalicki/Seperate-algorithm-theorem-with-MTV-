#ifndef SAT_H
#define SAT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "RectObj.h"

class SAT 
{
private:
	sf::Vector2f vectorABobj1;
	sf::Vector2f vectorBCobj1;
	sf::Vector2f vectorABobj2;
	sf::Vector2f vectorBCobj2;

	sf::Vector2f normVectorABobj1;
	sf::Vector2f normVectorBCobj1;
	sf::Vector2f normVectorABobj2;
	sf::Vector2f normVectorBCobj2;

	float projectionVertexObj1[4];
	float projectionVertexObj2[4];

	float obj1Min;
	float obj1Max;
	float obj2Min;
	float obj2Max;

	float distance = 0.0;
	int oppositeCounter = 1;
public:
	//SAT() {};

	void setProjectionVector(sf::VertexArray*, sf::VertexArray*);
	void setNormalVector(sf::Vector2f&, sf::Vector2f&);
	void setProjectionVertex(float*, sf::Vector2f&, sf::VertexArray*);
	void searchMinMax(float&, float&, float*);
	void normalize(sf::Vector2f&);
	bool collisionSAT(RectObj&, RectObj&);
	
	sf::Vector2f& getVectorABobj1() { return vectorABobj1; }
	sf::Vector2f& getVectorBCobj1() { return vectorBCobj1; }
	sf::Vector2f& getVectorABobj2() { return vectorABobj2; }
	sf::Vector2f& getVectorBCobj2() { return vectorBCobj2; }

	std::vector<sf::Vector2f> getVectorProjection();

	void calculateMTV(int );
	float getDepthCollision() { return distance; }
	int getVectorOfCollision() { return oppositeCounter; }

	virtual ~SAT() {};
};

#endif
