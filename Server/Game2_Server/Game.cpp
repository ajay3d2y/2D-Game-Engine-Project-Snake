#include <Game.h>
#include <Player.h>
#include <Timeline.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <thread>
#include <Event.h>
#include <EventManager.h>
#include <dukglue/dukglue.h>
#include<ScriptManager.h>
bool gravity;

EventManager em;

Game::Game() {
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Assignment 2 - Server", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);
	gameTime = *new Timeline(10);
	realTime = *new Timeline(1);
	bounds.push_back(new Boundary(sf::Vector2f(1200.f, 20.f), sf::Vector2f(0, 0), "res/dirt3.png"));
	bounds.push_back(new Boundary(sf::Vector2f(20.f, 680.f), sf::Vector2f(0, 20), "res/dirt3.png"));
	bounds.push_back(new Boundary(sf::Vector2f(1200.f, 20.f), sf::Vector2f(0, 700), "res/dirt3.png"));
	bounds.push_back(new Boundary(sf::Vector2f(20.f, 680.f), sf::Vector2f(1004, 20), "res/dirt3.png"));
	player = new Player(0, 20.f, "res/snake1.png");
	player->rb->setPosition(512.f, 600.f);
	fruit = new Fruit(20.f, "yellow");
	fruit->rb->setPosition(200.f, 200.f);
	player->setPointer(fruit,&body,&bounds);
	body.push_back(new Body(20.f,sf::Vector2f(512.f,620.f), "res/body.png"));
	press = 0;
	lastTime = 0;
	em = *new EventManager(&sc, this, player,&body,&gameTime);
	sc = *new ScriptManager();
	score = 0;
	std::this_thread::sleep_for(std::chrono::seconds(5));
}

void Game::start() {
	gameTime.switchPause();
}

void Game::run() {
	long currentTime = 0;
	long rcurrentTime = 0;
	long lastTime = 0;
	while (window.isOpen()) {
		sf::Event event;
		window.pollEvent(event);
		if (event.type == sf::Event::Closed)
			window.close();
		currentTime = gameTime.getTime();
		if ((currentTime - lastTime) > 1) {
			//std::cout << currentTime << "\n";
			lastTime = currentTime;
			update();
			em.eventDispatch();
			render();
		}
	}
}

void Game::fruitCheck() {
	if (fruit->getStatus() == 0) {
		double r1 = ((double)rand() / (RAND_MAX));
		double r2 = ((double)rand() / (RAND_MAX));
		double x = 40.f + r1 * (1024 - 120);
		double y = 40.f + r2 * (720 - 60);
		fruit->setPosition(sf::Vector2f(x, y));
		fruit->setStatus(1);
	}
}

void Game::growCheck() {
	if (lastFruit == 4) {
		player->setGrow(0);
		body.push_back(new Body(20.f, sf::Vector2f(growPos), "res/body.png"));
		/*int last = body.size() - 1;
		if (body[last-1]->getStatus() == 1) {
			sf::Vector2f pos(body[last - 1]->getDX(), body[last - 1]->getDY());
			body[last]->changeStatus();
			body[last]->addDestination(pos);
		}*/
	}
	else {
		lastFruit++;
	}
}

void Game::update() {
	if (player->getPlayerStatus() == 0) {
		sc.setupScript("Move.js");
		sc.movPlayer(player);
		if (player->getGrow() == 0) {
			for (int i = 0; i < body.size(); i++) {
				sc.movBody(body[i], player);
			}
		}
		else {
			growCheck();
		}
		fruitCheck();
		player->checkHit();
	}

}

void Game::render() {
		window.clear();
		if (player->getPlayerStatus() == 0) {
			for (int i = 0; i < bounds.size(); i++) {
				window.draw(*(bounds[i]->rb));
			}
			window.draw(*(player->rb));
			for (int i = 0; i < body.size(); i++) {
				window.draw(*(body[i]->rb));
			}
			window.draw(*(fruit->rb));
		}
		else {

		}
		
		window.display();
}

void Game::recvEvent(std::string eventStr) {
	long time = gameTime.getTime();
	em.enterQueue(Event(eventStr, time));
}

void Game::onEvent(Event event) {
	if (event.eType == EAT) {
		fruit->rb->setPosition(-40.f, -40.f);
		fruit->setStatus(0);
		growPos = player->rb->getPosition();
		player->setGrow(1);
		lastFruit = 0;
		score = score + 50;

	}
	else if (event.eType == GAME_START) {
		player->setPlayerStatus(0);
	}
}

std::vector<std::string> Game::getData() {
	std::vector<std::string> vec;
	sf::Vector2f data = player->rb->getPosition();
	float rot = player->rb->getRotation();
	std::string datastr = std::to_string(score)+" "+std::to_string(player->getPlayerStatus()) + " " + std::to_string(data.x) + " " + std::to_string(data.y)+" "+std::to_string(rot);
	vec.push_back(datastr);
	data = fruit->rb->getPosition();
	datastr = std::to_string(data.x) + " " + std::to_string(data.y);
	vec.push_back(datastr);
	datastr = std::to_string(body.size());
	vec.push_back(datastr);
	for (int i = 0; i < body.size(); i++) {
		data = body[i]->rb->getPosition();
		datastr = std::to_string(data.x) + " " + std::to_string(data.y);
		vec.push_back(datastr);
	}
	return vec;
}