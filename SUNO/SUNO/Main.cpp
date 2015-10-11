#include "Game.h"
#include <iostream>
#include "Carte.h"

int main() {
	Game game = Game();
	game.commencer();
	std::cout << game.pioche().size() << std::endl;

	for (Carte* carte : game.pioche()) {
		std::cout << carte->afficher() << std::endl;
	}
}