#ifndef LEVEL_H
#define LEVEL_H
//rysuje wszystkie obiekty, odswieza je

#include "GameEvent.h"
class Level
{
public:
	Level();
	~Level();
	Level(GameEvents* eventqueue);
	void tick(sf::Time dt);

private:
	GameEvents m_events;
	GameEvents* m_gameevents;
	
};
#endif

