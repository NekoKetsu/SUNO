#pragma once
#include "ComportementCarte.h"
class ComportementCarteSimple :
	public ComportementCarte {
public:

	ComportementCarteSimple(Carte * carte);
	~ComportementCarteSimple();
	void jouer();
};

