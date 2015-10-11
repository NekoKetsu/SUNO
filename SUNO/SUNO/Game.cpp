#include "Game.h"
#include <ctime>
#include <algorithm>
#include "Carte.h"


Game::Game() {
	sens_ = 1;
	tour_ = 1;
	talon_ = Paquet();
	pioche_ = Paquet();
	passTour_ = false;
	mains_[4] = {};
	cptPlusDeux_ = 0;
}

void Game::commencer() {
	/*pioche_.push_back(new Carte(this, ROUGE, 0));
	pioche_.push_back(new Carte(this, BLEU, 0));
	pioche_.push_back(new Carte(this, JAUNE, 0));
	pioche_.push_back(new Carte(this, VERT, 0));

	for (int s = 1; s < 12; ++s) {
		for (int j = -1; j > -4; --j) {
			pioche_.push_back(new Carte(this, j, s));
			pioche_.push_back(new Carte(this, j, s));

		}
	}
	for (int i = 1; i < 4; ++i) {
		pioche_.push_back(new Carte(this, NOIR, JOKER));
		pioche_.push_back(new Carte(this, NOIR, PLUS4));
	}*/
	melangerPioche();
	talon_.push_back(pioche_.back());
	pioche_.pop_back();

	for (int j = 0; j < 4; ++j) {
		Paquet main = piocher(7);
		mains_[j] = main;
	}
}

void Game::melangerPioche() {
	srand(time(nullptr));

	std::random_shuffle(pioche_.begin(), pioche_.end());
}


Paquet Game::piocher(unsigned int nb = 1) {
	Paquet cartes = Paquet();

	while (cartes.size() < nb) {
		if (pioche_.empty()) {
			refairePioche();
		}

		cartes.push_back(pioche_.back());
		pioche_.pop_back();
	}

	return cartes;
}

void Game::refairePioche() {
	Carte* c = talon_.back();
	talon_.pop_back();

	pioche_ = talon_;
	talon_ = Paquet();
	talon_.push_back(c);
}


void Game::tourSuivant() {
	int new_tour = sens_ + tour_;
	if (new_tour < TOUR_MIN)
		new_tour = TOUR_MAX;
	else if (new_tour > TOUR_MAX)
		new_tour = TOUR_MIN;

	tour_ = new_tour;
	if(passTour_) {
		passTour_ = false;
		tourSuivant();
	}
}

void Game::changerSens() {
	sens_ *= -1;
}

void Game::passeTour() {
	passTour_ = true;
}

bool Game::estJouable(Carte* carte) {
	bool memeSymbole = talon_.back()->symbole() == carte->symbole();
	bool memeCouleur = talon_.back()->couleur() == carte->couleur();
	return (cptPlusDeux_ > 0 ? memeSymbole :  memeCouleur || memeSymbole);
}

Paquet Game::getCarteJouables(int main) {
	Paquet cartes = Paquet();
	for (Carte* carte : mains_[main]) {
		if(estJouable(carte)) {
			cartes.push_back(carte);
		}
	}

	return cartes;
}

void Game::jouerCarte(Carte* carte) {
	carte->jouer();
	talon_.push_back(carte);
}


Game::~Game() {
}
