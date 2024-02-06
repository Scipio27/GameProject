#pragma once
#include "Enemy.h"
class Boss : public Enemy
{
private:
	bool phase2 = false;
	int maxHealth = 100;
	int regen = 0;
	int charge = 0;
	Perso* cible;
	int floor = 0;
	vector<string> dialogue = { "Bienvenue dans mon antre, vous êtes parvenus à arriver jusqu'ici en vain, pliez sous la puissance du grand ",
								"Vous avez continué... Vous pensez vraiment pouvoir atteindre le sommet ?\nJ'admire votre détermination néanmoins, j'ai eu le temps de me perfectionner, vous allez mourir !!!!!!!!",
								"Encore vous... N'approchez pas vous êtes fou vous ne connaissez même pas le nombre d'étage qu'il y a, mais vous continuez de grimper alors qu'il n'y a aucune récompense à la clé\n",
								"Oui toi derrière ton écran tu as bien compris, pas de récompense rien nada alors fais demi-tour et rentre chez toi au lieu de pénétrer chez les gens pour dérober tous leurs biens\n",
								"...  Pourquoi tu restes planter la sans rien dire ? Ah oui c'est vrai les développeurs était trop feignant pour te donner la possibilité de parler\n",
								"Bon et bien prépare toi à l'ultime défi. Je suis beaucoup plus puissant que la première fois que nous nous sommes vus, seulement l'un d'entre nous sortira vivant de cette joute céleste\n ",
								"Dommage pour toi que ce soit moi qui en sortira vivant malgré tous les efforts que tu as fourni jusqu'ici, c'était une belle perte de temps\n",
								"Surtout pour toi qui joue sur ton pc au lieu de profiter de la vie et d'aller prendre l'air\nQue le combat commence !",

								"Agrougrou Agrougrou Je suis un pas gentil\n",
								
								"Bien joué vous m'avez eu, comme promis il n'y a aucune récompense à part la culpabilité d'avoir tué quelqu'un de sang froid après être entré par effraction chez lui...\nCe fût quand même un plaisir\nJe... Adieu !\n",
								"Non ce n'est pas possible, vous avez gagné vous pouvez à présent rentrer chez vous raconter vos \"exploits\" il n'y a plus rien ensuite, inutile de continuer",
								"Vous avez vaincu le grand Furilus, mais ce n'est pas terminer franchissez le prochain étage si vous l'osez, je vous attendrai même si j'imagine que vous allez faire demi-tour !"};

public:
	Boss(int etage);

	bool getPhase2()const;
	int getMaxHealth() const;
	int getRegen() const;
	int getCharge() const;
	Perso* getCible() ;

	void changePhase2(bool p);
	void changeMaxHealth(int mh);
	void changeRegen(int r);
	void changeCharge(int c);
	void changeCible(Perso* c);

	void attack(Perso* other);
	void bigAttack(Perso* other);
	void regenVie();
	void chargeAttack(Perso& other);

	void genBoss();

	void dialogueBoss();

	friend ostream& operator<<(ostream& os, Boss const& p);
};

