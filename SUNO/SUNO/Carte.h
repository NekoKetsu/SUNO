#pragma once
#include "ComportementCarte.h"
#include <string>

class Game;

const int
JAUNE = -1,
ROUGE = -2,
BLEU = -3,
VERT = -4,
NOIR = -5;

const int
SENS = 10,
PASS = 11,
PLUS2 = 12,
JOKER = 13,
PLUS4 = 14,
NONE = 15;

class Carte {
private:
	int couleur_;
	int symbole_;
	Game * game_;
	ComportementCarte comp_;

public:
	Carte();
	Carte(int couleur, int symbole);
	Carte(Game * game, int couleur, int symbole);
	Carte(Game* game, ComportementCarte comp, int couleur, int symbole);
	~Carte();
	int symbole();
	int couleur();
	void jouer();
	void setComportement(ComportementCarte comp);

	Game* game() const {
		return game_;
	}

	void setGame(Game* game) {
		game_ = game;
	}

	std::string afficher();
};
