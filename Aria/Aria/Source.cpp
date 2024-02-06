#define NOMINMAX
#include <windows.h>
#include <conio.h>
#include "Room.h"
#include "Equipment.h"
#include "Resource.h"
#include "Boss.h"
#include "Magicien.h"
#include "Guerrier.h"
#include "Voleur.h"

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> cell(1, 4);

struct {
	bool operator()(Perso* a, Perso* e) const { return a->getInitiative()>e->getInitiative(); }
} customLess;

//Perso* turn(vector<Perso*> a, vector<Perso*> e, bool& player) {
//
//	sort(a.begin(), a.end(), customLess);
//	sort(e.begin(), e.end(), customLess);
//
//	while (a[0]->getInitiative() < 100 && e[0]->getInitiative() < 100) {
//		for (Perso* currentPlayer : a) {
//			currentPlayer->changeInitiative(currentPlayer->getInitiative() + 10);
//		}
//		for (Perso* currentEnemy : e) {
//			currentEnemy->changeInitiative(currentEnemy->getInitiative() + 10);
//		}
//
//	}
//	if (a[0]->getInitiative() >= e[0]->getInitiative()) {
//		player = true;
//		a[0]->changeInitiative(0);
//		return a[0];
//
//
//	}
//	else {
//		player = false;
//		e[0]->changeInitiative(0);
//		return e[0];
//
//	}
//}

void initiativeIncrement(vector<Perso*>& a, vector<Perso*>& e) {
	for (Perso* p : a) {
		p->changeInitiative(p->getInitiative() + 10);
	}
	for (Perso* enemy : e) {
		enemy->changeInitiative(enemy->getInitiative() + 10);
	}
}

/*void allyTurn(vector<Perso*> a, vector<Perso*>& e, string attack) {

	sort(a.begin(), a.end(), customLess);
	Perso* currentAttacker = a[0];
	
	if (Magicien* m = dynamic_cast<Magicien*>(currentAttacker)) {
		if (attack == "Draw Card") {
			m->drawCard(m->getMana(), e, a);
		}
		else if (attack == "Heal") {
			m->heal(m->getMana(), a);
		}
		else if (attack == "Fire Ball") {
			m->fireball(m->getMana(), e);
		}

	}


	else if (Guerrier* g = dynamic_cast<Guerrier*>(currentAttacker)) {
		
	}


	else if (Voleur* v = dynamic_cast<Voleur*>(currentAttacker)) {
		if (attack == "Back Stab") {
			v->backStab(e);
			initiativeIncrement(a, e);
		}
		else if (attack == "Steal") {
			v->steal(e);
			initiativeIncrement(a, e);
		}
		else if (attack == "Stealth") {
			v->stealth();
			initiativeIncrement(a, e);
		}

	}
	cout << "a[0]: \n Nom : " << a[0]->getName() << "\nInitiative : " << a[0]->getInitiative()<<"\n";
	system("pause");
	a[0]->changeInitiative(0);
	cout << "a[0]: \n Nom : " << a[0]->getName() << "\nInitiative : " << a[0]->getInitiative()<<"\n";
	system("pause");
	

}*/

/*void duringFight(vector<Perso*>& a, vector<Perso*>& e) {

	while (a[0]->getInitiative() < 100 && a[1]->getInitiative() < 100 && a[2]->getInitiative() < 100) {
		sort(a.begin(), a.end(), customLess);
		sort(e.begin(), e.end(), customLess);
		if (e[0]->getInitiative() == 100) {
			e[0]->attack(a);
			e[0]->changeInitiative(0);
		
	
		}
		initiativeIncrement(a, e);
	}

}*/

