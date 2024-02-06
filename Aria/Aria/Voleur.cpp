#include "Voleur.h"

Voleur::Voleur(string newName, int init)
{
	changeName(newName);
	changeInitiative(init);
	changeClasse("Voleur");
	skillList.push_back("Back Stab");
	skillList.push_back("Steal");
	skillList.push_back("Stealth");
}

void Voleur::backStab(Perso* e)
{

	
	cout << getName() << " effectue un BackStab !\n";
	if (getStealth()) {
		cout << "L'ennemi ne voit rien venir, il perds "<<getDamage()*2<<" PV !\n";
		e->changeHealth(e->getHealth() - getDamage() * 2);
		changeStealth(0);
	}
	else {
		cout << e->getName() <<" perds " << getDamage() << " PV !\n";
		e->changeHealth(e->getHealth() - getDamage()); 
	}
	cout << "Il lui reste " << e->getHealth()<<" PV !\n";
}

void Voleur::steal(Perso* e)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> rnd(0, 100);
	int rng = rnd(gen);
	Resource objetVol;
	
	if (rng <= 75) {

		cout << getName() << " vole un objet, il s'agit de : " << objetVol.getName()<<'\n';
		fillInventory(objetVol.getSelected());
	}
	else {
		cout << getName() << " essaie de voler un objet.. en vain\n";
	}

}

void Voleur::stealth()
{

	if (!getStealth()) {
		cout << getName() << " se cache et prepare son prochain coup\n";
		changeStealth(1);
	}
	else {
		cout << getName() << " est déjà caché !\n";
	}

}

void Voleur::manageInput(string input, Perso* e)
{
	if (input == "Attack") {
		attack(e);
	}
	if (input == "Steal") {
		steal(e);
	}
	else if (input == "Stealth") {
		stealth();
	}
	else if (input == "Back Stab") {
		backStab(e);
	}
}
