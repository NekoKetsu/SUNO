#pragma once
#include <vector>


class Carte;
typedef std::vector<Carte*> Paquet;
const int TOUR_MIN = 1;
const int TOUR_MAX = 4;

class Game {
private:
	bool passTour_;
	int sens_;
	int tour_;
	int cptPlusDeux_;
	bool plusQuatre_;
	Paquet talon_;
	Paquet pioche_;
	Paquet mains_[4];

public:
	Game();
	void commencer();
	void melangerPioche();
	Paquet piocher(unsigned int nb);
	void refairePioche();
	void jouerTour();
	void tourSuivant();
	void changerSens();
	void passeTour();
	bool estJouable(Carte* carte);
	int choixCouleurJoueur();
	void choixCarteJoueur(int main);
	void afficheMain(int main);
	void afficheTalon();
	Paquet getCarteJouables(int main);
	void jouerCarte(Carte* carte,int main);
	void setPlusQuatre(bool plusQuatre);
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
