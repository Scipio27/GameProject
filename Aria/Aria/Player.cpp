#include "Player.h"

Player::Player()
{
	changeX(9);
	changeY(5);
	changeZ(0);
}

Player::Player(string newName)
{
	changeName(newName);
}


void Player::buff()
{
	health *= 2;
}

void Player::changeName(string newName)
{
	if (newName != "") {
		name = newName;
	}
	else {
		cout << "Nom vide !" << endl;
	}
}

void Player::changeHealth(int newHealth)
{
	if (newHealth < 0) {
		cout << "Vie non valide !" << endl;
		health = 0;
	}
	else {
		health = newHealth;
	}
}

void Player::changeDamage(int newDamage)
{
	if (damage < 0) {
		cout << "Damage non valide !" << endl;
		damage = 0;
	}
	else {
		damage = newDamage;
	}
}

void Player::changeX(int newX)
{
	x = newX;
}

void Player::changeY(int newY)
{
	y = newY;
}

void Player::changeZ(int newZ)
{
	z = newZ;
}
void Player::changeMana(int newMana)
{
	mana = newMana;
	if (mana < 0) {
		cout << "Mana non valide !" << endl;
		mana = 0;
	}
}

void Player::changIsWeapon(bool iw)
{
	isWeapon = iw;
}

void Player::fillInventory(CItem* ci)
{
	if (ci != nullptr) {
		if (!ci->getInInventory()) {
			ci->changeInInventory(true);
			inventory.push_back(ci);
		}
		else {
			cout << *ci << " déjà dans l'inventaire !" << endl;
		}
	}
	else {
		cout << "L'objet n'existe pas !" << endl;
	}
}

