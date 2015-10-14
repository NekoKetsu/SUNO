#include "ComportementPasseTour.h"
#include "Carte.h"
#include "Game.h"

ComportementPasseTour::ComportementPasseTour(Carte* carte) : ComportementCarte(carte) {
}

ComportementPasseTour::~ComportementPasseTour() {
}

void ComportementPasseTour::jouer() {
	carte_->getGame()->passeTour();
}
