#pragma once
class Game;
class Carte;

class CarteFactory {
public:
	static Carte* createCarte(Game* game, int couleur, int symbole);
};

