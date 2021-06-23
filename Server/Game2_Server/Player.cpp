#include<Player.h>
#include<EventManager.h>


Player::Player() {

}

Player::Player(int id,float side, std::string path) {
	rb = new RigidBody('S', side);
	rb->setOrigin(side / 2, side / 2);
	tb = new TextureObject(rb, path);
	playerDir = id;
	playerStatus = -1;
	playerGrow = 0;
}

Event Player::getEvent() {
	Event tst = pQueue.top();
	pQueue.pop();
	return tst;
}

int Player::getGrow() {
	return playerGrow;
}

void Player::setGrow(int g) {
	playerGrow = g;
}

int Player::getQueueSize() {
	return pQueue.size();
}

int Player::getPlayerStatus() {
	return playerStatus;
}

void Player::setPlayerStatus(int st) {
	playerStatus = st;
}

void Player::setPointer(Fruit* f, std::vector<Body*>* tb, std::vector<Boundary*>* tbounds) {
	fr = f;
	b = tb;
	bounds = tbounds;
}

float Player::getX() {
	return rb->getPosition().x;
}

float Player::getY() {
	return rb->getPosition().y;
}

int Player::getDirection() {
	return playerDir;
}

void Player::setPos(float x, float y) {
	rb->setPosition(sf::Vector2f(x, y));
}

void Player::onEvent(Event event) {
	if (event.eType == USER_INPUT) {
		if (event.argList[0] == 0) {
			if ((playerDir == 1) || (playerDir == 3)) {
				if (playerDir == 1) {
					rb->rotate(-90.f);
				}
				else {
					rb->rotate(90.f);
				}
				playerDir = 0;
				float arg[] = { rb->getPosition().x,rb->getPosition().y };
				pQueue.push(Event(DIRECTION_CHANGE, 2, 0, arg));
			}
		}
		else if (event.argList[0] == 1) {
			if ((playerDir == 0) || (playerDir == 2)) {
				if (playerDir == 2) {
					rb->rotate(-90.f);
				}
				else {
					rb->rotate(90.f);
				}
				playerDir = 1;
				float arg[] = { rb->getPosition().x,rb->getPosition().y };
				pQueue.push(Event(DIRECTION_CHANGE, 2, 0, arg));
			}
		}
		else if(event.argList[0]==2){
			if ((playerDir == 1) || (playerDir == 3)) {
				if (playerDir == 3) {
					rb->rotate(-90.f);
				}
				else {
					rb->rotate(90.f);
				}
				playerDir = 2;
				float arg[] = { rb->getPosition().x,rb->getPosition().y };
				pQueue.push(Event(DIRECTION_CHANGE, 2, 0, arg));
			}
		}
		else if (event.argList[0] == 3) {
			if ((playerDir == 0) || (playerDir == 2)) {
				if (playerDir == 0) {
					rb->rotate(-90.f);
				}
				else {
					rb->rotate(90.f);
				}
				playerDir = 3;
				float arg[] = { rb->getPosition().x,rb->getPosition().y };
				pQueue.push(Event(DIRECTION_CHANGE, 2, 0, arg));
			}
		}
	}
	else if (event.eType == PLAYER_DEAD) {
		playerStatus = 1;
	}
	else if (event.eType == PLAYER_WIN) {
		playerStatus = 2;
	}
}

void Player::checkHit() {
	if (rb->getGlobalBounds().intersects(fr->rb->getGlobalBounds())) {
		float arg[] = {1};
		pQueue.push(Event(EAT, 1, 0, arg));
	}
	int size = b->size() - 2;
	for (int i = 0; i < size;i++) {
		Body* tmp = b->at(i);
		if (rb->getGlobalBounds().intersects(tmp->rb->getGlobalBounds())) {
			std::cout << "HIT " << i;
			float arg[] = { 1 };
			pQueue.push(Event(PLAYER_DEAD, 0, 0, arg));
		}
	}
	for (int i = 0; i < bounds->size(); i++) {
		Boundary* tmp = bounds->at(i);
		if (rb->getGlobalBounds().intersects(tmp->rb->getGlobalBounds())) {
			float arg[] = { 1 };
			pQueue.push(Event(PLAYER_DEAD, 0, 0, arg));
		}
	}

}

//void Player::setPointers(std::vector<Platform*>* tpf, std::vector<MovPlatform*>* tmpf, std::vector<DeathZone*>* tdz,Timeline* gT) {
//	pf = tpf;
//	mpf = tmpf;
//	dz = tdz;
//	gameTime = gT;
//}