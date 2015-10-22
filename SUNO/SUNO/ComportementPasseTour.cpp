#include "ComportementPasseTour.h"
#include "Carte.h"
#include "Game.h"

ComportementPasseTour::ComportementPasseTour(Carte* carte) : ComportementCarte(carte) {
	nom = "PasseTour";
}

ComportementPasseTour::~ComportementPasseTour() {
}

void ComportementPasseTour::jouer() {
	carte_->getGame()->passeTour();
}
