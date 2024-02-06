#include "Boss.h"

Boss::Boss(int etage)
{
	changeInitiative(40);
	floor = etage;
	changeHealth(100);
	genBoss();
}

bool Boss::getPhase2() const
{
	return phase2;
}

int Boss::getMaxHealth() const
{
	return maxHealth;
}

int Boss::getRegen() const
{
	return regen;
}

int Boss::getCharge() const
{
	return charge;
}

Perso* Boss::getCible()
{
	return cible;
}

void Boss::changePhase2(bool p)
{
	phase2 = p;
	if (phase2) {
		changeDamage(getDamage() * 2);
	}
	else {
		changeDamage(getDamage() / 2);
	}
}

void Boss::changeMaxHealth(int mh)
{
	maxHealth = mh;
}

void Boss::changeRegen(int r)
{
	regen = r;
}

void Boss::changeCharge(int c)
{
	charge = c;
}

void Boss::changeCible(Perso* c)
{
	cible = c;
}

void Boss::attack(Perso* other)
{
	random_device rd;
	default_random_engine gen(rd());
	uniform_int_distribution<int> dist(0, 1);
	if (dist(gen)) {
		int d = getDamage();
		if (getRegen() != 0) {
			regenVie();
		}
		else {
			if (getTourDoT() > 0) {
				changeHealth(getHealth() - 5);
				cout << getName() << " perds 5 PV à cause du Poison ! (reste " << getTourDoT() - 1 << "tours)\n";
				changeTourDoT(getTourDoT() - 1);
			}
			if (getIsStunned()) {
				cout << getName() << " est étourdi et passe donc son tour !\n";
			}
			else {
				cout << dialogue[8] << endl;
				cout << getName() << " attaque de façon furieuse!" << endl;
				other->changeHealth(other->getHealth() - damage);
				cout << other->getName() << " a perdu " << d << " pv, il lui reste " << other->getHealth() << " pv !" << endl << endl;
			}
		}
	}
	else {
		bigAttack(other);
	}	
}

void Boss::bigAttack(Perso* other)
{
	random_device rd;
	default_random_engine gen(rd());
	uniform_int_distribution<int> dist(0, 2);

	if (getRegen() != 0) {
		regenVie();
	}
	else if (getCharge() == 0) {
		int tmp = getDamage();
		changeDamage(tmp * 2.5);
		if (dist(gen) == 2) {
			changeCharge(3);
			changeCible(other);
			chargeAttack(*other);
		}
		else {
			if (getTourDoT() > 0) {
				changeHealth(getHealth() - 5);
				cout << getName() << " perds 5 PV à cause du Poison ! (reste " << getTourDoT() - 1 << "tours)\n";
				changeTourDoT(getTourDoT() - 1);
			}
			if (getIsStunned()) {
				cout << getName() << " est étourdi et passe donc son tour !\n";
			}
			else {
				cout << getName() << " fait une grosse attaque!" << endl;
				other->changeHealth(other->getHealth() - damage);
				cout << other->getName() << " a perdu " << damage << " pv, il lui reste " << other->getHealth() << " pv !" << endl << endl;
			}
			if (dist(gen) == 1 && getHealth() != getMaxHealth()) { 
				changeRegen(3);
			}
		}
		changeDamage(tmp);
	}
	else {
		chargeAttack(*getCible());
	}

}

void Boss::regenVie()
{
	changeRegen(getRegen() - 1);
	if (getRegen() != 0) {
		cout << getName() << " concentre son énergie afin de régénérer sa vie, il aura fini dans " << getRegen() << " tours !!" << endl;
	}
	else {
		if (getHealth() * 2 < getMaxHealth()) {
			changeHealth(getHealth() + getMaxHealth() / 3);
		}
		else {
			changeHealth(getMaxHealth());
		}
		cout << getName() << " a régénéré sa vie\nIl lui reste désormais " << getHealth() << " points de vie" << endl;
	}
}

void Boss::chargeAttack(Perso& c)
{
	int tmp = getDamage();
	changeDamage(tmp * 5);
	changeCharge(getCharge() - 1);
	if (getCharge() != 0) {
		cout << getName() << " prépare quelque chose, il regarde férocement " << c.getName() << ", vous saurez ce qu'il prépare dans " << getCharge() << "tours" << endl;
	}
	else {
		cout << getName() << " passe à l'attaque contre " << c.getName();
		cout << " il subit " << damage << " dégâts" << endl;
		c.changeHealth(c.getHealth() - damage);
		cout << "il lui reste " << c.getHealth() << " point de vie" << endl << endl;
	}
	changeDamage(tmp);
}

void Boss::genBoss()
{
	changeName("Dark Furilus");
	changeDamage(getDamage() * (floor * 0.75));
	changeHealth(getHealth() * (floor * 0.75));
	phase2 = false;
	maxHealth = getHealth();
	
}

void Boss::dialogueBoss() {
	if (getHealth() == getMaxHealth()) {
		if (floor != 3) {
			cout << dialogue[floor - 1] << getName() << endl;
		}
		else {
			for (int i = 0; i < 6; i++) {
				cout << dialogue[i + floor - 1] << endl;
				system("pause");
				system("cls");
			}
		}
		cout << endl;
	}
	else if (getHealth() == 0) {
		cout << dialogue[dialogue.size() - 1 - (floor - 1)] << endl;
	}
	system("pause");
}


ostream& operator<<(ostream& os, Boss const& p)
{
	os << "Je m'appelle " << p.getName() << endl;
	os << "J'ai " << p.getHealth() << " points de vie";
	os << " ainsi que " << p.getDamage() << " points de dégats !" << endl;
	return os;
}
