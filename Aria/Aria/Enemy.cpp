#include "Enemy.h"

Enemy::Enemy()
{
	changeHealth(50);
	changeDamage(10);
	changeProbaFuite(0);
	changeClasse("Enemy");
}

Enemy::Enemy(int health, int damage, int initiative, string name)
{
	changeHealth(health);
	changeDamage(damage);
	changeInitiative(initiative);
	changeName(name);
	changeClasse("Enemy");
}

Enemy::Enemy(string newName, int init)
{
	changeName(newName);
	changeInitiative(init);
	changeClasse("Enemy");
}

void Enemy::attack(Perso* a)
{
	if (getIsDead()) {

	}else {
		if (getTourDoT() > 0) {
			changeHealth(getHealth() - 5);
			cout << getName() << " perds 5 PV à cause du Poison ! (reste " << getTourDoT() - 1 << "tours)\n";
			changeTourDoT(getTourDoT() - 1);
		}
		if (getIsStunned()) {
			cout << getName() << " est étourdi et passe donc son tour !\n";
			changeIsStunned(false);
		}
		else {
			cout << "Attention " << getName() << " attaque " << a->getName() << endl;
			a->changeHealth(a->getHealth() - getDamage());
			cout << "Il lui reste " << a->getHealth() << " PV !\n\n";
		}
	}
}

int Enemy::getProbaFuite()
{
	return probaFuite;
}



void Enemy::changeProbaFuite(int pf)
{
	probaFuite = pf;
}
