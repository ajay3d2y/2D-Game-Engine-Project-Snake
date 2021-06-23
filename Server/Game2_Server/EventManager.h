#pragma once
#include<queue>
#include<Event.h>
#include<Player.h>
#include<Body.h>
#include<Timeline.h>
#include<fstream>
#include<streambuf>
#include<Game.h>
#include <dukglue/dukglue.h>
#include <ScriptManager.h>
class EventManager {
public:
	EventManager() {

	}
	EventManager(ScriptManager* sc1,Game *gc1, Player *p, std::vector<Body*>* tb,Timeline *tgameTime ) {
		player = p;
		eventTime = tgameTime;
		gc = gc1;
		sc = sc1;
		b = tb;
		flag = 0;
	}

	void enterQueue(Event e) {
		while(flag!=0){}
		flag = 1;
		eventQueue.push(e);
		flag = 0;
	}

	void eventDispatch() {
		retrieveEvents();
		if (eventQueue.size() != 0) {
			while(flag!=0){}
			flag = 1;
			Event event = eventQueue.top();
			flag = 0;
			while (eventQueue.size() != 0 && event.timeStamp < eventTime->getTime()) {
				while (flag != 0) {
				}
				flag = 1;
				eventQueue.pop();
				flag = 0;
				if (event.eType == USER_INPUT) {
					if (player->getGrow() == 0) {
						player->onEvent(event);
					}
					else {
						event.timeStamp = eventTime->getTime() + 5;
						enterQueue(event);
					}
				}
				else if (event.eType == PLAYER_DEAD) {
					player->onEvent(event);
				}
				else if (event.eType == GAME_START||event.eType == EAT) {
					gc->onEvent(event);
				}
				else if (event.eType == DIRECTION_CHANGE) {
					for (int i = 0; i < b->size(); i++) {
						Body* tmp = b->at(i);
						tmp->onEvent(event);
					}
				}
				else {
					std::cout << "STRANGE " << event.argList[0];
				}
				retrieveEvents();
				if (eventQueue.size() != 0) {
					while(flag!=0){}
					flag = 1;
					event = eventQueue.top();
					flag = 0;
				}
				
			}
			
		}
	}

	void retrieveEvents() {
		while (player->getQueueSize() != 0) {
			Event tmp = player->getEvent();
			this->enterQueue(tmp);
		}
		//for (Player* p1 : *players) {
		//	if (p1 != 0) {
		//		while (p1->getQueueSize() != 0) {
		//			Event tmp = p1->getEvent();
		//			
		//			//tmp.timeStamp = tmp.timeStamp + eventTime->getTime();
		//			this->enterQueue(tmp);
		//		}
		//	}
		//}
		/*for (MovPlatform* mp1 : *mpf) {
			while (mp1->getQueueSize() != 0) {
				Event tmp = mp1->getEvent();
				tmp.timeStamp = tmp.timeStamp + eventTime->getTime();
				this->enterQueue(tmp);
			}
		}*/
	}

	

private:
	std::priority_queue<Event, vector<Event>, greater<vector<Event>::value_type>> eventQueue;
	Player* player;
	std::vector<Body*>* b;
	Timeline* eventTime;
	Game* gc;
	ScriptManager* sc;
	int flag;
};