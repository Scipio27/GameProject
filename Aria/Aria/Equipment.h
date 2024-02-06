#pragma once
#include "CItem.h"
#include "Room.h"
#include <time.h>
#include <random>

class Equipment : public CItem
{
private:
	vector<CItem*> arme = { new CItem("épée",20,0,0), new CItem("lance",10,0,0), new CItem("masse d'arme",30,0,0), new CItem("dague",5,0,0), new CItem("baton magique",2,0,10), new CItem("hache",25,0,0) };
	vector<CItem*> equipement = { new CItem("botte",0,10,5), new CItem("armure", 0,30,0), new CItem("casque",0,10,0), new CItem("cape", 0,5,15), new CItem("gants",0,10,5), new CItem("amulette", 15,10,25), new CItem("anneau",10,10,30), new CItem("bouclier",10,40,0) };
	CItem* selected = new CItem("", 0, 0, 0);

public:
	Equipment();
	CItem* chooseArme() const;
	CItem* getSelected() const;
	vector<CItem*> getArme() const;
	vector<CItem*> getEquipement() const;
	CItem* chooseEquipement();

	void changeArme(CItem* a);
	void changeSelected(CItem* s, int difficulty);
	void changeEquipement(CItem* e, int difficulty);
};

