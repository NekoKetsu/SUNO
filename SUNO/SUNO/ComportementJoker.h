#pragma once
#include "ComportementCarte.h"

class ComportementJoker :
		public ComportementCarte {
public:
	ComportementJoker();
	~ComportementJoker();
	ComportementJoker(Carte* carte);
	void jouer();
};
