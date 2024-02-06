#include "Magicien.h"

#pragma region Getter
int Magicien::getMana()
{
	return mana;
}

int Magicien::getNbCard()
{
	return nbCard;
}
#pragma endregion Getter

Magicien::Magicien(string newName, int init)
{
	changeName(newName);
	changeInitiative(init);
	changeClasse("Magicien");
	skillList.push_back("Heal");
	skillList.push_back("Draw Card");
	skillList.push_back("Fire Ball");
}

#pragma region Setter
void Magicien::changeMana(int newMana)
{
	mana = newMana;
}
void Magicien::changeNbCard(int newNbCard)
{
	nbCard = newNbCard;
}
string Magicien::cardToString(cardNumber card) {
	switch (card) {
	case nullcard:
		return "nullcard";
		break;
	case As:
		return "As";
		break;
	case Deux:
		return "Deux";
		break;
	case Trois:
		return "Trois";
		break;
	case Quatre:
		return "Quatre";
		break;
	case Cinq:
		return "Cinq";
		break;
	case Six:
		return "Six";
		break;
	case Sept:
		return "Sept";
		break;
	case Huit:
		return "Huit";
		break;
	case Neuf:
		return "Neuf";
		break;
	case Dix:
		return "Dix";
		break;
	case Valet:
		return "Valet";
		break;
	case Dame:
		return "Dame";
		break;
	case Roi:
		return "Roi";
		break;
	default:
		break;
	}
	return "";
}
string Magicien::colorToString(cardColor card)
{
	switch (card) {
	case nullcolor:
		return "nullcolor";
	case Pique:
		return "Pique";
	case Carreaux:
		return "Carreau";
	case Trefle:
		return "Trèfle";
	case Coeur:
		return "Coeur";
	default:
		break;
	}
	return "";
}
int Magicien::cardToInt(cardNumber card)
{
	switch (card) {
	case nullcard:
		return 0;
		break;
	case As:
		return 1;
		break;
	case Deux:
		return 2;
		break;
	case Trois:
		return 3;
		break;
	case Quatre:
		return 4;
		break;
	case Cinq:
		return 5;
		break;
	case Six:
		return 6;
		break;
	case Sept:
		return 7;
		break;
	case Huit:
		return 8;
		break;
	case Neuf:
		return 9;
		break;
	case Dix:
		return 10;
		break;
	case Valet:
		return 11;
		break;
	case Dame:
		return 12;
		break;
	case Roi:
		return 13;
		break;
	default:
		break;
	}
}
#pragma endregion Setter

#pragma region Gameplay



void Magicien::heal(Perso* a)
{
	if (getMana() >= 10) {

		

		if (a->getName() == getName()) {
			cout << getName() << " se soigne et se rends " << getDamage() << " HP !\n";
			changeHealth(getHealth() + getDamage());
		}
		else
		{
			cout << getName() << " soigne " << a->getName() << " et lui rends " << getDamage() << " HP !\n";
			a->changeHealth(a->getHealth() + getDamage());
		}
	}
	else {
		cout << getName() << " n'a pas assez de mana !\n";
	}
}

void Magicien::manageInput(string input, Perso* e){
	if (input == "Attack") {
		attack(e);
	}
	if (input == "Draw Card") {
		drawCard(e);
	}
	else if (input == "Fire Ball") {
		fireball(e);
	}
	else if (input == "Heal") {
		heal(e);
	}

}

void Magicien::drawCard(Perso* e)
{
	if (getMana() >= 10) {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> numberRNG(1,13);
		uniform_int_distribution<> colorRNG(1, 4);
		cardNumber cardValue = static_cast<cardNumber>(numberRNG(gen));
		cardColor Ccolor = static_cast<cardColor>(colorRNG(gen));
		cout << getName() << " a tiré un : " << cardToString(cardValue) << " de " << colorToString(Ccolor) << endl;
		int valeur = cardToInt(cardValue);
		string color = colorToString(Ccolor);
		cout << "Voulez vous attaquer ? (Oui : 1 / Non :2) [Attention ! Si vous n'attaquez pas, la carte sera perdue]\n";
		int choice =0;
		do {
			cin >> choice;

		} while (choice <0 && choice>2);
		if (choice == 1) {

			if (color == "Pique") {
				attackPique(valeur, e);
			}
			else if (color == "Carreau") {
				attackCarreau(valeur,  e);

			}
			else if (color == "Trèfle") {

				attackTrefle(valeur, e);
			}
			else if (color == "Coeur") {
				//attackCoeur(valeur, e);
				attackPique(valeur, e); // Methode attackCoeur pas fini de mettre à jour
			}
		}
		else if (choice == 2) {
			cout << "Carte défaussée\n";
		}
		changeMana(10);
	}
	else {
		cout << getName() << " n'a pas assez de mana !\n";
	}
}

