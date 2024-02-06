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
	vector<string> dialogue = { "Bienvenue dans mon antre, vous �tes parvenus � arriver jusqu'ici en vain, pliez sous la puissance du grand ",
								"Vous avez continu�... Vous pensez vraiment pouvoir atteindre le sommet ?\nJ'admire votre d�termination n�anmoins, j'ai eu le temps de me perfectionner, vous allez mourir !!!!!!!!",
								"Encore vous... N'approchez pas vous �tes fou vous ne connaissez m�me pas le nombre d'�tage qu'il y a, mais vous continuez de grimper alors qu'il n'y a aucune r�compense � la cl�\n",
								"Oui toi derri�re ton �cran tu as bien compris, pas de r�compense rien nada alors fais demi-tour et rentre chez toi au lieu de p�n�trer chez les gens pour d�rober tous leurs biens\n",
								"...  Pourquoi tu restes planter la sans rien dire ? Ah oui c'est vrai les d�veloppeurs �tait trop feignant pour te donner la possibilit� de parler\n",
								"Bon et bien pr�pare toi � l'ultime d�fi. Je suis beaucoup plus puissant que la premi�re fois que nous nous sommes vus, seulement l'un d'entre nous sortira vivant de cette joute c�leste\n ",
								"Dommage pour toi que ce soit moi qui en sortira vivant malgr� tous les efforts que tu as fourni jusqu'ici, c'�tait une belle perte de temps\n",
								"Surtout pour toi qui joue sur ton pc au lieu de profiter de la vie et d'aller prendre l'air\nQue le combat commence !",

								"Agrougrou Agrougrou Je suis un pas gentil\n",
								
								"Bien jou� vous m'avez eu, comme promis il n'y a aucune r�compense � part la culpabilit� d'avoir tu� quelqu'un de sang froid apr�s �tre entr� par effraction chez lui...\nCe f�t quand m�me un plaisir\nJe... Adieu !\n",
								"Non ce n'est pas possible, vous avez gagn� vous pouvez � pr�sent rentrer chez vous raconter vos \"exploits\" il n'y a plus rien ensuite, inutile de continuer",
								"Vous avez vaincu le grand Furilus, mais ce n'est pas terminer franchissez le prochain �tage si vous l'osez, je vous attendrai m�me si j'imagine que vous allez faire demi-tour !"};

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

