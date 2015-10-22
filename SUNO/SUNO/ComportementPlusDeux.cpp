#include "ComportementPlusDeux.h"
#include "Carte.h"
#include "Game.h"

ComportementPlusDeux::ComportementPlusDeux(Carte* carte) : ComportementCarte(carte) {
	nom = "PlusDeux";
}

void ComportementPlusDeux::jouer() {
	carte_->getGame()->incrCptPlusDeux();
}

ComportementPlusDeux::~ComportementPlusDeux() {
}
