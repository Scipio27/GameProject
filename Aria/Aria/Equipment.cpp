#include "Equipment.h"

Equipment::Equipment()
{
	if (rand() % 2) {
		changeEquipement(chooseEquipement(), 1);
	}
	else {
		changeSelected(chooseArme(), 1);
	}
	
}

CItem* Equipment::chooseArme() const
{
	random_device rd;
	default_random_engine gen(rd());
	uniform_int_distribution<int> dist(0, arme.size()-1);
	return arme[dist(gen)];
}

CItem* Equipment::getSelected() const
{
	return selected;
}

vector<CItem*> Equipment::getArme() const
{
	return arme;
}

vector<CItem*> Equipment::getEquipement() const
{
	return equipement;
}

CItem* Equipment::chooseEquipement() 
{
	random_device rd;
	default_random_engine gen(rd());
	uniform_int_distribution<int> equip(0, equipement.size()-1);
	return equipement[equip(gen)];
}

void Equipment::changeArme(CItem* a)
{
	for (int i = 0; i < arme.size(); i++) {
		if (arme[i]->getName() == a->getName()) {
			arme[i] = a;
			break;
		}
	}
}

void Equipment::changeSelected(CItem* s, int difficulty)
{
	selected = s;
	changeName(s->getName());
	changeBonusDamage(s->getBonusDamage() + difficulty * 5);
	if (s->getBonusMana() != 0) {
		changeBonusMana(s->getBonusMana() + difficulty * 5);
	}
	else {
		changeBonusMana(0);
	}
}

void Equipment::changeEquipement(CItem* e, int difficulty)
{
	vector<string> spe = { " force", " vie", " mana" };
	if (e->getName() == "amulette" || e->getName() == "anneau") {
		random_device rd;
		default_random_engine gen(rd());
		uniform_int_distribution<int> type(0, spe.size()-1);
		int r = type(gen);
		switch (r) {
		case 0:
			e->changeName(e->getName() += spe[r]);
			e->changeBonusDamage(15);
			e->changeBonusHealth(5);
			e->changeBonusMana(5);
			break;
		case 1:
			e->changeName(e->getName() += spe[r]);
			e->changeBonusDamage(5);
			e->changeBonusHealth(20);
			e->changeBonusMana(5);
			break;
		case 2:
			e->changeName(e->getName() += spe[r]);
			e->changeBonusDamage(5);
			e->changeBonusHealth(5);
			e->changeBonusMana(20);
			break;
		default:
			break;
		}
	}

	changeName(e->getName());		
	if (e->getBonusMana() != 0) {
		changeBonusMana(e->getBonusMana() + difficulty * 5);		
	}
	if(e->getBonusHealth() != 0){
		changeBonusHealth(e->getBonusHealth() + difficulty * 5);
	}
	if (e->getBonusDamage() != 0){
		changeBonusDamage(e->getBonusDamage() + difficulty * 5);
	}

	selected = e;
}
