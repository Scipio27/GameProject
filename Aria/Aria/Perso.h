#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

class Perso
{
protected:
	string name = "Bob";
	int health = 100;
	int damage = 10;
	int mana = 0;
	string classe;
	int initiative = 0;
	bool isTakingDamage = 0;
	bool isTaunting = 0;
	bool isStealth = 0;
	bool isBlocking = 0;
	bool isProtected = 0;
	bool isProtecting = 0;
	int tourDoT = 0;
	bool isStunned = 0;
	bool isDead = false;
	

public:

	//Getter
	bool getIsStunned() const;
	bool getIsDead() const;
	bool getIsProtecting() const;
	bool getIsTaunting() const;
	bool getStealth() const;
	bool getIsTakingDamage() const;
	bool getIsBlocking() const;
	bool getIsProtected() const;
	string getName() const;
	int getHealth() const;
	int getDamage() const;
	int getInitiative() const;
	int getMana()const;
	int getTourDoT() const;
	string getClasse() const;

	//Setter
	void changeIsDead(bool newIsDead);
	void changeIsStunned(bool newStun);
	void changeIsProtecting(bool newProtect);
	void changeIsProtected(bool newIsProtected);
	void changeIsTakingDamage(bool newIsTakingDamage);
	void changeName(string newName);
	void changeHealth(int newHealth);
	void changeDamage(int newDamage);
	void changeBlocking(bool newBlockValue);
	void changeInitiative(int newInitiative);
	void changeIsTaunting(bool newIsTaunting);
	void changeStealth(bool newStealth);
	void changeMana(int newMana);
	void changeTourDoT(int newTourDoT);
	void changeClasse(string newClasse);


	//Gameplay
	void printPerso(vector<Perso*> p);
	virtual void attack(Perso* e)=0;
	
	void block();

	friend ostream& operator<<(ostream& os, Perso const& p);
};

