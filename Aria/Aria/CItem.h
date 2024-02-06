#pragma once
#include <iostream>
#include <vector>
#include <random>
using namespace std;
class CItem
{
private:
	string name = "Bob";
	int bonusDamage = 0;
	int bonusHealth = 0;
	int bonusMana = 0;
	bool equipped = false;
	bool inInventory = false;
	//vector<CItem*> arme = { new CItem("épée",20,0,0) };
public:
	CItem();
	CItem(string n, int bd, int bh, int bm);
	string getName() const;
	int getBonusDamage() const;
	int getBonusHealth() const;
	int getBonusMana() const;
	bool getEquipped()const;
	bool getInInventory()const;
	//vector<CItem*> getWeapon()const;

	void changeName(string n);
	void changeBonusDamage(int bd);
	void changeBonusHealth(int bh);
	void changeBonusMana(int bm);
	void changeEquipped(bool e);
	void changeInInventory(bool in);
	friend ostream& operator<<(ostream& os, CItem const& p);
};