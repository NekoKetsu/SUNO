#pragma once
#include <vector>


class Carte;
typedef std::vector<Carte*> Paquet;

class Game {
private:
	bool passTour_;
	int sens_;
	int tour_;
	int cptPlusDeux_;
	const int TOUR_MIN = 1;
	const int TOUR_MAX = 4;
	Paquet talon_;
	Paquet pioche_;
	Paquet mains_[4];

public:
	Game();
	void commencer();
	void melangerPioche();
	Paquet piocher(unsigned int nb);
	void refairePioche();
	void tourSuivant();
	void changerSens();
	void passeTour();
	bool estJouable(Carte* carte);
	Paquet getCarteJouables(int main);
	void jouerCarte(Carte* carte);
	~Game();

	Paquet pioche() {
		return pioche_;
	}

	void set_pioche(Paquet pioche) {
		pioche_ = pioche;
	}

	int getCptPlusDeux() const {
		return cptPlusDeux_;
	}

	void incrCptPlusDeux() {
		++cptPlusDeux_;
	}

};
