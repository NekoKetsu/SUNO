#include "ComportementPlusDeux.h"
#include "Carte.h"
#include "Game.h"

ComportementPlusDeux::ComportementPlusDeux() {
}

ComportementPlusDeux::ComportementPlusDeux(Carte* carte) : ComportementCarte(carte) {}

void ComportementPlusDeux::jouer() {
	carte_->game()->incrCptPlusDeux();
}

ComportementPlusDeux::~ComportementPlusDeux() {
}
