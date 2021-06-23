#pragma once
#include <SFML/Graphics.hpp>
#include <GameObject.h>
#include <iostream>
#include <list>
#include <queue>
#include<Event.h>
#include<Timeline.h>

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
	void setPointer();
	void checkHit();
	float getX();
	float getY();
	int getDirection();
	void setPos(float x, float y);
private:
	sf::Vector2f drawPoint;
	sf::Texture playerTexture;
	int playerDir;
	int playerStatus;
	std::priority_queue<Event, vector<Event>, greater<vector<Event>::value_type>> pQueue;
	Timeline* gameTime;
};