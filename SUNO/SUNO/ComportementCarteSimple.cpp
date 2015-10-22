#include "ComportementCarteSimple.h"

ComportementCarteSimple::ComportementCarteSimple(Carte* carte) : ComportementCarte(carte) {
	nom = "Simple";
}

ComportementCarteSimple::~ComportementCarteSimple() {
}

void ComportementCarteSimple::jouer() {
}