void fight(vector <Perso*>& a, vector <Perso*>& e) {
	bool allDead = false;
	int checkAllDeadEnemy = 0;
	int checkAllDeadPlayer = 0;

	while (!allDead) {
		sort(a.begin(), a.end(), customLess);
		sort(e.begin(), e.end(), customLess);
		while (a[0]->getInitiative() < 100 && e[0]->getInitiative() < 100) {
			initiativeIncrement(a, e);
		}
		if (a[0]->getInitiative() >= e[0]->getInitiative()) {
			if (a[0]->getIsDead()) {
				a[0]->changeInitiative(0);
			}
			else {


				Player* p = dynamic_cast<Player*>(a[0]);
				string input = p->playerTurn(p->getFightMenu(), e, a);
				vector<string> Persos;
				Perso* cible = nullptr;
				if (input != "Stealth" && input != "Taunt") {
					if (input == "Protect" || input == "Heal") {
						for (Perso* player : a) {
							Persos.push_back(player->getName());
						}
					}
					else {
						for (Perso* enemy : e) {
							Persos.push_back(enemy->getName());
						}
					}
					string cibleName = p->playerTurn(Persos, e, a);
					for (Perso* enemy : e) {
						if (enemy->getName() == cibleName) {
							cible = enemy;
							break;
						}
					}
					for (Perso* player : a) {
						if (player->getName() == cibleName) {
							cible = player;
							break;
						}
					}
				}
				cout << '\n';

				p->manageInput(input, cible);
				a[0]->changeInitiative(0);
				cout << '\n';
				for (Perso* enemy : e) {
					if (enemy->getIsDead()) {
						checkAllDeadEnemy++;
					}
					else {
						checkAllDeadEnemy = 0;
					}
				}

				if (checkAllDeadEnemy >= e.size()) {
					allDead = true;
				}
			}
		}
		else {
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<> RNG(0, a.size() - 1);
			if (e[0]->getIsDead()) {
				e[0]->changeInitiative(0);

			}
			else {


				Perso* playerToAttack = a[RNG(gen)];
				do {
					playerToAttack = a[RNG(gen)];
				} while (playerToAttack->getStealth());
				if (playerToAttack->getIsProtected()) {
					for (Perso* playerGuarding : a) {
						if (playerGuarding->getIsProtecting()) {
							playerToAttack = playerGuarding;
						}
					}
				}
				e[0]->attack(playerToAttack);
				e[0]->changeInitiative(0);
				for (Perso* player : a) {
					if (player->getIsDead()) {
						checkAllDeadPlayer++;
					}
					else {
						checkAllDeadPlayer = 0;
					}
				}
				if (checkAllDeadPlayer >= a.size()) {
					allDead = true;
				}


				system("pause");
			}

			

		}

	}
}

void item(vector<Perso*>& a) {
	int val = 0;
	Equipment e;
	if (rand() % 2) {
		Resource r;
		cout << "Voulez-vous prendre " << r.getName() << " ? (1.oui, 2.non)" << endl;
		cout << "Si vous ne récupérez pas l'item, il risque d'être volé par un gobelin !" << endl;
		cin >> val;
		if (val == 1) {
			cout << "Qui doit le prendre 1- " << a[0]->getName() << ", 2- " << a[1]->getName() << " ou 3- " << a[2]->getName();
			cin >> val;
			((Player*)a[val - 1])->fillInventory(r.getSelected());
		}
	}

	cout << "Voulez-vous 1- prendre, 2- équiper ou 3- ne pas toucher à " << e.getName() << " ?" << endl;
	cout << "Si vous ne récupérez pas l'item il risque d'être volé par un gobelin !" << endl;
	cin >> val;
	if (val == 1) {
		cout << "Qui doit le prendre 1- " << a[0]->getName() << ", 2- " << a[1]->getName() << " ou 3- " << a[2]->getName();
		cin >> val;
		((Player*)a[val - 1])->fillInventory(e.getSelected());
	}
	else if (val == 2) {
		cout << "Qui doit l'équiper 1- " << a[0]->getName() << ", 2- " << a[1]->getName() << " ou 3- " << a[2]->getName();
		cin >> val;
		((Player*)a[val - 1])->fillInventory(e.getSelected());
		((Player*)a[val - 1])->equipItem(e.getSelected());
	}
}

