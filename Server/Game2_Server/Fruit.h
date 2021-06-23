#pragma once
#include<GameObject.h>
class Fruit : public GameObject {
public:
	Fruit() {

	}

	Fruit(float side, std::string path) {
		rb = new RigidBody('S', side);
		rb->setOrigin(side / 2, side / 2);
		tb = new TextureObject(rb, path);
		rb->setPosition(-500.f,-500.f);
		status = 0;
	}

	void setPosition(sf::Vector2f pos) {
		rb->setPosition(pos);
	}

	int getStatus() {
		return status;
	}

	void setStatus(int s) {
		status = s;
	}

private:
	int status;
};