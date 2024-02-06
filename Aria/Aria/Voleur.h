#pragma once
#include "Player.h"
class Voleur : public Player 
{
public:

	Voleur(string newName, int init);
	//Getter
	
	//Setter

	//Gameplay
	void backStab(Perso* e);
	void steal(Perso* e);
	void stealth();

	void manageInput(string input, Perso* e);
};

