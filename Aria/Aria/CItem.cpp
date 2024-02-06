#include "CItem.h"

CItem::CItem()
{
	name = "Bob";
	bonusDamage = 0;
	bonusHealth = 0;
	bonusMana = 0;
	equipped = false;
	inInventory = false;
	//arme = { new CItem("épée",20,0,0), new CItem("lance",10,0,0), new CItem("masse d'arme",30,0,0), new CItem("dague",5,0,0), new CItem("baton magique",2,0,10) };
}

CItem::CItem(string n, int bd, int bh, int bm)
{
	changeName(n);
	changeBonusDamage(bd);
	changeBonusHealth(bh);
	changeBonusMana(bm);
}

string CItem::getName() const
{
	return name;
}

int CItem::getBonusDamage() const
{
	return bonusDamage;
}

int CItem::getBonusHealth() const
{
	return bonusHealth;
}

int CItem::getBonusMana() const
{
	return bonusMana;
}

bool CItem::getEquipped() const
{
	return equipped;
}

bool CItem::getInInventory() const
{
	return inInventory;
}

//vector<CItem*> CItem::getWeapon() const
//{
//	return arme;
//}

void CItem::changeName(string n)
{
	name = n;
}

void CItem::changeBonusDamage(int bd)
{
	bonusDamage = bd;
}

void CItem::changeBonusHealth(int bh)
{
	bonusHealth = bh;
}

void CItem::changeBonusMana(int bm)
{
	bonusMana = bm;
}

void CItem::changeEquipped(bool e)
{
	equipped = e;
}

void CItem::changeInInventory(bool in)
{
	inInventory = in;
}

ostream& operator<<(ostream& os, CItem const& p)
{
	os << "[";
	os << p.getName() << ", ";
	os << p.getBonusDamage() << ", ";
	os << p.getBonusHealth() << ", ";
	os << p.getBonusMana();
	os << "]";
	return os;
}
