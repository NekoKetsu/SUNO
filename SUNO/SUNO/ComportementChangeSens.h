#pragma once
#include "ComportementCarte.h"

class ComportementChangeSens :
		public ComportementCarte {
public:
	ComportementChangeSens(Carte* carte);
	void jouer();
	~ComportementChangeSens();
};
