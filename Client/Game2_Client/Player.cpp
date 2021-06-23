#include<Player.h>


Player::Player() {

}

Player::Player(int id,float side, std::string path) {
	rb = new RigidBody('S', side);
	rb->setOrigin(side / 2, side / 2);
	tb = new TextureObject(rb, path);
	playerDir = id;
	playerStatus = 0;
}

Event Player::getEvent() {
	Event tst = pQueue.top();
	pQueue.pop();
	return tst;
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

void Player::setPointer() {
}

void Player::checkHit() {
	
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

}

//void Player::setPointers(std::vector<Platform*>* tpf, std::vector<MovPlatform*>* tmpf, std::vector<DeathZone*>* tdz,Timeline* gT) {
//	pf = tpf;
//	mpf = tmpf;
//	dz = tdz;
//	gameTime = gT;
//}