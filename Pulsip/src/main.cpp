//#include "../include/Player.h"
//#include "../include/ResourceManager.h"
//#include "../include/Game.h"
//#include "../include/SpriteAnimator.h"
//#include "../include/util.h"
#include "../include/Rectangle.h"
#include <iostream>
int main()
{
	Rectangle<int> ir(0,10,20,30);
	Rectangle<int> ir2(0,10,20,30);
	Rectangle<int> ir3(30,20,10,0);
	bool jeden = ir==ir2;
	bool dwa = ir2==ir3;
    return 0;
}
