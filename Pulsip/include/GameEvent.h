#ifndef GAME_EVENT_H
#define GAME_EVENT_H

#include<SFML\System.hpp>
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
		sf::Vector2i moved;
		sf::Vector2i position;
	};
	struct LevelEvent
	{
		bool isrunning;
	};

	enum EventType
	{
		PointsEvent,
		PlayerMovedEvent,
		PlayerHitEvent,
		LevelFinishedEvent,
		LevelStartedEvent,

		



	};
	EventType type;
	
};
typedef std::queue<GameEvent> GameEvents;
#endif // !GAME_EVENT_H
