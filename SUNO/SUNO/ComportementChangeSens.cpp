#include "ComportementChangeSens.h"
#include "Carte.h"
#include "Game.h"

ComportementChangeSens::ComportementChangeSens() {
}

ComportementChangeSens::ComportementChangeSens(Carte* carte) : ComportementCarte(carte) {}

void ComportementChangeSens::jouer() {
	carte_->game()->changerSens();
}

ComportementChangeSens::~ComportementChangeSens() {
}
