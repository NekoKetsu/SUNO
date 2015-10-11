#pragma once
#include "ComportementCarte.h"


class ComportementPasseTour :
	public ComportementCarte {
public:
	ComportementPasseTour(Carte* carte);
	~ComportementPasseTour();
	void jouer();
};