/*int select(int index, vector<string> menu, vector <Perso*> e, vector<Perso*>& a)
{
	
	int i = index;
	bool selection = false;
	string categorie;
	int arrow;
	sort(a.begin(), a.end(), customLess);
	Perso* currentPlayer = a[0];
	Player* p = dynamic_cast<Player*>(currentPlayer);
	
	while (selection != true) {
		showMenu(i, menu);
		arrow = _getch();
		switch (arrow) {
		case 72:
			//cout << "Avant incrémentation : " << i << endl;
			if (i < menu.size() - 1) {
				i++;
				//cout << "Après incrémentation : " << i << endl;
			}
			showMenu(i, menu);
			break;
		case 80:
			//cout << "Avant incrémentation : " << i << endl;
			if (i > 0) {
				i--;
				//cout << "Après incrémentation : " << i << endl;
			}
			showMenu(i, menu);
			break;
		case 13:
			if (menu[i] == "Fight !") {
			
				showMenu(p->getFightMenu().size() - 1, p->getFightMenu());
				select(p->getFightMenu().size() - 1, p->getFightMenu(),e, a);
				break;
			}
			else if (menu[i] == "Search") {
				selection = true;
				break;
			}
			else if (menu[i] == "Skills") {
				showMenu(p->getSkillList().size() - 1, p->getSkillList());
				select(p->getSkillList().size() - 1, p->getSkillList(),e, a);
				categorie = "Fight !";
				break;
			}
			else if (menu[i] == "Leave") {
				selection = true;
			}
			else if (menu[i] == "Draw Card") {
				fight(a, e, "Draw Card");	
			}
			else if (menu[i] == "Fire Ball") {
				fight(a, e, "Fire Ball");
			}
			else if (menu[i] == "Heal") {
				fight(a, e, "Heal");
			}
			else if (menu[i] == "Big Attack") {
				fight(a, e, "Big Attack");
			}
			else if (menu[i] == "Protect") {
				fight(a, e, "Protect");
			}
			else if (menu[i] == "Taunt") {
				fight(a, e, "Taunt");
			}
			else if (menu[i] == "Steal") {
				fight(a, e, "Steal");
			}
			else if (menu[i] == "Stealth") {
				fight(a, e, "Stealth");
			}
			else if (menu[i] == "Back Stab") {
				fight(a, e, "Back Stab");
			}
			else if (menu[i] == "Back") {
				if (categorie == "Fight !") {
					selection = true;
				}
				else if (categorie == "Skills") {
					showMenu(p->getSkillList().size() - 1, p->getSkillList());
					select(p->getSkillList().size() - 1, p->getSkillList(),e, a);
					break;
				}
				else {
					selection = true;
				}
			}
			break;
		default:
			break;
		}
	}
	return 0;
}*/

