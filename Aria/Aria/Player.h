#pragma once
#include "Perso.h"
#include "Equipment.h"
#include "Resource.h"
#include <conio.h>

class Player : public Perso {

protected:
	vector<CItem*> inventory;
	vector<string> menu = {"Leave"};
	vector<string> fightMenu = {"Skills", "Attack"};
	vector<string> skillList = {"Back"};
	vector<string> itemMenu = { "Take", "Equip", "Leave" };
	bool isWeapon = false;
	int x, y, z;

	//vector<CItem*> inventory;
public:
	Player();
	Player(string newName);

	void buff();

	//Getter
	string getName() const;
	int getHealth() const;
	int getDamage() const;
	int getMana() const;
	vector<CItem*> getInventory();
	bool getIsWeapon() const;
	int getX();
	int getY();
	int getZ();
	vector<string> getFightMenu();
	vector<string> getSkillList();
	vector<string> getItemMenu();

	int getMenuIndex(vector<string>& menu, string toSearch);

	//Setter
	void changeName(string newName);
	void changeHealth(int newHealth);
	void changeDamage(int newDamage);
	void changeMana(int newMana);
	void changIsWeapon(bool iw);
	void fillInventory(CItem* ci);
	CItem* throwInventory(CItem* ci);
	CItem* throwInventory(int i);
	void changeX(int newX);
	void changeY(int newY);
	void changeZ(int newZ);


	void equipItem(CItem* ci);
	void equipItem(int i);
	void unequipItem(CItem* ci);
	void unequipItem(int i);
	void useItem(CItem* ci);
	void useItem(int i);
	void showMenu(int index, vector<string>& menu);

	void showInventory();

	void attack(Perso* e);
	string playerTurn(vector<string> menu, vector <Perso*> e, vector <Perso*> a);

	virtual void manageInput(string input, Perso* p)=0;

};