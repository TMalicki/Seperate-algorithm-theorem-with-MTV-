#ifndef SAT_H
#define SAT_H

#include <iostream>
#include <SFML/Graphics.hpp>
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

public:
	SAT() {};

	void setProjectionVector(sf::VertexArray*, sf::VertexArray*);
	void setNormalVector(sf::Vector2f&, sf::Vector2f&);
	void setProjectionVertex(sf::Vector2f&, sf::VertexArray*);
	void searchMinMax(float&, float&, float*);
	bool collisionSAT(RectObj&, RectObj&);
	
	sf::Vector2f& getVectorABobj1() { return vectorABobj1; }
	sf::Vector2f& getVectorBCobj1() { return vectorBCobj1; }
	sf::Vector2f& getVectorABobj2() { return vectorABobj2; }
	sf::Vector2f& getVectorBCobj2() { return vectorBCobj2; }


	virtual ~SAT() {};
};

#endif

//bool Player::collisionSAT(Car* traffic)
//{
//	bool collided = true;
//	int counter = 1;
//	/// vertexes of player object are: A - topLeftCorner, B - topRightCorner, C - bottomRightCorner, D - bottomLeftCorner (clockwise)
//	/// vertexes od traffic Car object are: E, F, G, H (clockwise)
//
//	sf::FloatRect trafficCar = traffic->getSprite().getGlobalBounds();
//	sf::Vector2f trafficTopLeftCorner = sf::Vector2f(trafficCar.left, trafficCar.top);
//	sf::Vector2f trafficTopRightCorner = sf::Vector2f(trafficCar.left + trafficCar.width, trafficCar.top);
//	sf::Vector2f trafficBottomRightCorner = sf::Vector2f(trafficCar.left + trafficCar.width, trafficCar.top + trafficCar.height);
//	sf::Vector2f trafficBottomLeftCorner = sf::Vector2f(trafficCar.left, trafficCar.top + trafficCar.height);
//
//	sf::Vector2f vectorABplayer = sf::Vector2f(topRightCorner.x - topLeftCorner.x, topRightCorner.y - topLeftCorner.y);
//	sf::Vector2f vectorBCplayer = sf::Vector2f(bottomRightCorner.x - topRightCorner.x, bottomRightCorner.y - topRightCorner.y);
//	sf::Vector2f vectorEFtraffic = sf::Vector2f(trafficTopRightCorner.x - trafficTopLeftCorner.x, trafficTopRightCorner.y - trafficTopLeftCorner.y);
//	sf::Vector2f vectorGHtraffic = sf::Vector2f(trafficBottomRightCorner.x - trafficTopRightCorner.x, trafficBottomRightCorner.y - trafficTopRightCorner.y);
//
//	sf::Vector2f normVectorABplayer = sf::Vector2f(-vectorABplayer.y, vectorABplayer.x);
//	sf::Vector2f normVectorBCplayer = sf::Vector2f(-vectorBCplayer.y, vectorBCplayer.x);
//	sf::Vector2f normVectorEFtraffic = sf::Vector2f(-vectorEFtraffic.y, vectorEFtraffic.x);
//	sf::Vector2f normVectorGHtraffic = sf::Vector2f(-vectorGHtraffic.y, vectorGHtraffic.x);
//
//	sf::Vector2f normVector;
//
//	float projectionVertexABCD[4];
//	float projectionVertexEFGH[4];
//
//	float playerMin;
//	float playerMax;
//	float trafficMin;
//	float trafficMax;
//
//	using namespace std;
//
//	while (collided == true && counter <= 4)
//	{
//		/// for normVectorABplayer
//		if (counter == 1) normVector = normVectorABplayer;
//		/// for normVectorBCplayer
//		else if (counter == 2) normVector = normVectorBCplayer;
//		/// for normVectorEFtraffic
//		else if (counter == 3) normVector = normVectorEFtraffic;
//		/// for normVectorGHtraffic
//		else if (counter == 4) normVector = normVectorGHtraffic;
//
//		projectionVertexABCD[0] = normVector.x * topLeftCorner.x + normVector.y * topLeftCorner.y;
//		projectionVertexABCD[1] = normVector.x * topRightCorner.x + normVector.y * topRightCorner.y;
//		projectionVertexABCD[2] = normVector.x * bottomRightCorner.x + normVector.y * bottomRightCorner.y;
//		projectionVertexABCD[3] = normVector.x * bottomLeftCorner.x + normVector.y * bottomLeftCorner.y;
//
//		playerMin = projectionVertexABCD[0];
//		playerMax = projectionVertexABCD[0];
//		for (int i = 1; i < 4; i++)
//		{
//			if (playerMin > projectionVertexABCD[i]) playerMin = projectionVertexABCD[i];
//			if (playerMax < projectionVertexABCD[i]) playerMax = projectionVertexABCD[i];
//		}
//
//		projectionVertexEFGH[0] = normVector.x * trafficTopLeftCorner.x + normVector.y * trafficTopLeftCorner.y;
//		projectionVertexEFGH[1] = normVector.x * trafficTopRightCorner.x + normVector.y * trafficTopRightCorner.y;
//		projectionVertexEFGH[2] = normVector.x * trafficBottomRightCorner.x + normVector.y * trafficBottomRightCorner.y;
//		projectionVertexEFGH[3] = normVector.x * trafficBottomLeftCorner.x + normVector.y * trafficBottomLeftCorner.y;
//
//		trafficMin = projectionVertexEFGH[0];
//		trafficMax = projectionVertexEFGH[0];
//		for (int i = 1; i < 4; i++)
//		{
//			if (trafficMin > projectionVertexEFGH[i]) trafficMin = projectionVertexEFGH[i];
//			if (trafficMax < projectionVertexEFGH[i]) trafficMax = projectionVertexEFGH[i];
//		}
//
//		/// negation
//		if (!(((playerMin < trafficMax) && (playerMin > trafficMin)) || ((trafficMin < playerMax) && (trafficMin > playerMin))))
//		{
//			collided = false;
//		}
//		counter++;
//
//		cout << "Counter: " << counter << endl;
//		cout << " topLeftCorner: X: " << topLeftCorner.x << " Y: " << topLeftCorner.y << endl;
//		cout << " bottomLeftCorner: X: " << bottomLeftCorner.x << " Y: " << bottomLeftCorner.y << endl;
//		cout << " trafficTopLeftCorner: X: " << trafficTopLeftCorner.x << " Y: " << trafficTopLeftCorner.y << endl;
//		cout << " trafficBottomLeftCorner: X: " << trafficBottomLeftCorner.x << " Y: " << trafficBottomLeftCorner.y << endl;
//	}
//	return collided;
//}