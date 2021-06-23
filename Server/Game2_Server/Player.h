#pragma once
#include <SFML/Graphics.hpp>
#include <GameObject.h>
#include <iostream>
#include <list>
#include <queue>
#include<Event.h>
#include<Fruit.h>
#include<Timeline.h>
#include<Body.h>
#include<Boundary.h>

class Player : public GameObject
{
public:
	Player();
	Player(int id,float side, std::string path);
	void onEvent(Event event);
	Event getEvent();
	int getQueueSize();
	int getPlayerStatus();
	void setPlayerStatus(int st);
	void setPointer(Fruit* f, std::vector<Body*>* tb, std::vector<Boundary*>* tbounds);
	void checkHit();
	float getX();
	float getY();
	int getDirection();
	int getGrow();
	void setGrow(int g);
	void setPos(float x, float y);
private:
	sf::Vector2f drawPoint;
	sf::Vector2f growDes;
	sf::Texture playerTexture;
	int playerDir;
	int playerStatus;
	int playerGrow;
	std::priority_queue<Event, vector<Event>, greater<vector<Event>::value_type>> pQueue;
	Timeline* gameTime;
	Fruit* fr;
	std::vector<Body*>* b;
	std::vector<Boundary*>* bounds;
};