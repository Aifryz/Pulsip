#ifndef GAME_H
#define GAME_H
//rysuje gui, zajmuje sie managementem resourcow 
#include"Level.h"
class Game
{
public:
	Game();
	~Game();	
	void start();
private:
	Level* m_level;
};
#endif // !GAME_H
