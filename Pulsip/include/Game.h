#ifndef GAME_H
#define GAME_H
//rysuje gui, zajmuje sie managementem resourcow 
#include"Level.h"
#include"GameEvent.h"
class Game
{
public:
	Game();
	~Game();	
	void start();
private:
	std::queue<GameEvent> m_events;
	Level* m_level;
};
#endif // !GAME_H
