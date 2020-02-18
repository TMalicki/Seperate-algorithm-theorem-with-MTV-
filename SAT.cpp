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

void SAT::setProjectionVertex(float* projectionVertexObj, sf::Vector2f& normVector, sf::VertexArray* obj)
{
	/// 0 - topLeftCorner; 1 - topRightCorner; 2 - bottomRightCorner; 3 - bottomLeftCorner
	for (int i = 0; i < 4; i++)
	{
		sf::Vector2f pos = (*obj)[i].position;
		projectionVertexObj[i] = (normVector.x * pos.x + normVector.y * pos.y) / sqrt(pow(normVector.x, 2.0) + pow(normVector.y, 2.0));
	}
	//std::cout << (*obj)[1].position.x << std::endl;
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
	using std::cout; using std::endl;


		bool collided = true;
		int counter = 1;

		obj1.calculateCornersPos();
		obj2.calculateCornersPos();

		obj1.showCollisionArea();
		obj2.showCollisionArea();

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
	
			setProjectionVertex(projectionVertexObj1, normVector, obj1.getCollisionArea());
			searchMinMax(obj1Min, obj1Max, projectionVertexObj1);

			setProjectionVertex(projectionVertexObj2, normVector, obj2.getCollisionArea());
			searchMinMax(obj2Min, obj2Max, projectionVertexObj2);

			/// negation of collision
			//int distance = obj2Max - obj1Min;
			//int distance = 
			if (!(((obj1Min < obj2Max) && (obj1Min > obj2Min)) || ((obj2Min < obj1Max) && (obj2Min > obj1Min))))
			{
				collided = false;
			}

			if (counter == 1)
			{
				distance = abs(obj1Max - obj2Min);
				if (distance > abs(obj2Max - obj1Min)) distance = abs(obj2Max - obj1Min);
			}
			else
			{
				if (distance > abs(obj1Max - obj2Min))
				{
					distance = abs(obj1Max - obj2Min);
					oppositeCounter = counter;
				}
				if (distance > abs(obj2Max - obj1Min))
				{
					distance = abs(obj2Max - obj1Min);
					oppositeCounter = counter;
				}
			}


			counter++;

			//std::cout << "position: " << obj1.getObjShape().getPosition().y << std::endl;
			//std::cout << counter << " : " << obj1Max - obj2Min << std::endl

			//	cout << "counter: " << counter << " Obj1Max: " << obj1Max - obj2Min << endl;
				//cout << "counter: " << counter << " Obj1Min: " << obj1Min << endl;
			//	cout << "counter: " << counter << " Obj2Max: " << obj2Max - obj1Min << endl;
				//cout << "counter: " << counter << " Obj2Min: " << obj2Min << endl;
			//	cout << "collided: " << collided << endl;
		}

		cout << distance << endl;
		cout << oppositeCounter << endl;



		//obj2.getObjShape().move(x, y);


		return collided;
}
