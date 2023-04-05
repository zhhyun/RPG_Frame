//main running program
#include "Game.h"
#include "GameObject.h"
#include "Component.h"
#include "SpriteComponent.h"
int main(int argc, char* argv[]) {
	GameFrame::Game PROJECT;
	bool success = PROJECT.Initialize();
	if (success) {
		PROJECT.loop();
	}
	
	//PROJECT.shutdown();
	return 0;
}