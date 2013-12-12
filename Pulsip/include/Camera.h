#ifndef CAMERA_H
#define CAMERA_H
#include"GameObject.h"
//Class representing camera that can track GameObject
class Camera
{
public:
	Camera(sf::Window& window, GameObject& tracked);

private:
	sf::Window& window;
	GameObject& tracked;
};

#endif // !CAMERA_H
