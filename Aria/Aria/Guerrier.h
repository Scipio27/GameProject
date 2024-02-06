#pragma once
#include "Player.h"
class Guerrier : public Player {

private:
	int stamina=100;
public:
	Guerrier(string newName, int init);

	//Getter
	int getStamina() const;

	//Setter
	void changeStamina(int newStamina);


	//Gameplay
	void bigAttack(Perso* e);
	void protect(Perso* a);
	void taunt();

	void manageInput(string input, Perso* e);
};

