#pragma once
#include "CItem.h"
class Resource : public CItem
{
private:
	vector<string> power = { " mineur", " normal", " majeur" };
	vector<string> type = { " vie", " mana", " force" };
	vector<int> capacity = { 0,0,0 };
	CItem* selected = new CItem("",0,0,0);

public:
	Resource();

	vector<int> getCapacity() const;
	vector<string> getType() const;
	CItem* getSelected()const;
	string getName() const;

	void changeCapacity(vector<int> c);
	void genPotion();
	void genParchemin();
};

