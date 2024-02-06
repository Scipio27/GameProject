#include "Room.h"
#include <random>

int Room::nbRoom[] = {0,0,0,0};
int Room::nbRoomMax[] = {5,2,5,3};

bool Room::isCreated = false;

Room::Room(int posX, int posY, int posZ) {
	
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> cell(0, 5);
	uniform_int_distribution<> cell2(0, 2);
	uniform_int_distribution<> cell3(0, 3);
	
	this->difficulty = cell3(gen);
	this->posX = posX;
	this->posY = posY;

	switch (difficulty) {
	case 0:
		if (nbRoom[1] < nbRoomMax[1]) {
			this->name = 'R';
			Room::nbRoom[1]++;
			roomMenu.push_back("Rest");
			Room::isCreated = true;
		}
		else {
			Room::isCreated = false;
		}
		break;
	case 1:
		if (nbRoom[2] < nbRoomMax[2]) {
			this->name = 'I';
			place = emplacement[cell(gen)];
			prop = props[cell(gen)];
			Room::nbRoom[2]++;
			Room::isCreated = true;
			roomMenu.push_back("Search");
		}
		else {
			Room::isCreated = false;
		}
		break;
	case 2:
		if (nbRoom[0] < nbRoomMax[0]) {
			this->name = 'F';
			place = emplacement[cell(gen)];
			enemyType = enemy[cell2(gen)];
			Room::nbRoom[0]++;
			Room::isCreated = true;
			roomMenu.push_back("Fight !");
		}
		else {
			Room::isCreated = false;
		}
		break;
	case 3:
		if (nbRoom[3] < nbRoomMax[3]) {
			this->name = 'E';
			Room::nbRoom[3]++;
			Room::isCreated = true;
		}
		else {
			Room::isCreated = false;
		}
		break;
	default:
		break;
	}
}

Room::Room(int posX, int posY, int posZ, int difficulty)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> cell(0, 5);
	uniform_int_distribution<> cell2(0, 2);

	this->difficulty = difficulty;
	this->posX = posX;
	this->posY = posY;
	this->isDiscovered = false;

	switch (difficulty) {
	case 0:
		this->name = 'R';
		break;
	case 1:
		this->name = 'I';
		place = emplacement[cell(gen)];
		prop = props[cell(gen)];
		break;
	case 2:
		this->name = 'F';
		place = emplacement[cell(gen)];
		enemyType = enemy[cell2(gen)];
		break;
	case 3:
		this->name = 'E';
		break;
	case 4:
		this->name = 'B';
		roomMenu.push_back("Boss Fight");
		break;
	case 5:
		this->name = ' ';
		this->isDiscovered = true;
		break;
	case 6:
		this->name = 'S';
		this->isDiscovered = true;
	default:
		cout << "default";
		break;
	}
}

int Room::getDifficulty()
{
	return difficulty;
}

int Room::getPosX()
{
	return posX;
}

int Room::getPosY()
{
	return posY;
}

char Room::getName()
{
	return name;
}

int Room::getPosZ()
{
	return posZ;
}

bool Room::getIsClear()
{
	return isClear;
}

bool Room::getIsDiscovered()
{
	return isDiscovered;
}

void Room::setIsClear(bool newState)
{
	isClear = newState;
}

vector<string> Room::getRoomMenu()
{
	return roomMenu;
}

void Room::setIsDiscovered(bool newState)
{
	isDiscovered = newState;
}

ostream& operator<<(ostream& os, Room const& r)
{
	switch (r.difficulty) {
	case 0 :
		os << "Vous entrez dans une salle dans laquelle se trouve un canapé " << endl;
		break;
	case 1 :
		os << "Vous entrez dans une salle " << r.place << " se trouve " << r.prop << endl;
		break;
	case 2 :
		os << "Vous entrez dans une salle " << r.place << " se trouve " << r.enemyType << endl;
		break;
	case 3 :
		os << "Vous entrez dans une salle complètement vide " << endl;
		break;
	case 4 :
		os << "Vous entrez dans la salle du boss" << endl;
		break;
	case 5:
		os << "Salle inexistante !" << endl;
		break;
	case 6:
		os << "Vous êtes dans la salle de départ " << endl;
		break;
	}
	return os;
	
}
