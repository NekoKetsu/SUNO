#pragma once

class Game;

enum Couleur {
	JAUNE = 1,
	ROUGE = 2,
	BLEU = 3,
	VERT = 4,
	NOIR = 5
};

enum Symbole {
	SENS = 10,
	PASS = 11,
	PLUS2 = 12,
	JOKER = 13,
	PLUS4 = 14,
	NONE = 15
};

class Carte {

private:
	Couleur couleur_;
	Symbole symbole_;
	Game * game_;

public:
	Carte();
	Carte(Game * game);
	Carte(Game * game, Couleur couleur, Symbole symbole);
	~Carte();

};
