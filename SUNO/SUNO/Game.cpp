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
		mains_[j] = Paquet();
		tour_ = j;
		piocher(7);
	}
	tour_ = TOUR_MIN;
}

void Game::melangerPioche() {
	srand(time(nullptr));
	std::random_shuffle(pioche_.begin(), pioche_.end());
}

Paquet Game::getMainCourante() {
	return mains_[tour_];
}

void Game::setMainCourante(Paquet p) {
	mains_[tour_] = p;
}

void Game::piocher(unsigned int nb = 1) {
	Paquet cartes = Paquet();

	while (cartes.size() < nb) {
		if (pioche_.empty()) {
			refairePioche();
		}

		cartes.push_back(pioche_.back());
		pioche_.pop_back();
	}
	Paquet main = getMainCourante();
	main.insert(main.end(), cartes.begin(), cartes.end());
	setMainCourante(main);
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

	// Si aucune carte jouable
	if (getCarteJouables().empty()) {
		// Pioches les cartes
		piocher(nbPioche);
		cptPlusDeux_ = 0;
		plusQuatre_ = false;

		if (nbPioche == 1 && !getCarteJouables().empty()) {
			choixCarte();
		}
	}else {
		choixCarte();
	}



	if (getMainCourante().empty()) {
		// SITUATION DE VICTOIRE du joueur n�tour_
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
	bool plusQuatre = plusQuatre_;
	return (plusQuatre ? false : ( (cptPlusDeux_ > 0 ? memeSymbole : memeCouleur || memeSymbole || carteJoker)));
}

int Game::choixCouleur() {
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
	}
	while (true);
	std::cout << "|_____________________________________________|" << std::endl;
	int couleur = (choix - '0') * -1;

	return couleur;
}

Paquet Game::getCarteJouables() {
	Paquet cartes = Paquet();
	for (Carte* carte : getMainCourante()) {
		if (estJouable(carte)) {
			cartes.push_back(carte);
		}
	}

	return cartes;
}

void Game::jouerCarte(Carte* carte) {
	carte->jouer();
	talon_.push_back(carte);
	Paquet main = getMainCourante();
	main.erase(std::find(main.begin(), main.end(), carte));
	setMainCourante(main);
}

void Game::setPlusQuatre(bool plusQuatre) {
	plusQuatre_ = plusQuatre;
}

void Game::afficheMain() {
	std::cout << " ______________________________________________ " << std::endl;
	std::cout << "|           Composition de la main :           |" << std::endl;
	for (Carte* carte : getMainCourante()) {
		std::cout << carte->toString() << " |";
	}
	std::cout << " " << std::endl;
}

void Game::afficheTalon() {
	std::cout << " ______________________________________________ " << std::endl;
	std::cout << "|           Carte visible du talon :           |" << std::endl;
	std::cout << "             " << talon_.back()->toString() << std::endl;
}

void Game::choixCarte() {
	Paquet cartesJouables = Paquet();
	unsigned choix;
	std::cout << " __________tour du joueur "<< tour_ << "______________________________________ " << std::endl;
	std::cout << " _________________________________________________________________ " << std::endl;
	std::cout << "|           Choisissez la carte que vous voulez jouer :           |" << std::endl;
	for (Carte* carte : getCarteJouables()) {
		std::cout << carte->toString() << " |";
		cartesJouables.push_back(carte);
	}
	if (cartesJouables.size() != 0) {
		do {
			std::cout << " Saisissez la position de la carte dans la liste (de 1 à " << cartesJouables.size() << ")" << std::endl;
			std::cin >> choix;
			if (choix < 1 || choix > cartesJouables.size()) {
				std::cout << "|              Entree incorrecte              |" << std::endl;
				std::cout << "|_____________________________________________|" << std::endl;
			}
			else {
				jouerCarte(cartesJouables.at(choix - 1));
				break;
			}
		}
		while (true);
	}
}

Game::~Game() {
}
