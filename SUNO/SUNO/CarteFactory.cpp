#include "CarteFactory.h"
#include "ComportementPlusDeux.h"
#include "ComportementPasseTour.h"
#include "Carte.h"

Carte * CarteFactory::createCarte(Game* game, int couleur, int symbole) {
	Carte* carte = new Carte(game, couleur, symbole);
	ComportementCarte comp;
	switch (symbole) {
	case SENS:
		comp = ComportementPasseTour(carte);
		break;
	case PASS : 
		comp = ComportementPasseTour(carte);
		break;
	case PLUS2 :
		comp = ComportementPlusDeux(carte);
		break;
		
	}
	carte->setComportement(comp);
	return carte;
}
