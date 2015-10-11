#include "Carte.h"


Carte::Carte() {
	game_ = nullptr;
	couleur_ = NOIR;
	symbole_ = NONE;
	comp_ = nullptr;
}

Carte::Carte(int couleur, unsigned int symbole) {
	game_ = nullptr;
	couleur_ = couleur;
	symbole_ = symbole;
	comp_ = nullptr;
}


Carte::Carte(Game* game, ComportementCarte comp, int couleur, unsigned int symbole) {
	game_ = game;
	couleur_ = couleur;
	symbole_ = symbole;
	comp_ = comp;
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
	comp_.jouer();
}

void Carte::setComportement(ComportementCarte comp) {
	comp_ = comp;
}

