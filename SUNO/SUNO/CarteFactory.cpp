#include "CarteFactory.h"
#include "ComportementPlusDeux.h"
#include "ComportementPasseTour.h"
#include "ComportementChangeSens.h"
#include "Carte.h"


Carte * CarteFactory::createCarte(Game* game, int couleur, int symbole) {
	Carte* carte = new Carte(game, couleur, symbole);
	ComportementCarte comp;
	switch (symbole) {
	case SENS:
		comp = ComportementChangeSens(carte);
		break;
	case PASS : 
		comp = ComportementPasseTour(carte);
		break;
	case PLUS2 :
		comp = ComportementPlusDeux(carte);
		break;
	default :
		comp = ComportementCarte(carte);
		break;
	}
	carte->setComportement(comp);
	return carte;
}
