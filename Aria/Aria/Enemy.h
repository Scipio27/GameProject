#pragma once
#include "Perso.h"
#include "Player.h"

class Enemy : public Perso
{
private:
	int probaFuite = 0;

public:

	Enemy();
	Enemy(int h, int d, int pf, string n);
	Enemy(string newName, int init);

	//Getter
	int getProbaFuite();
	
	//Setter

	void changeProbaFuite(int pf);
	//Gameplay
	
	void attack(Perso* a);
	
	
};