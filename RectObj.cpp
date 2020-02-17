#include "RectObj.h"


RectObj::RectObj(sf::Color color, float x, float y)
{
	object.setSize(sf::Vector2f(x, y));
	object.setOrigin(object.getGlobalBounds().width / 2, object.getGlobalBounds().height / 2);
	object.setFillColor(color);
}

void RectObj::calculateCornersPos()
{
	sf::FloatRect spriteBounds = object.getLocalBounds();

	topLeftCorner = object.getTransform().transformPoint(sf::Vector2f(spriteBounds.left, spriteBounds.top));
	topRightCorner = object.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + spriteBounds.width, spriteBounds.top));
	bottomRightCorner = object.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + spriteBounds.width, spriteBounds.top + spriteBounds.height));
	bottomLeftCorner = object.getTransform().transformPoint(sf::Vector2f(spriteBounds.left, spriteBounds.top + spriteBounds.height));
}

void RectObj::showCollisionArea()
{
	sf::Vertex points[5] = { topLeftCorner, topRightCorner, bottomRightCorner, bottomLeftCorner, topLeftCorner };
	collisionArea = new sf::VertexArray(sf::LineStrip, 5);

	for (int i = 0; i < 5; i++)
	{
		(*collisionArea)[i].position = points[i].position;
	}
}
