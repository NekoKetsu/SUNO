#pragma once
#include "ComportementCarte.h"

class Game;

const int static 
	JAUNE = -1,
	ROUGE = -2,
	BLEU = -3,
	VERT = -4,
	NOIR = -5;

const int static
	SENS = 10,
	PASS = 11,
	PLUS2 = 12,
	JOKER = 13,
	PLUS4 = 14,
	NONE = 15;

class Carte {
private:
	int couleur_;
	unsigned int symbole_;
	Game * game_;
	ComportementCarte comp_;

public:
	Carte();
	Carte(int couleur, unsigned symbole);
	Carte(Game * game, ComportementCarte comp, int couleur, unsigned int symbole);
	~Carte();
	unsigned int symbole();
	int couleur();
	void jouer();
	void setComportement(ComportementCarte comp);

	Game* game() const {
		return game_;
	}

	void setGame(Game* game) {
		game_ = game;
	}
};