#pragma region DrawTypeAttack
void Magicien::attackCoeur(int valeur, Perso* a)
{
	
	 if (valeur == 1) {
		 cout << getName() << " soigne " << a->getName() << " et lui rends " << getDamage() * 5 << " HP !\n";
		 a->changeHealth(a->getHealth() + getDamage() * 5);
	 }
	 else if (valeur <= 4) {
		 cout << getName() << " soigne " << a->getName() << " et lui rends " << getDamage() * 0.5f << " HP !\n";
		 a->changeHealth(a->getHealth() + getDamage() * 0.5f);
	 }
	 else if (valeur <= 7) {
		 cout << getName() << " soigne " << a->getName() << " et lui rends " << getDamage() * 1 << " HP !\n";
		 a->changeHealth(a->getHealth() + getDamage() * 1);
	 }
	 else if (valeur <= 10) {
		 cout << getName() << " soigne " << a->getName() << " et lui rends " << getDamage() * 1.5f << " HP !\n";
		 a->changeHealth(a->getHealth() + getDamage() * 1.5f);
	 }
	 else if (valeur <= 13) {
		 cout << getName() << " soigne "<< a->getName()  <<" et lui rends "<<getDamage()*2 <<" HP !\n";
		 a->changeHealth(a->getHealth() + getDamage() * 2);
	 }
}
void Magicien::attackPique(int valeur,  Perso* e)
{
	
	if (valeur == 1) {
		cout << getName() << "lance une attaque unique !\n";
		e->changeHealth(e->getHealth() - getDamage() * 5);
	}
	else if (valeur <=4) {
		cout << getName() << "lance une attaque faible!\n";
		e->changeHealth(e->getHealth() - getDamage() * 0.5f);
	}
	else if (valeur<= 7) {
		cout << getName() << "lance une attaque normale!\n";
		e->changeHealth(e->getHealth() - getDamage() * 1);
	}
	else if ( valeur <= 10) {
		cout << getName() << "lance une attaque forte !\n";
		e->changeHealth(e->getHealth() - getDamage() * 1.5f);
	}
	else if ( valeur <= 13) {
		cout << getName() << "lance une attaque puissante !\n";
		e->changeHealth(e->getHealth() - getDamage() * 2);
	}


}
void Magicien::attackTrefle(int valeur, Perso* e)
{
	
	if (valeur == 1) {
		cout << getName() << " inflinge un poison pendant 5 tours\n";
		e->changeTourDoT(getTourDoT() + 5);
	

	}
	else if (valeur <= 4) {
		cout << getName() << " inflinge un poison pendant 1 tours\n";
		e->changeTourDoT(getTourDoT()+1);
		
	}
	else if (valeur <= 7) {
		cout << getName() << " inflinge un poison pendant 2 tours\n";
		e->changeTourDoT(getTourDoT() + 2);
		
	}
	else if (valeur <= 10) {
		cout << getName() << " inflinge un poison pendant 3 tours\n";
		e->changeTourDoT(getTourDoT() + 3);
	
	}
	else if (valeur <= 13) {
		cout << getName() << " inflinge un poison pendant 4 tours\n";
		e->changeTourDoT(getTourDoT() + 4);
		
	}
}
void Magicien::attackCarreau(int valeur, Perso* e)
{
	
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> numberRNG(0, 100);
	int RNG = numberRNG(gen);
		if (valeur == 1) {
			cout << getName() << "étourdit à coup sûr " << e->getName() << '\n';
			e->changeIsStunned(true);


		}
		else if (valeur <= 4) {
			cout << getName() << "essaie d'étourdir " << e->getName() << " avec un sort de confusion !\n";
			if (RNG <= 20) {
			
				e->changeIsStunned(true);
				cout << "Sort réussi, " << e->getName() << " est étourdi !\n";

			}
			else {
				cout << e->getName() << " a résisté au sort !\n";
			}
		}
		else if (valeur <= 7) {
			cout << getName() << " essaie d'étourdir " << e->getName() << " avec un sort de confusion !\n";
			if (RNG <= 40) {
				e->changeIsStunned(true);
				cout << "Sort réussi, " << e->getName() << " est étourdi !\n";
			}
			else {
				cout << e->getName() << " a résisté au sort !\n";
			}
		}
		else if (valeur <= 10) {
			cout << getName() << " essaie d'étourdir " << e->getName() << " avec un sort de confusion !\n";
			if (RNG <= 60) {
				e->changeIsStunned(true);
				cout << "Sort réussi, " << e->getName() << " est étourdi !\n";
			}
			else {
				cout << e->getName() << " a résisté au sort !\n";
			}
		}
		else if (valeur <= 13) {
			cout << getName() << " essaie d'étourdir " << e->getName() << " avec un sort de confusion !\n";
			if (RNG <= 80) {
				e->changeIsStunned(true);
				cout << "Sort réussi, " << e->getName() << " est étourdi !\n";
			}
			else {
				cout << e->getName() << " a résisté au sort !\n";
			}
		}
}
#pragma endregion DrawTypeAttack


void Magicien::fireball(Perso* e)
{
	if (getMana() >= 10) {
		cout << getName() << " envoie une boule de feu sur " << e->getName() << " !\n";
		e->changeHealth(e->getHealth() - getDamage() * 1.5f);
		cout << e->getName() << " perds " << getDamage() * 1.5f << " , il lui reste " << e->getHealth() << " PV !\n";
	}
	else {
		cout << getName() << " n'a pas assez de Mana !";
	}
}

#pragma endregion Gameplay