#pragma once
#include<SFML/Graphics.hpp>
#include<Boundary.h>
#include<Player.h>
#include<Timeline.h>
#include<Event.h>
#include<Body.h>
#include<list>
#include<Fruit.h>

#define WIDTH 1024
#define HEIGHT 720

class Game {
public:	
		Game();
		void run();
		void serverUpdate(std::vector<std::string> data);
		std::string getEvent();
		int peekEventQueue();
		void maintainLength(int size);


		float started;
private:
	
	void render();
	void update();
	void updateScore(std::string scr);
	sf::RenderWindow window;
	sf::Font font;

	sf::Text scoreDisplay;
	sf::Text winDisplay;
	sf::Text loseDisplay;
	std::list<Event> eventQueue;

	Player* player;
	vector<Body*> body;
	vector<Boundary*> bounds;
	Fruit* fruit;

	Timeline gameTime;
	Timeline realTime;
	sf::Clock clock;

	char windowFocus;
	float press;
	long score;
	
};