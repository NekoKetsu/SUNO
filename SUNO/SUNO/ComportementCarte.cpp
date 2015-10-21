#include "ComportementCarte.h"


ComportementCarte::ComportementCarte() {
	carte_ = nullptr;
}

ComportementCarte::ComportementCarte(Carte* carte) : carte_(carte) {
}

ComportementCarte::~ComportementCarte() {
}

void ComportementCarte::jouer() {
}
