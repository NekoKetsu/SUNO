#include "Game.h"
#include <iostream>
#include "Carte.h"

int main() {
	Game game = Game();
	//std::cout << game.choixCouleur() << std::endl;
	game.commencer();

	while(!game.isFinPartie()){
		game.jouerTour();
	}
	//	std::cout << game.pioche().size() << std::endl;
	//
	//	for (Carte* carte : game.pioche()) {
	//		std::cout << carte->toString() << std::endl;
	//	}
}
