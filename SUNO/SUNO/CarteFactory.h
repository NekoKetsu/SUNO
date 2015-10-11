#pragma once


class Game;
class Carte;

class CarteFactory {
private:
	static Game* game_;
public:
	static Carte* createCarte(Game* game, int couleur, int symbole);
};

