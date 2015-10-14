#pragma once
#include "ComportementJoker.h"

class ComportementPlusQuatre :
		public ComportementJoker {
public:
	ComportementPlusQuatre(Carte* carte);
	ComportementPlusQuatre();
	~ComportementPlusQuatre();
	void jouer();
};
