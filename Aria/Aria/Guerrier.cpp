#include "Guerrier.h"

Guerrier::Guerrier(string newName, int init)
{
	changeName(newName);
	changeInitiative(init);
	changeClasse("Guerrier");
	skillList.push_back("Big Attack");
	skillList.push_back("Protect");
	skillList.push_back("Taunt");
}

int Guerrier::getStamina() const
{
	return stamina;
}


void Guerrier::changeStamina(int newStamina)
{
	if ((stamina - newStamina) < 0) {
		stamina = 0;
	}
	else {
		stamina -= newStamina;
	}
}

void Guerrier::bigAttack(Perso* e)
{
	if (getStamina() >= 10) {
		cout << getName() << " lance une grosse attaque !" << endl;
		e->changeHealth(e->getHealth() - (getDamage() * 3));
		cout << e->getName() << " a perdu " << getDamage() *3 << " pv, il lui reste " << e->getHealth() << " pv !" << endl;
		changeStamina(10);
	}
	else {
		cout << getName()<<" n'a pas assez d'endurance !\n";
	}
}

void Guerrier::protect(Perso* a)
{
	if (getStamina() >= 15) {
		cout << getName() << " protège " << a->getName() << " !\n";
		a->changeIsProtected(true);
		changeIsProtecting(true);
		changeStamina(15);
	}
	else {
		cout << getName() << " n'a pas assez d'endurance !\n";
	}
}

void Guerrier::taunt()
{
	if (getStamina() >= 20) {
		changeIsTaunting(true);
		changeStamina(20);
	}
	else {
		cout << getName() << " n'a pas assez d'endurance !\n";
	}
}

void Guerrier::manageInput(string input, Perso* e)
{
	if (input == "Attack") {
		attack(e);
	}
	if (input == "Big Attack") {
		bigAttack(e);
	}
	else if (input == "Protect") {
		protect(e);
	}
	else if (input == "Taunt") {
		taunt();
	}
}
