#ifndef GAME_EVENT_H
#define GAME_EVENT_H

#include<SFML/Graphics.hpp>
#include<queue>
class GameEvent
{
public:
	struct PointsEvent
	{
		int amount;
	};
	struct PlayerEvent
	{
		unsigned int health;
		bool isdead;
		sf::Vector2i* posptr;
		sf::Vector2i* movedptr;
	};
	struct LevelEvent
	{
		bool isrunning;
	};
	struct ViewEvent
	{
		sf::View* viewptr;
	};

	enum EventType
	{
		PointsValueEvent = 0,
		PlayerMovedEvent,
		PlayerHitEvent,
		LevelFinishedEvent,
		LevelStartedEvent,
		ViewChangedEvent

	};
	EventType type;

	union
	{
		PointsEvent points;
		PlayerEvent player;
		LevelEvent level;
		ViewEvent view;
	};
	
};
typedef std::queue<GameEvent> GameEvents;
#endif // !GAME_EVENT_H
