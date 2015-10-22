#include "ComportementPlusQuatre.h"
#include "Carte.h"
#include "Game.h"

ComportementPlusQuatre::ComportementPlusQuatre(Carte* carte) : ComportementJoker(carte) {
	nom = "PlusQuatre";
}



ComportementPlusQuatre::~ComportementPlusQuatre() {
}

void ComportementPlusQuatre::jouer() {
	ComportementJoker::jouer();
	carte_->getGame()->setPlusQuatre(true);
}
