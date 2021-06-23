#include <Game.h>
#include <Player.h>
#include <Timeline.h>
#include <iostream>
#include <istream>
#include <string>
#include <sstream>
#include <thread>
#include <Event.h>
#include <Body.h>

bool gravity;

Game::Game() {
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Assignment 2 - Client", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);
	gameTime = *new Timeline(10);
	realTime = *new Timeline(1);

	if (!font.loadFromFile("res/ITCKRIST.ttf")) {
		std::cout << "ERROR\n";
	}

	bounds.push_back(new Boundary(sf::Vector2f(1200.f, 20.f), sf::Vector2f(0, 0), "res/dirt3.png"));
	bounds.push_back(new Boundary(sf::Vector2f(20.f, 680.f), sf::Vector2f(0, 20), "res/dirt3.png"));
	bounds.push_back(new Boundary(sf::Vector2f(1200.f, 20.f), sf::Vector2f(0, 700), "res/dirt3.png"));
	bounds.push_back(new Boundary(sf::Vector2f(20.f, 680.f), sf::Vector2f(1004, 20), "res/dirt3.png"));

	player = new Player(0, 20.f, "res/snake1.png");
	player->rb->setPosition(-40.f, -40.f);
	fruit = new Fruit(20.f, "yellow");

	//body.push_back(new Body(40.f, sf::Vector2f(-40.f, -40.f), "res/body.png"));

	scoreDisplay.setFont(font);
	scoreDisplay.setPosition(sf::Vector2f(10.f, 10.f));
	scoreDisplay.setCharacterSize(20);
	winDisplay.setString("Congratulations");
	winDisplay.setFont(font);
	winDisplay.setCharacterSize(60);
	winDisplay.setPosition(sf::Vector2f(200.f, 400.f));
	loseDisplay.setString("Game Over");
	loseDisplay.setFont(font);
	loseDisplay.setCharacterSize(60);
	loseDisplay.setPosition(sf::Vector2f(300.f, 325.f));
	windowFocus = 'Y';
	press = 0.f;
	started = 0.f;
}

void Game::run() {
	long lastTime = 0;
	long currentTime = 0;
	float arg[] = { 1 };
	eventQueue.push_back(Event(GAME_START, 1, gameTime.getTime(), arg));
	while (window.isOpen()) {
		sf::Event event;
		window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			window.close();/*
			float arg[] = { playerId - 1 };
			eventQueue.push_back(Event(GAME_EXIT, 1, gameTime.getTime(), arg));
			while(eventQueue.size()!=0){}*/
		}
			
		if (event.type == sf::Event::GainedFocus) {
			windowFocus = 'Y';
		}
		if (event.type == sf::Event::LostFocus) {
			windowFocus = 'N';
		}
		
		currentTime = gameTime.getTime();
		if ((currentTime - lastTime) > 1) {
			lastTime = currentTime;
			update();
			render();
		}
		
	}
}

void Game::update() {
	scoreDisplay.setString("Score = " + std::to_string(score));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&&(windowFocus=='Y')&&press == 0.f) {
		float arg[] = { 0 };
		eventQueue.push_back(Event(USER_INPUT, 1, gameTime.getTime(), arg));
		press = 1.f;
		clock.restart();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&(windowFocus == 'Y') && press == 0.f) {
		float arg[] = { 1 };
		eventQueue.push_back(Event(USER_INPUT, 1, gameTime.getTime(), arg));
		press = 1.f;
		clock.restart();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&&(windowFocus == 'Y') && press == 0.f)  {
		float arg[] = { 2 };
		eventQueue.push_back(Event(USER_INPUT, 1, gameTime.getTime(), arg));
		press = 1.f;
		clock.restart();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (windowFocus == 'Y') && press == 0.f) {
		float arg[] = { 3 };
		eventQueue.push_back(Event(USER_INPUT, 1, gameTime.getTime(), arg));
		press = 1.f;
		clock.restart();
	}
	else {
		sf::Time time = clock.getElapsedTime();
		if (time > sf::seconds(.4f))
			press = 0.f;
	}

	if (player->getPlayerStatus()>0) {
		scoreDisplay.setPosition(400.f, 500.f);
	}
}

void Game::updateScore(std::string scr) {
	score = std::stol(scr);
}

std::string Game::getEvent() {
	std::string eventString = "";
	if (eventQueue.size() != 0) {
		Event event = eventQueue.front();
		eventQueue.pop_front();
		eventString = event.eventToString();
	}
	return eventString;
}

void Game::maintainLength(int size){
	while (size > body.size()) {
		body.push_back(new Body(20.f, sf::Vector2f(-40.f,-40.f), "res/body.png"));
	}
}
void Game::serverUpdate(std::vector <std::string> data) {
	int iter = 1;
	std::string info = data.at(0);
	std::istringstream test(info);
	std::string score;
	std::string status;
	std::string posx;
	std::string posy;
	std::string rot;
	test >> score;
	test >> status;
	test >> posx;
	test >> posy;
	test >> rot;
	std::cout << status << "\n";
	updateScore(score);
	player->setPlayerStatus(std::stoi(status));
	player->rb->setPosition(sf::Vector2f(std::stof(posx), std::stof(posy)));
	player->rb->setRotation(std::stof(rot));
	info = data.at(iter);
	std::istringstream test1(info);
	test1 >> posx;
	test1 >> posy;
	fruit->rb->setPosition(sf::Vector2f(std::stof(posx), std::stof(posy)));
	iter++;
	info = data.at(iter);
	maintainLength(std::stoi(info));
	iter++;
	for (int i = 0; i < body.size(); i++) {
		info = data.at(iter);
		std::istringstream tmp(info);
		tmp >> posx;
		tmp >> posy;
		body[i]->rb->setPosition(sf::Vector2f(std::stof(posx), std::stof(posy)));
		iter++;
	}

}

int Game::peekEventQueue() {
	return eventQueue.size();
}


void Game::render() {
		window.clear();
		if (player->getPlayerStatus() == 0) {
			try {
				
			}
			catch (const std::exception& e) {

			}
			for (int i = 0; i < bounds.size(); i++) {
				window.draw(*(bounds[i]->rb));
			}
			window.draw(*(player->rb));
			for (int i = 0; i < body.size(); i++) {
				window.draw(*(body[i]->rb));
			}
			window.draw(*(fruit->rb));
			window.draw(scoreDisplay);
		}
		else if (player->getPlayerStatus() == 1) {
			window.draw(scoreDisplay);
			window.draw(loseDisplay);
		}
		else if (player->getPlayerStatus() == 2) {
			window.draw(scoreDisplay);
			window.draw(winDisplay);
		}
		
		window.display();
}
