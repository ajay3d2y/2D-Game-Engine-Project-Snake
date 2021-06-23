#pragma once
#include<GameObject.h>
#include<Event.h>
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

	void setDirection(int a) {
		bdir = a;
	}
	int getStatus() {
		return bodyStatus;
	}
	
	void addDestination(sf::Vector2f loc) {
		dpos = loc;
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

	void onEvent(Event e) {
		if (e.eType == DIRECTION_CHANGE) {
			des.push_back(sf::Vector2f(e.argList[0], e.argList[1]));
		}
	}

private:
	int bdir;
	int bodyStatus;
	std::list <sf::Vector2f> des;
	sf::Vector2f dpos;
};