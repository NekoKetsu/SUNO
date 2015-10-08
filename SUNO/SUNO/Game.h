#pragma once
#include <stack>
#include <vector>

class Carte;
typedef std::vector<Carte*> Paquet;

class Game {
private:
	int sens_;
	int tour_;
	const int TOUR_MIN = 1;
	const int TOUR_MAX = 4;
	Paquet talon_;
	Paquet pioche_;
	Paquet mains_[4];

public:
	Game();
	void commencer();
	void melangerPioche();
	Carte * piocher();
	Paquet piocher(int nb);
	void refairePioche();
	void tourSuivant();
	void changerSens();
	bool estJouable(Carte carte);

	~Game();

};