void createMap(Room* map[10][10][3]) {
	for (int k = 0; k < 3; k++) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				map[i][j][k] = new Room(i, j, k, 5);
			}
		}
	}

	int i = 9;
	int j = 5;
	int nbRoom = 0;
	for (int k = 0; k < 3; k++) {
		map[i][j][k] = new Room(i, j, k, 6);
	}

	for (int k = 0; k < 3; k++) {
		nbRoom = 0;
		i = 9;
		j = 5;

		do {
			switch (cell(gen)) {
			case 1:
				if (i > 0) {
					if (map[--i][j][k]->getName() == ' ') {
						map[i][j][k] = new Room(i, j, k);
						//cout << "1 - Creating Room in " << i << " - " << j << " - " << k << " : " << *map[i][j][k] << " - named : " << map[i][j][k]->getName() << " nbRoom = " << nbRoom << endl;
						if (Room::isCreated != true) {
							map[i][j][k] = new Room(i, j, k, 5);
							i++;
						}
						else {
							nbRoom++;
						}
					}
					else {
						//cout << "Essaie d'aller en haut" << endl;
						i++;
					}
				}
				else if (j == 0) {
					nbRoom = 15;
					//cout << " 1 - nbRoom forced set to 15" << endl;
				}
				break;
			case 2:
				if (j > 0) {
					if (map[i][--j][k]->getName() == ' ') {
						map[i][j][k] = new Room(i, j, k);
						//cout << "2 - Creating Room in " << i << " - " << j << " - " << k << " : " << *map[i][j][k] << " - named : " << map[i][j][k]->getName() << " nbRoom = " << nbRoom << endl;
						if (Room::isCreated != true) {
							map[i][j][k] = new Room(i, j, k, 5);
							j++;
						}
						else {
							nbRoom++;
						}
					}
					else {
						//cout << "Essaie d'aller à gauche" << endl;
						j++;
					}
				}
				else if (i == 0) {
					nbRoom = 15;
					//cout << "2 - nbRoom forced set to 15" << endl;
				}
				break;
			case 3:
				if (j < 9) {
					if (map[i][++j][k]->getName() == ' ') {
						map[i][j][k] = new Room(i, j, k);
						//cout << "3 - Creating Room in " << i << " - " << j << " - " << k << " : " << *map[i][j][k] << " - named : " << map[i][j][k]->getName() << " nbRoom = " << nbRoom << endl;
						if (Room::isCreated != true) {
							map[i][j][k] = new Room(i, j, k, 5);
							j--;
						}
						else {
							nbRoom++;
						}
					}
					else {
						//cout << "Essaie d'aller à droite" << endl;
						j--;
					}
				}
				else if (i == 0) {
					nbRoom = 15;
					//cout << "3 - nbRoom forced set to 15" << endl;
				}
				break;
			}
			/*for (int k = 0; k < 3; k++) {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						cout << *map[i][j][k];
					}
					cout << endl;
				}
				cout << "---------------------------" << endl;
			}*/

		} while (nbRoom < 15);
		/*cout << Room::nbFightRoom;
		cout << Room::nbRestRoom;
		cout << Room::nbItemRoom << endl;
		cout << Room::nbFightRoomMax ;
		cout << Room::nbRestRoomMax;
		cout << Room::nbItemRoomMax << endl << endl;*/
		map[i][j][k] = new Room(i, j, k, 4);

		for (int i = 0; i < 4; i++) {
			Room::nbRoom[i] = 0;
		}
	}
}

void printMap(Room* map[10][10][3], int k, Player* p) {
	//for (int k = 0; k < 3; k++) {
	system("cls");
		cout << "   Étage " << k + 1 << endl;
		cout << " ----------" << endl;
		for (int i = 0; i < 10; i++) {
			cout << '|';
			for (int j = 0; j < 10; j++) {
				if(map[i][j][k]->getIsDiscovered() != false) {
					if (p->getX() == i && p->getY() == j && p->getZ() == k) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
					}
					cout << map[i][j][k]->getName();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
				else {
					cout << '?';
				}
				
			}
			cout << '|' << endl;
		}
		cout << " ----------" << endl;
	//}
}

void printRoom(Room* map[10][10][3], int i, int j, int k) {
		cout << *map[i][j][k];
}

void showRoomMenu(int index, vector<string>& menu)
{
	for (int i = menu.size() - 1; i >= 0; i--) {
		if (i == index) {
			cout << '>';
		}
		cout << menu[i] << endl;
	}
}

void Repos(vector<Perso*>& a) {
	for (int i = 0; i < 3; i++) {
		a[i]->changeHealth(a[i]->getHealth()+50);
	}
}

