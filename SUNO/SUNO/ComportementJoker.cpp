#include "ComportementJoker.h"
#include "Carte.h"
#include "Game.h"


ComportementJoker::~ComportementJoker() {
}

ComportementJoker::ComportementJoker(Carte* carte) : ComportementCarte(carte) {
	nom = "Joker";
}

void ComportementJoker::jouer() {
	carte_->setCouleur(carte_->getGame()->choixCouleur());
}
