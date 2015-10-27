#include "CarteFactory.h"
#include "ComportementPlusDeux.h"
#include "ComportementPasseTour.h"
#include "ComportementChangeSens.h"
#include "Carte.h"
#include "ComportementPlusQuatre.h"
#include <iostream>
#include "ComportementCarteSimple.h"


Carte* CarteFactory::createCarte(Game* game, int couleur, int symbole) {
	Carte* carte = new Carte(game, couleur, symbole);
	ComportementCarte* comp;
	switch (symbole) {
		case SENS:
			comp = new ComportementChangeSens(carte);
			break;
		case PASS:
			comp = new ComportementPasseTour(carte);
			break;
		case PLUS2:
			comp = new ComportementPlusDeux(carte);
			break;
		case JOKER:
			comp = new ComportementJoker(carte);
			break;
		case PLUS4:
			comp = new ComportementPlusQuatre(carte);
			break;

		default:
			comp = new ComportementCarteSimple(carte);

	}
	carte->setComportement(comp);
	return carte;
}
