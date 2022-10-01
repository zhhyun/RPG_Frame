//main running program
#include "Game.h"
int main(int argc, char* argv[]) {
	GameFrame::Game PROJECT;
	bool success = PROJECT.Initialize();
	if (success) {
		PROJECT.loop();
	}
	
	PROJECT.shutdown();
	return 0;
}