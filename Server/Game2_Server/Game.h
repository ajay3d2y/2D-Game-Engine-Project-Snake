#pragma once
#include<SFML/Graphics.hpp>
#include<Player.h>
#include<Body.h>
#include<Boundary.h>
#include<Fruit.h>
#include<Timeline.h>
#include<Event.h>
#include<list>
#include<string>
#include<queue>
#include<ScriptManager.h>
#include<time.h>
#include <dukglue/dukglue.h>

#define WIDTH 1024
#define HEIGHT 720
#define sleep(n)    Sleep(n)
class Game {
public:	
		Game();
		void run();
		std::vector<std::string> getData();
		void onEvent(Event event);
		void start();
		void recvEvent(std::string eventStr);
		void fruitCheck();
		void growCheck();
		
private:
	void render();
	void update();
	sf::RenderWindow window;

	sf::Vector2f growPos;

	Player* player;
	Fruit* fruit;
	vector<Body*> body;
	vector<Boundary*> bounds;

	//std::list<Event> eventQueue;
	std::priority_queue<Event, vector<Event>, less<vector<Event>::value_type>> eventQueue;
	Timeline gameTime;
	Timeline realTime;
	ScriptManager sc;


	long lastTime;
	long lastFruit;
	long score;
	int press = 0;
};