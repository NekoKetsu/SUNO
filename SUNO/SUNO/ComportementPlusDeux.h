#pragma once
#include "ComportementCarte.h"

class ComportementPlusDeux : public ComportementCarte {
public:
	ComportementPlusDeux();
	ComportementPlusDeux(Carte* carte);
	void jouer();
	~ComportementPlusDeux();
};
