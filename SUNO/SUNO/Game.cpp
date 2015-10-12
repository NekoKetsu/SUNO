#include "Game.h"
#include <ctime>
#include <algorithm>
#include "Carte.h"
#include "CarteFactory.h"


Game::Game() {
	sens_ = 1;
	tour_ = 1;
	talon_ = Paquet();
	pioche_ = Paquet();
	passTour_ = false;
	cptPlusDeux_ = 0;
	plusQuatre_ = false;
}

void Game::commencer() {

	pioche_.push_back(CarteFactory::createCarte(this, JAUNE, 0));
	pioche_.push_back(CarteFactory::createCarte(this, ROUGE, 0));
	pioche_.push_back(CarteFactory::createCarte(this, BLEU, 0));
	pioche_.push_back(CarteFactory::createCarte(this, VERT, 0));

	for (int s = 1; s < 13; ++s) {
		for (int j = -1; j > -5; --j) {
			pioche_.push_back(CarteFactory::createCarte(this, j, s));
			pioche_.push_back(CarteFactory::createCarte(this, j, s));

		}
	}
	for (int i = 1; i < 5; ++i) {
		pioche_.push_back(CarteFactory::createCarte(this, NOIR, JOKER));
		pioche_.push_back(CarteFactory::createCarte(this, NOIR, PLUS4));
	}
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

void Game::jouerTour() {
	int nbPioche = (cptPlusDeux_ > 0 ? cptPlusDeux_*2 : (plusQuatre_ ?  4 : 1));
	Paquet cartesJouables = Paquet();
	Paquet mainCourante = mains_[tour_];
	
	for (Carte* c : mainCourante) {
		if(estJouable(c)) {
			cartesJouables.push_back(c);
		}
	}

	if (cartesJouables.empty()) {
		Paquet pioches = piocher(nbPioche);
		
		mainCourante.insert(mainCourante.end(), pioches.begin(), pioches.end());
	}
	// TODO 
	//	si nbPioche == 1 checker si la nouvelle carte est jouable
	//		Demander quelles cartes joué parmi les jouables 
	//		Mettre dans carteAJouer
	Carte carteAJouee;
	carteAJouee.jouer();
	// Voir comment géré le choix du joker et di plus 4 (ta vu tmtc)
	mainCourante.erase(std::remove(mainCourante.begin(), mainCourante.end(), carteAJouee), mainCourante.end());
	if(mainCourante.empty()) {
		// SITUATION DE VICTOIRE du joueur n°tour_
	}else {
		tourSuivant();
	}
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
	bool carteJoker = carte->couleur() == NOIR;
	return (cptPlusDeux_ > 0 ? memeSymbole :  memeCouleur || memeSymbole || carteJoker);
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
