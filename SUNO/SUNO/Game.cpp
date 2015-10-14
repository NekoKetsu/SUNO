#include "Game.h"
#include <ctime>
#include <algorithm>
#include <iostream>
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
	int nbPioche = (cptPlusDeux_ > 0 ? cptPlusDeux_ * 2 : (plusQuatre_ ? 4 : 1));
	Paquet cartesJouables = Paquet();
	Paquet mainCourante = mains_[tour_];

	// Récupère les cartes jouables
	for (Carte* c : mainCourante) {
		if (estJouable(c)) {
			cartesJouables.push_back(c);
		}

	}


	// Si aucune carte jouable
	if (cartesJouables.empty()) {
		// Pioches les cartes
		Paquet pioches = piocher(nbPioche);
		// Met dans la main
		mainCourante.insert(mainCourante.end(), pioches.begin(), pioches.end());
	}
	// TODO 
	//	si nbPioche == 1 checker si la nouvelle carte est jouable
	//		Demander quelles cartes joué parmi les jouables 
	//		Mettre dans carteAJouer
	Carte* carteAJouer;
	jouerCarte(carteAJouer);
	mainCourante.erase(std::find(mainCourante.begin(), mainCourante.end(), carteAJouer));
	if (mainCourante.empty()) {
		// SITUATION DE VICTOIRE du joueur n°tour_
	}
	else {
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
	if (passTour_) {
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
	return (cptPlusDeux_ > 0 ? memeSymbole : memeCouleur || memeSymbole || carteJoker);
}

int Game::choixCouleurJoueur() {
	char choix = ' ';
	std::cout << " _____________________________________________ " << std::endl;
	std::cout << "|           Choisissez la couleur :           |" << std::endl;
	std::cout << "| Jaune : 1 | Rouge : 2 | Bleu : 3 | Vert : 4 |" << std::endl;
	std::cout << "|_____________________________________________|" << std::endl;

	do {
		std::cout << "|        Entrez une valeur entre 1 et 4       |" << std::endl;
		std::cout << "                        ";
		std::cin >> choix;
		if (choix < '1' || choix > '4') {
			std::cout << "|              Entree incorrecte              |" << std::endl;
			std::cout << "|_____________________________________________|" << std::endl;
		}
		else
			break;
	} while (true);
	std::cout << "|_____________________________________________|" << std::endl;
	int couleur = (choix - '0') * -1;

	return couleur;
}

Paquet Game::getCarteJouables(int main) {
	Paquet cartes = Paquet();
	for (Carte* carte : mains_[main]) {
		if (estJouable(carte)) {
			cartes.push_back(carte);
		}
	}

	return cartes;
}

void Game::jouerCarte(Carte* carte) {
	carte->jouer();
	talon_.push_back(carte);
}

void Game::setPlusQuatre(bool plusQuatre) {
	plusQuatre_ = plusQuatre;
}

Game::~Game() {
}
