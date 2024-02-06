#pragma once
#include "Perso.h"

enum typeRoom {
	Rest, Fight, Item
};
class Room {
private :
	char name;
	int difficulty;
	int posX;
	int posY;
	int posZ;
	bool isClear;
	bool isDiscovered;
	vector<string> roomMenu = { "Leave" };

	typeRoom room = typeRoom::Rest;
	vector<string> emplacement = { "à gauche", "au fond à gauche", "à droite", "au fond à droite", "droit devant", "au fond" };
	vector<string> props = {"un canapé", "une fontaine", "une bibliothèque", "des étagères", "un coffre", "une table"};
	vector<string> enemy = {"un squelette", "une araignée", "un serpent"};
	string place;
	string prop;
	string enemyType;

	

public:
	Room(int posX, int posY, int posZ);
	Room(int posX, int posY, int posZ, int difficulty);

	int getDifficulty();
	int getPosX();
	int getPosY();
	int getPosZ();
	char getName();
	bool getIsClear();
	bool getIsDiscovered();
	vector<string> getRoomMenu();

	void setIsClear(bool newState);
	void setIsDiscovered(bool newState);

	static int nbRoom[4];
	static int nbRoomMax[4];
	static bool isCreated;

	friend ostream& operator<<(ostream& os, Room const& r);

};