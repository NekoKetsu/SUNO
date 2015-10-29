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
	bool finPartie;

public:
	Game();
	void commencer();
	void melangerPioche();
	Paquet getMainCourante();
	void setMainCourante(Paquet p);
	void piocher(unsigned int nb);
	void refairePioche();
	void jouerTour();
	void tourSuivant();
	void changerSens();
	void passeTour();
	bool estJouable(Carte* carte);
	int choixCouleur();
	Paquet getCarteJouables();
	void afficheTalon();
	void choixCarte();
	void jouerCarte(Carte* carte);
	void setPlusQuatre(bool plusQuatre);
	void afficheMain();
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

	bool isFinPartie() const {
		return finPartie;
	}

	void setFinPartie(bool finPartie) {
		this->finPartie = finPartie;
	}
};
