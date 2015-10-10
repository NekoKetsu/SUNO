#include "Game.h"
#include <iostream>

int main() {
	Game game = Game();
	game.commencer();
	std::cout << game.pioche().size() << std::endl;
}