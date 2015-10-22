#pragma once
#include <string>
class Carte;

class ComportementCarte {
protected:
	Carte* carte_;
	std::string nom;
public:
	ComportementCarte(Carte* carte);
	virtual ~ComportementCarte() = 0;
	virtual void jouer() = 0;
};
