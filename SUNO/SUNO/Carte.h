#pragma once
#include "Game.h"

class Game;

int static 
	JAUNE = -1,
	ROUGE = -2,
	BLEU = -3,
	VERT = -4,
	NOIR = -5;

int static
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

public:
	Carte();
	Carte(Game * game);
	Carte(Game * game, int couleur, unsigned int symbole);
	~Carte();
	unsigned int symbole();
	int couleur();
	void jouer();
};
