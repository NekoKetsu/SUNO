#include "ComportementPlusQuatre.h"
#include "Carte.h"
#include "Game.h"

ComportementPlusQuatre::ComportementPlusQuatre(Carte* carte) : ComportementJoker(carte) {
}


ComportementPlusQuatre::ComportementPlusQuatre() {
}


ComportementPlusQuatre::~ComportementPlusQuatre() {
}

void ComportementPlusQuatre::jouer() {
	carte_->getGame()->setPlusQuatre(true);
	ComportementJoker::jouer();
}
