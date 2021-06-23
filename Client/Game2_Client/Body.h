#pragma once
#include<GameObject.h>
class Body : public GameObject {
public:
	Body() {

	}

	Body(float side, sf::Vector2f pos,std::string path) {
		rb = new RigidBody('S', side);
		rb->setOrigin(side / 2, side / 2);
		tb = new TextureObject(rb, path);
		rb->setPosition(pos);
		bdir = 0;
		bodyStatus = 0;
	}

	float getX() {
		return rb->getPosition().x;
	}

	float getY() {
		return rb->getPosition().y;
	}

	int getDirection() {
		return bdir;
	}
	int getStatus() {
		return bodyStatus;
	}
	
	void changeStatus() {
		if (bodyStatus == 0) {
			bodyStatus = 1;
		}
		else {
			bodyStatus = 0;
		}
	}

	float getDX() {
		return dpos.x;
	}

	float getDY() {
		return dpos.y;
	}

	int getDestinationSize() {
		return des.size();
	}

	void popDestination() {
		dpos = des.front();
		des.pop_front();
	}

	void setPosition(float x, float y) {
		rb->setPosition(sf::Vector2f(x, y));
	}


private:
	int bdir;
	int bodyStatus;
	std::list <sf::Vector2f> des;
	sf::Vector2f dpos;
};