string roomChoice(vector<string> menu, vector<Perso*>& a, vector<Perso*>& e, Room* r)
{
	int arrow;
	bool validate = false;
	string output;
	int index = menu.size() - 1;
	while (!validate) {
		system("cls");
		showRoomMenu(index, menu);
		arrow = _getch();
		switch (arrow) {
		case 72:
			index + 1 > menu.size() - 1 ? index = 0 : index++;
			break;
		case 80:
			index - 1 < 0 ? index = menu.size() - 1 : index--;
			break;
		case 13:
			output = menu[index];
			if (output == "Fight !") {
				if (!r->getIsClear()) {
					fight(a, e);
					for (Perso* enemy : e) {
						enemy->changeHealth(100);
						r->setIsClear(true);
					}
				}
				else {
					cout << "Les ennemis sont tous mort !\n";
					system("pause");
				}
			}
			else if (output == "Search") {
				if (!r->getIsClear()) {
					item(a);
					r->setIsClear(true);
				}
				else {
					cout << "Il n'y a plus rien à récupérer ici !\n";
					system("pause");
				}
				
			}
			else if (output == "Rest") {
				if (!r->getIsClear()) {
					Repos(a);
					r->setIsClear(true);
				}
				else {
					cout << "Vous vous êtes déjà reposé ici !\n";
					system("pause");
				}
			}
			else if (output == "Boss Fight") {
				if (!r->getIsClear()) {
					Boss boss(((Player*)a[0])->getZ() + 1);
					vector<Perso*> b = { &boss };
					boss.dialogueBoss();
					fight(a, b);
					system("cls");
					boss.dialogueBoss();
					r->setIsClear(true);
				}
				else {
					cout << "Le boss n'est plus dans la salle" << endl << "Quitter la salle et appuyer sur espace pour passer au prochain étage" << endl;
					system("pause");
				}
				
			}
			else validate = true;
			break;
		default:
			break;
		}
		
	}
	return output;
}

void move(Player* p, Room* map[10][10][3],vector<Perso*>& e, vector<Perso*>& a) {
	int arrow;
	bool move = true;
	 do {
		arrow = _getch();
		
		switch (arrow) {
		case 72:
			if (p->getX() > 0 && map[p->getX() - 1][p->getY()][p->getZ()]->getName() != ' ') {
				/*cout << "Haut !" << endl;*/
				p->changeX(p->getX() - 1);
				map[p->getX()][p->getY()][p->getZ()]->setIsDiscovered(true);
				printRoom(map, p->getX(), p->getY(), p->getZ());
				/*cout << "X = " << p->getX() << endl;
				cout << "Y = " << p->getY() << endl;*/
			}
			else {
				cout << "Nan ! C'est un mur ça !" << endl;
			}
			printMap(map, p->getZ(), p);
			break;
		case 80:
			if (p->getX() < 9 && map[p->getX() + 1][p->getY()][p->getZ()]->getName() != ' ') {
				/*cout << "Bas !" << endl;*/
				p->changeX(p->getX() + 1);
				map[p->getX()][p->getY()][p->getZ()]->setIsDiscovered(true);
				printRoom(map, p->getX(), p->getY(), p->getZ());
				/*cout << "X = " << p->getX() << endl;
				cout << "Y = " << p->getY() << endl;*/
			}
			else {
				cout << "Nan ! C'est un mur ça !" << endl;
			}
			printMap(map, p->getZ(), p);
			break;
		case 75:
			if (p->getY() > 0 && map[p->getX()][p->getY() - 1][p->getZ()]->getName() != ' ') {
				/*cout << "Gauche !" << endl;*/
				p->changeY(p->getY() - 1);
				map[p->getX()][p->getY()][p->getZ()]->setIsDiscovered(true);
				printRoom(map, p->getX(), p->getY(), p->getZ());
				/*cout << "X = " << p->getX() << endl;
				cout << "Y = " << p->getY() << endl;*/
			}
			else {
				cout << "Nan ! C'est un mur ça !" << endl;
			}
			printMap(map, p->getZ(), p);
			break;
		case 77:
			if (p->getY() < 9 && map[p->getX()][p->getY() + 1][p->getZ()]->getName() != ' ') {
				/*cout << "Droite !" << endl;*/
				p->changeY(p->getY() + 1);
				map[p->getX()][p->getY()][p->getZ()]->setIsDiscovered(true);
				printRoom(map, p->getX(), p->getY(), p->getZ());
				/*cout << "X = "<< p->getX() << endl;
				cout << "Y = " << p->getY() << endl;*/
			}
			else {
				cout << "Nan ! C'est un mur ça !" << endl;
			}
			printMap(map, p->getZ(), p);
			break;
		case 32:
			if (map[p->getX()][p->getY()][p->getZ()]->getName() == 'B') {
				if (p->getZ() < 2) {
					p->changeX(9);
					p->changeY(5);
					p->changeZ(p->getZ() + 1);
				}
				else {
					cout << "GG EZ" << endl;
					move = false;
				}
			}
			printMap(map, p->getZ(), p);
			break;
		case 13:
			//fight(a,e);
			//showMenu(map[p->getX()][p->getY()][p->getZ()]->getRoomMenu().size() - 1, map[p->getX()][p->getY()][p->getZ()]->getRoomMenu());
			roomChoice(map[p->getX()][p->getY()][p->getZ()]->getRoomMenu(), a, e, map[p->getX()][p->getY()][p->getZ()]);
			move = false;
			break;
		default:
			printMap(map, p->getZ(), p);
			break;
		}

	}while (move);
}

