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

//Fonction permettant d'initialiser la pioche, le talon et les 4 mains des joueurs
void Game::commencer() {

	//Ajout des 0. On le faite de cette façon pour que les 0 sont uniques par rapport au autres cartes
	pioche_.push_back(CarteFactory::createCarte(this, JAUNE, 0));
	pioche_.push_back(CarteFactory::createCarte(this, ROUGE, 0));
	pioche_.push_back(CarteFactory::createCarte(this, BLEU, 0));
	pioche_.push_back(CarteFactory::createCarte(this, VERT, 0));

	// Ajout des cartes de 1 à 9, changement de sens, passeTour, +2
	for (int s = 1; s < 13; ++s) {
		for (int j = -1; j > -5; --j) {
			pioche_.push_back(CarteFactory::createCarte(this, j, s));
			pioche_.push_back(CarteFactory::createCarte(this, j, s));

		}
	}

	//Permet d'ajouter les jokers (+4 et le changement de la couleur)
	for (int i = 1; i < 5; ++i) {
		pioche_.push_back(CarteFactory::createCarte(this, NOIR, JOKER));
		pioche_.push_back(CarteFactory::createCarte(this, NOIR, PLUS4));
	}

	//Fonction permettant de mélanger la pioche
	melangerPioche();

	//Ajout d'une carte pour le talon
	talon_.push_back(pioche_.back());

	//On retire la dernière carte de la pioche puisqu'elle a été ajouté au talon
	pioche_.pop_back();

	//Création des mains des joueurs
	for (int j = 0; j < 4; ++j) {
		mains_[j] = Paquet();
		tour_ = j+1;

		//Fonction permettant de piocher le nombre de carte passé en paramètre
		piocher(7);
	}

	//On commence au premier tour
	tour_ = TOUR_MIN;

	//Permet de définir lorsque la partie doit se terminer
	finPartie = false;
}

//Permet de mélanger la pioche
void Game::melangerPioche() {
	srand(time(nullptr));
	std::random_shuffle(pioche_.begin(), pioche_.end());
}

//Retourne la main courant du joueur actuel. Passage de tour-1 en paramètre car le tour commence à 1 et la collection de main à 0
Paquet Game::getMainCourante() {
	return mains_[tour_-1];
}

//Permet de "setter" un paquet de carte pour le joueur courant
void Game::setMainCourante(Paquet p) {
	mains_[tour_-1] = p;
}

//Fonction permettant de piocher un nombre de carte. Par défaut égal à 1
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

//Permet de refaire la pioche lorsque le nombre de carte de la pioche est à 0
void Game::refairePioche() {
	Carte* c = talon_.back();
	talon_.pop_back();

	pioche_ = talon_;
	talon_ = Paquet();
	talon_.push_back(c);
}

//Fonction gérant toute les actions pendant un tour. Vérification des cartes jouables, affichage de la main
//affichage du talon, le nombre de carte à piocher et changement de la valeur du tour
void Game::jouerTour() {
	std::cout << " __________tour du joueur "<< tour_ << "______________________________________ " << std::endl;
	int nbPioche = (cptPlusDeux_ > 0 ? cptPlusDeux_ * 2 : (plusQuatre_ ? 4 : 1));
	afficheMain();
	afficheTalon();
	// Si aucune carte jouable
	if (getCarteJouables().empty()) {
		std::cout << " Le joueur "<< tour_ << " pioche un nombre de carte de " << nbPioche << std::endl;
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

	// si un joueur n'a plus de carte dans sa main, alors il gagne la partie
	if (getMainCourante().empty()) {
		finPartie = true;
		std::cout << "Le joueur " <<tour_<< " a gagné"<< std::endl;
	}
	else {
		tourSuivant();
	}
}

//Fonction permettant de gérer le numéro du tour, ainsi que le sens
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

//Fonction étant utilisé lorsqu'un joueur joue le changement de sens
void Game::changerSens() {
	sens_ *= -1;
}

//Fonction utilisé lorsqu'un joueur joue un passe tour ou un +4
void Game::passeTour() {
	passTour_ = true;
}

//Permet de vérifier si une carte est jouable par un joueur
bool Game::estJouable(Carte* carte) {
	bool memeSymbole = talon_.back()->symbole() == carte->symbole();
	bool memeCouleur = talon_.back()->couleur() == carte->couleur();
	bool carteJoker = carte->couleur() == NOIR;
	bool plusQuatre = plusQuatre_;
	return (plusQuatre ? false : ( (cptPlusDeux_ > 0 ? memeSymbole : memeCouleur || memeSymbole || carteJoker)));
}

//Permet au joueur de choisir sa couleur lorsqu'il joue un joker (+4 et carte changement de couleur)
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

//Permet de contituer un paquet temporaire de carte jouable pour le joueur selon sa main
Paquet Game::getCarteJouables() {
	Paquet cartes = Paquet();
	for (Carte* carte : getMainCourante()) {
		if (estJouable(carte)) {
			cartes.push_back(carte);
		}
	}

	return cartes;
}

//Permet de joueur une carte, de l'ajouter sur le talon et de l'enlever de sa main
void Game::jouerCarte(Carte* carte) {
	carte->jouer();
	talon_.push_back(carte);
	Paquet main = getMainCourante();
	main.erase(std::find(main.begin(), main.end(), carte));
	setMainCourante(main);
}

//Permet de savoir si un +4 a été jouer au tour précédent
void Game::setPlusQuatre(bool plusQuatre) {
	plusQuatre_ = plusQuatre;
}

//Permet d'afficher la main du joueur courant
void Game::afficheMain() {
	std::cout << " ______________________________________________ " << std::endl;
	std::cout << "|           Composition de la main :           |" << std::endl;
	for (Carte* carte : getMainCourante()) {
		std::cout << carte->toString() << " |";
	}
	std::cout << " " << std::endl;
}

//Permet d'afficher la dernière carte du talon
void Game::afficheTalon() {
	std::cout << " ______________________________________________ " << std::endl;
	std::cout << "|           Carte visible du talon :           |" << std::endl;
	std::cout << "             " << talon_.back()->toString() << std::endl;
	std::cout << "|______________________________________________|" << std::endl;
}

//Permet au joueur de choisir la carte qu'il veut jouer selon les cartes possibles à jouer de sa main
void Game::choixCarte() {
	Paquet cartesJouables = Paquet();
	unsigned choix;
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
