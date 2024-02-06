#include "Perso.h"

void Perso::changeIsDead(bool newIsDead)
{
	isDead = newIsDead;
}

void Perso::changeIsStunned(bool newStun)
{
	isStunned = newStun;
}

void Perso::changeIsProtecting(bool newProtect)
{
	isProtecting = newProtect;
}

void Perso::changeIsProtected(bool newIsProtected)
{
	isProtected = newIsProtected;
}

void Perso::changeIsTakingDamage(bool newIsTakingDamage)
{
		isTakingDamage = newIsTakingDamage;
	
}

void Perso::changeName(string newName)
{
	if (newName != "") {
		name = newName;
	}
	else {
		cout << "Nom vide !" << endl;
	}
}

void Perso::changeHealth(int newHealth)
{
	if (newHealth <= 0) {
		isDead = true;
		health = 0;
	}
	else {
		health = newHealth;
	}
}

void Perso::changeDamage(int newDamage)
{
	if (damage < 0) {
		cout << "Damage non valide !" << endl;
		damage = 0;
	}
	else {
		damage = newDamage;
	}
}

void Perso::changeBlocking(bool newBlockValue)
{
	isBlocking = newBlockValue;
}

void Perso::changeInitiative(int newInitiative)
{
	initiative = newInitiative;
}

void Perso::changeIsTaunting(bool newIsTaunting)
{
	isTaunting = newIsTaunting;
}

void Perso::changeStealth(bool newStealth)
{
	isStealth = newStealth;
}


bool Perso::getIsStunned() const
{
	return isStunned;
}

bool Perso::getIsDead() const
{
	return isDead;
}

bool Perso::getIsProtecting() const
{
	return isProtecting;
}

bool Perso::getIsTaunting() const
{
	return isTaunting;
}

bool Perso::getStealth() const
{
	return isStealth;
}
void Perso::changeMana(int newMana)
{
	mana = newMana;
}


string Perso::getName() const
{
	return name;
}

int Perso::getHealth() const
{
	return health;
}

bool Perso::getIsTakingDamage() const
{
	return isTakingDamage;
}

bool Perso::getIsBlocking() const
{
	return isBlocking;
}

bool Perso::getIsProtected() const
{
	return isProtected;
}

int Perso::getDamage() const
{
	return damage;
}

int Perso::getInitiative() const
{
	return initiative;
}

int Perso::getMana() const
{
	return mana;
}

void Perso::block()
{
	changeBlocking(1);
}
int Perso::getTourDoT() const
{
	return tourDoT;
}

string Perso::getClasse() const
{
	return classe;
}


void Perso::changeTourDoT(int newTourDoT)
{
	tourDoT = newTourDoT;
}

void Perso::changeClasse(string newClasse)
{
	classe = newClasse;
}

void Perso::printPerso(vector<Perso*> p) {
	cout << " =====================================================================" << endl;
	cout << "||";
	for (int i = 0; i < p.size(); i++) {
		cout << "  Nom : " << p[i]->getName();
		for (int j = 0; j < 13 - p[i]->getName().size(); j++) {
			cout << " ";
		}
		cout << "||";
	}
	cout << endl;
	cout << "||";
	for (int i = 0; i < p.size(); i++) {
		cout << "  PV : " << p[i]->getHealth();
		for (int j = 0; j < 14 - to_string(p[i]->getHealth()).size(); j++) {
			cout << " ";
		}
		cout << "||";
	}
	cout << endl;
	cout << "||";
	for (int i = 0; i < p.size(); i++) {
		cout << "  Damage : " << p[i]->getDamage();
		for (int j = 0; j < 10 - to_string(p[i]->getDamage()).size(); j++) {
			cout << " ";
		}
		cout << "||";
	}
	cout << endl;
	cout << "||";
	for (int i = 0; i < p.size(); i++) {
		cout << "  Classe : " << p[i]->getClasse();
		for (int j = 0; j < 10 - p[i]->getClasse().size(); j++) {
			cout << " ";
		}
		cout << "||";
	}
	cout << endl;
	cout << " =====================================================================" << endl;
}


ostream& operator<<(ostream& os, vector<Perso*> p)
{
	return os;
}
