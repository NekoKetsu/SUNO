#include "ComportementChangeSens.h"
#include "Carte.h"
#include "Game.h"

ComportementChangeSens::ComportementChangeSens(Carte* carte) : ComportementCarte(carte) {
	nom = "ChnageSens";
}

void ComportementChangeSens::jouer() {
	carte_->getGame()->changerSens();
}

ComportementChangeSens::~ComportementChangeSens() {
}
