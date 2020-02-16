#include "SAT.h"


void SAT::setProjectionVector(sf::VertexArray* obj1, sf::VertexArray* obj2)
{
	/// 0 - topLeftCorner; 1 - topRightCorner; 2 - bottomRightCorner; 3 - bottomLeftCorner
	vectorABobj1 = sf::Vector2f((*obj1)[1].position.x - (*obj1)[0].position.x, (*obj1)[1].position.y - (*obj1)[0].position.y);
	vectorBCobj1 = sf::Vector2f((*obj1)[2].position.x - (*obj1)[1].position.x, (*obj1)[2].position.y - (*obj1)[1].position.y);
	vectorABobj2 = sf::Vector2f((*obj2)[1].position.x - (*obj2)[0].position.x, (*obj2)[1].position.y - (*obj2)[0].position.y);
	vectorBCobj2 = sf::Vector2f((*obj2)[2].position.x - (*obj2)[1].position.x, (*obj2)[2].position.y - (*obj2)[1].position.y);
}

void SAT::setNormalVector(sf::Vector2f& normVector, sf::Vector2f& vector)
{
	normVector = sf::Vector2f(-vector.y, vector.x);
}

void SAT::setProjectionVertex(sf::Vector2f& normVector, sf::VertexArray* obj)
{
	/// 0 - topLeftCorner; 1 - topRightCorner; 2 - bottomRightCorner; 3 - bottomLeftCorner
	for (int i = 0; i < 4; i++)
	{
		projectionVertexObj1[i] = normVector.x * (*obj)[i].position.x + normVector.y * (*obj)[i].position.y;
	}
}

void SAT::searchMinMax(float& objMin, float& objMax, float* projectionVertexObj)
{
	objMin = projectionVertexObj[0];
	objMax = projectionVertexObj[0];
	for (int i = 1; i < 4; i++)
	{
		if (objMin > projectionVertexObj[i]) objMin = projectionVertexObj[i];
		if (objMax < projectionVertexObj[i]) objMax = projectionVertexObj[i];
	}
}

bool SAT::collisionSAT(RectObj& obj1, RectObj& obj2)
{
		bool collided = true;
		int counter = 1;
		/// vertexes of object 1 are: a - topleftcorner, b - toprightcorner, c - bottomrightcorner, d - bottomleftcorner (clockwise)
		/// vertexes of object 2 are: e, f, g, h (clockwise)
		setProjectionVector(obj1.getCollisionArea(), obj2.getCollisionArea());

		setNormalVector(normVectorABobj1, getVectorABobj1());
		setNormalVector(normVectorBCobj1, getVectorBCobj1());
		setNormalVector(normVectorABobj2, getVectorABobj2());
		setNormalVector(normVectorBCobj2, getVectorBCobj2());

		sf::Vector2f normVector;

		while (collided == true && counter <= 4)
		{
			/// for normvectorabplayer
			if (counter == 1) normVector = normVectorABobj1;
			/// for normvectorbcplayer
			else if (counter == 2) normVector = normVectorBCobj1;
			/// for normvectoreftraffic
			else if (counter == 3) normVector = normVectorABobj2;
			/// for normvectorghtraffic
			else if (counter == 4) normVector = normVectorBCobj2;
	
			setProjectionVertex(normVector, obj1.getCollisionArea());
			searchMinMax(obj1Min, obj1Max, projectionVertexObj1);

			setProjectionVertex(normVector, obj2.getCollisionArea());
			searchMinMax(obj2Min, obj2Max, projectionVertexObj2);
	
			std::cout << obj1Min << " " << obj1Max << std::endl;
			std::cout << obj2Min << " " << obj2Max << std::endl;

			/// negation
			if (!(((obj1Min < obj2Max) && (obj1Min > obj2Min)) || ((obj2Min < obj1Max) && (obj2Min > obj1Min))))
			{
				collided = false;
			}
			counter++;
		}
		return collided;
}
