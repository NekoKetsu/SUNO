#include "ComportementJoker.h"
#include "Carte.h"
#include "Game.h"


ComportementJoker::ComportementJoker() {
}


ComportementJoker::~ComportementJoker() {
}

ComportementJoker::ComportementJoker(Carte* carte) : ComportementCarte(carte) {
}

void ComportementJoker::jouer() {
	carte_->setCouleur(carte_->getGame()->choixCouleurJoueur());
}
