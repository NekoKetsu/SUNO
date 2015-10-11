#pragma once


class Carte;

class ComportementCarte {
protected:
	Carte* carte_;
public:
	ComportementCarte();
	ComportementCarte(Carte * carte);
	~ComportementCarte();
	void jouer();
};