CItem* Player::throwInventory(CItem* ci)
{
	vector<CItem*>::iterator it = find(inventory.begin(), inventory.end(), ci);
	if (it != inventory.end()) {
		if (ci->getEquipped()) {
			int choix = 0;
			do {
				cout << *ci << " est équipé si vous le jeter vous perdrez ses stats. Voulez-vous continuer ? (1- oui, 2- non) ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (!(cin >> choix) || choix < 1 || choix > 2);

			if (choix == 2) {
				return nullptr;
			}
			unequipItem(ci);
		}
		ci->changeInInventory(false);
		inventory.erase(it);
		return ci;
	}
	else {
		cout << *ci << " n'est pas dans l'inventaire !" << endl;
		return nullptr;
	}
}

CItem* Player::throwInventory(int i)
{
	if (i < inventory.size() && i > 0) {
		CItem* temp = inventory[i - 1];
		if (temp->getEquipped()) {
			int choix = 0;
			do {
				cout << *temp << " est équipé si vous le jeter vous perdrez ses stats. Voulez-vous continuer ? (1- oui, 2- non) ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (!(cin >> choix) || choix < 1 || choix > 2);

			if (choix == 2) {
				return nullptr;
			}
			unequipItem(temp);
		}
		temp->changeInInventory(false);
		inventory.erase(inventory.begin() + i - 1);
		return temp;
	}
	else {
		cout << i << " n'appartient pas à l'inventaire !" << endl;
		return nullptr;
	}
}

void Player::equipItem(CItem* ci)
{
	Equipment e;
	vector<string> tmp, tmp2;;
	for (int i = 0; i < e.getArme().size(); i++) {
		tmp.push_back(e.getArme()[i]->getName());
	}
	for (int i = 0; i < e.getEquipement().size(); i++) {
		tmp2.push_back(e.getEquipement()[i]->getName());
	}

	if (ci != nullptr) {
		if (ci->getName().compare(0, 5, "potion") != 0 || ci->getName().compare(0, 8, "parchemin") != 0) {
			if (!ci->getEquipped()) {

				if (find(tmp.begin(), tmp.end(), ci->getName()) != tmp.end() && getIsWeapon()) {

					for (int i = 0; i < inventory.size(); i++) {
						if (find(tmp.begin(), tmp.end(), inventory[i]->getName()) != tmp.end() && inventory[i]->getEquipped()) {
							unequipItem(inventory[i]);
							break;
						}
					}
					changIsWeapon(true);
				}
				else if (find(tmp.begin(), tmp.end(), ci->getName()) != tmp.end()) {
					changIsWeapon(true);
				}
				else if (find(tmp2.begin(), tmp2.end(), ci->getName()) != tmp2.end() || ci->getName().compare(0, 8, "amulette") == 0 || ci->getName().compare(0, 6, "anneau") == 0) {
					for (int i = 0; i < inventory.size(); i++) {
						if (inventory[i]->getEquipped() && (find(tmp2.begin(), tmp2.end(), inventory[i]->getName()) != tmp2.end() || ci->getName().compare(0, 7, "amulette") == 0 || ci->getName().compare(0, 5, "anneau") == 0)) {
							unequipItem(inventory[i]);
							break;
						}
					}
				}
				ci->changeEquipped(true);
				changeDamage(ci->getBonusDamage() + getDamage());
				changeHealth(ci->getBonusHealth() + getHealth());
				changeMana(ci->getBonusMana() + getMana());
				cout << *ci << " vous confère " << ci->getBonusDamage() << " damage, ";
				cout << ci->getBonusHealth() << " point de vie et " << ci->getBonusMana() << " mana" << endl;
			}
			else {
				cout << *ci << " déjà équipé(e) !" << endl;
			}
		}
		else {
			cout << *ci << " ne peut pas être équipée seulement utilisé ! " << endl;
		}

	}
	else {
		cout << "L'objet n'existe pas !" << endl;
	}
}

void Player::equipItem(int i)
{
	if (i < inventory.size()) {
		equipItem(inventory[i - 1]);
	}
	else {
		cout << "La valeur entrée ne correspond à l'emplacement d'aucun item ! " << endl;
	}

}

void Player::unequipItem(CItem* ci)
{
	Equipment e;
	vector<string> tmp;
	for (int i = 0; i < e.getArme().size(); i++) {
		tmp.push_back(e.getArme()[i]->getName());
	}
	if (ci != nullptr) {
		if (ci->getEquipped()) {
			ci->changeEquipped(false);
			changeDamage(getDamage() - ci->getBonusDamage());
			changeHealth(getHealth() - ci->getBonusHealth());
			changeMana(getMana() - ci->getBonusMana());
			if (find(tmp.begin(), tmp.end(), ci->getName()) != tmp.end()) {
				changIsWeapon(false);
			}
		}
		else {
			cout << *ci << " n'est pas équipé(e) !" << endl;
		}
	}
	else {
		cout << "L'objet n'existe pas !" << endl;
	}
}

void Player::unequipItem(int i)
{
	if (i < inventory.size()) {
		unequipItem(inventory[i - 1]);
	}
	else {
		cout << "La valeur entrée ne correspond à l'emplacement d'aucun item ! " << endl;
	}
}

void Player::useItem(CItem* ci)
{
	if (ci != nullptr) {
		if (find(inventory.begin(), inventory.end(), ci) != inventory.end()) {
			if (ci->getName().compare(0, 6, "potion") == 0 || ci->getName().compare(0, 9, "parchemin") == 0) {
				changeDamage(ci->getBonusDamage() + getDamage());
				changeHealth(ci->getBonusHealth() + getHealth());
				changeMana(ci->getBonusMana() + getMana());
				throwInventory(ci);
				cout << *ci << " vous confère " << ci->getBonusDamage() << " damage, ";
				cout << ci->getBonusHealth() << " point de vie et " << ci->getBonusMana() << " mana" << endl;
			}
			else {
				//equipItem(ci);
				cout << *ci << " n'est pas un consommable ! " << endl;
			}
		}
		else {
			cout << *ci << " n'est pas dans l'inventaire !" << endl;
		}

	}
	else {
		cout << "La valeur entrée ne correspond à aucun item !" << endl;
	}
}

void Player::useItem(int i)
{
	if (i <= inventory.size()) {
		useItem(inventory[i - 1]);
	}
	else {
		cout << "La valeur entrée ne correspond à l'emplacement d'aucun item ! " << endl;
	}
}

void Player::showMenu(int index, vector<string>& menu)
{
	for (int i = menu.size() - 1; i >= 0; i--) {
		if (i == index) {
			cout << '>';
		}
		cout << menu[i] << endl;
	}
}

void Player::showInventory()
{
	cout << "Votre inventaire contient : " << endl << "[ " << endl;
	for (int i = 0; i < inventory.size(); i++) {
		cout << i + 1 << ". " << *inventory[i];
		if (inventory[i]->getEquipped())
			cout << " (équipé)";

		if (i < inventory.size() - 1)
			cout << ", " << endl;
	}
	cout << endl << " ]" << endl;
	cout << "Voulez-vous utiliser (1), équiper(2) ou jeter(3) un item ? retour(4) " << endl;
	int choix = 0, val = 0;	
	do {
		cin >> choix;
		if (!(cin >> choix)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		
	} while (choix < 1 || choix > 4);

	switch (choix) {
	case 1:
		cout << "Choisissez un item à utiliser "; cin >> val;
		useItem(val);
		break;
	case 2:
		cout << "Choisissez un item à équiper "; cin >> val;
		equipItem(val);
		break;
	case 3:
		cout << "Choisissez un item à jeter "; cin >> val;
		throwInventory(val);
		break;
	case 4:
		break;
	default:
		break;
	}
}

string Player::playerTurn(vector<string> menu, vector <Perso*> e, vector <Perso*> a)
{
	int arrow;
	bool validate = false;
	string output;
	int index = menu.size() - 1;
	while (!validate) {
		system("cls");
		printPerso(e);
		cout << "			   " << "__      _______ " << endl;
		cout << "			   " << "\\ \\    / / ____|" << endl;
		cout << "			   " << " \\ \\  / / (___  " << endl;
		cout << "			   " << "  \\ \\/ / \\___ \\ " << endl;
		cout << "			   " << "   \\  /  ____) |" << endl;
		cout << "			   " << "    \\/  |_____/ " << endl << endl;
		printPerso(a);
		cout << "Tour de " << getName() << endl;
		showMenu(index, menu);
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
			if (output == "Back")  menu = getFightMenu();
			else if (output == "Skills")menu = getSkillList();
			else validate = true;
			break;
		default:
			break;
		}
	}
	return output;
}


string Player::getName() const
{
	return name;
}

int Player::getHealth() const
{
	return health;
}

int Player::getDamage() const
{
	return damage;
}

int Player::getX()
{
	return x;
}

int Player::getY()
{
	return y;
}

int Player::getZ()
{
	return z;
}

vector<string> Player::getFightMenu()
{
	return fightMenu;
}

vector<string> Player::getSkillList()
{
	return skillList;
}

vector<string> Player::getItemMenu()
{
	return itemMenu;
}

int Player::getMenuIndex(vector<string>& menu, string toSearch)
{
	for (int i = 0; i < menu.size(); i++) {
		if (menu[i] == toSearch) return i;
	}
	return -1;
}

int Player::getMana() const
{
	return mana;
}

vector<CItem*> Player::getInventory()
{
	return inventory;
}

bool Player::getIsWeapon() const
{
	return isWeapon;
}

void Player::attack(Perso* e) {
	cout << getName() << " attaque " << e->getName() << " et lui enlève " << getDamage() << " PV !\n";
	e->changeHealth(e->getHealth() - getDamage());
	cout << "Il lui reste " << e->getHealth() << " PV !\n";
}