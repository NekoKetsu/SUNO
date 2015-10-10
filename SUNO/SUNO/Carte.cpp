#include "Carte.h"
#include "Game.h"

Carte::Carte() {
	game_ = new Game();
	couleur_ = NOIR;
	symbole_ = NONE;
}

Carte::Carte(Game* game) {
	game_ = game;
	couleur_ = NOIR;
	symbole_ = NONE;
}

Carte::Carte(Game* game, int couleur, unsigned int symbole) {
	game_ = game;
	couleur_ = couleur;
	symbole_ = symbole;
}


Carte::~Carte() {
}

unsigned int Carte::symbole() {
	return symbole_;
}

int Carte::couleur() {
	return couleur_;
}

void Carte::jouer() {
}