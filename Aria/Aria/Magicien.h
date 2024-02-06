#pragma once
#include "Player.h"
#include "CItem.h"

enum cardNumber {
	nullcard, As, Deux, Trois, Quatre, Cinq, Six, Sept, Huit, Neuf, Dix, Valet, Dame, Roi
};
enum cardColor {
	nullcolor,Pique,Carreaux,Trefle,Coeur
};

class Magicien : public Player
{
private:
	int mana = 100;
	int nbCard = 52;

public:
	Magicien(string newName, int init);

	//Getter
	int getMana();
	int getNbCard();

	//Setter
	void changeMana(int newMana);
	void changeNbCard(int newNbCard);
	int cardToInt(cardNumber card);
	string cardToString(cardNumber card);
	string colorToString(cardColor card);
	//Gameplay
	void fireball(Perso* e);
	void drawCard(Perso* e);
	void attackCoeur(int valeur,  Perso* a);
	void attackPique(int valeur, Perso* e);
	void attackTrefle(int valeur,  Perso* e);
	void attackCarreau(int valeur, Perso* e);
	void heal(Perso* a);


	void manageInput(string input, Perso* e);
};