void lore() {
	int val = 0;
	cout << "Vous êtes un groupe d'aventuriers étant partis à la recherche de péripéties nombreuses et variées \n";
	cout << "Vous vous retrouvez à explorer une énorme plaine quand vous voyez au loin le haut de ce qui s'apparente à une tour \n";
	cout << "Voulez-vous vous en approcher ? (1- oui, 2- non) ";
	do {
		cin >> val; 
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (val < 1 || val>2) {
			cout << "La valeur entrée n'est pas valide" << endl;
		}
	} while (val < 1 || val>2);
	system("cls");
	if (val == 2) {
		cout << "Vous continuer votre chemin et ignorer ce qui a l'air d'être une tour peut-être trouverez-vous plus intrigant ailleurs \n";
		exit(0);
	}
	
	cout << "Votre bande se retrouve surexcité à l'idée de découvrir ce qu'il se cache dans cette tour au milieu de nulle ipart \n";
	cout << "Après une demi-heure de marche vous arrivez au pied d'une tour aux aspects lugubres. Il y a l'air d'y avoir personne à l'intérieur et la porte est fermée de l'intérieur mais semble facilement cassable\n";
	cout << "Voulez-vous défoncer la porte ? (1- oui, 2- non)"; 
	do {
		cin >> val;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (val < 1 || val>2) {
			cout << "La valeur entrée n'est pas valide" << endl;
		}
	} while (val < 1 || val>2);
	if (val == 2) {
		cout << "\nIl n'y a aucun autre moyen d'entrer, ne voulant pas casser la porte pensant qu'il s'agit peut-être de la demeure d'une honnête personne vos faites demi-tour et chercher d'autres endroits inexploré à découvrir\n";
		exit(0);
	}
	cout << "\nVous défoncez la porte sans aucun problème et entrez dans cette mystérieuse tour. L'aventure peut commencer !\n";
	system("pause");
}

int main() {

	SetConsoleOutputCP(1252);
	Room* map[10][10][3];
	Resource r1;
	vector<Perso*> a = { new Guerrier("Doigby",100), new Magicien("Guillaume",20), new Voleur("Klement",40) };
	//vector <Perso*> e = { nullptr };
	vector<Perso*> e = { new Enemy("Bob",80), new Enemy("Gauthier",50), new Enemy("Hugo",60) };

	lore();

	createMap(map);
	Player* p = dynamic_cast<Player*>(a[0]);
	while (true) {
		printMap(map, p->getZ(), p);
		printRoom(map, p->getX(), p->getY(), p->getZ());
		move(p, map, e,a);
	}


	/*for (int i = 0; i < 10; i++) {
		Resource r;
		cout << m << endl;
		m.fillInventory(r.getSelected());
		Equipment e;
		m.fillInventory(e.getSelected());
	//Magicien m("q",10);
	//for (int i = 0; i < 10; i++) {
	//	Resource r;
	//	cout << m << endl;
	//	m.fillInventory(r.getSelected());
	//	Equipment e;
	//	m.fillInventory(e.getSelected());
	//}
	cout << m << endl;
	m.showInventory();
	cout << m << endl;
	m.showInventory();
	m.showInventory();
	cout << m << endl;*/

/*	Boss b(3);
	cout << b << endl;
	b.dialogueBoss();
	vector<Perso*> bo = { new Boss(3) };
	
	fight(a, bo);
*/
	/*vector<Perso*> bo = { new Boss(1) };
	fight(a, bo);*/
	

	
	//fight(a, e);
	

	return EXIT_SUCCESS;


}