#include "Game.h"
#include "Carte.h"
#include <ctime>
#include <algorithm>


Game::Game() {
	sens_ = 1;
	tour_ = 1;
	talon_ = Paquet();
	pioche_ = Paquet();
}

void Game::commencer() {
	/*
	TODO :
	Init pioche (Crée toutes les cartes dans la pioche)

	*/
	melangerPioche();
	talon_.push_back(pioche_.back());
	pioche_.pop_back();

	for (int i = 0; i < 4; ++i) {
		Paquet main = piocher(7);
		mains_[i] = main;
	}
}

void Game::melangerPioche() {
	srand(time(0));

	std::random_shuffle(pioche_.begin(), pioche_.end());
}


Paquet Game::piocher(int nb = 1) {
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
}

void Game::changerSens() {
	sens_ *= -1;
}

bool Game::estJouable(Carte carte) {
	//TODO : 
	return false;
}


Game::~Game() {
}
