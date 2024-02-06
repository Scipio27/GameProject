#include "Resource.h"

Resource::Resource()
{
	rand() % 2 ? genPotion() : genParchemin();
}

vector<int> Resource::getCapacity() const
{
	return capacity;
}

vector<string> Resource::getType() const
{
	return type;
}

CItem* Resource::getSelected() const
{
	return selected;
}

string Resource::getName() const
{
	return selected->getName();
}

void Resource::changeCapacity(vector<int> c)
{
	capacity = c;
}

void Resource::genPotion()
{
	selected->changeName("potion");
	random_device rd;
	default_random_engine gen(rd());
	uniform_int_distribution<int> dist(0, type.size()-1);
	int r = dist(gen);
	string tmp;

	switch (r) {
	case 0:
		changeCapacity({ 5,5,5 });
		tmp = power[r];
		break;
	case 1:
		changeCapacity({ 20,20,20 });
		tmp = power[r];
		break;
	case 2:
		changeCapacity({ 50,50,50 });
		tmp = power[r];
		break;
	default:
		break;
	}

	r = dist(gen);

	switch (r) {
	case 0:
		selected->changeName(selected->getName() += type[r]);
		selected->changeName(selected->getName() += tmp);
		selected->changeBonusHealth(getCapacity()[r]);
		break;
	case 1:
		selected->changeName(selected->getName() += type[r]);
		selected->changeName(selected->getName() += tmp);
		selected->changeBonusMana(getCapacity()[r]);
		break;
	case 2:
		selected->changeName(selected->getName() += type[r]);
		selected->changeName(selected->getName() += tmp);
		selected->changeBonusDamage(getCapacity()[r]);
		break;
	default:
		break;
	}

	/*changeName(ci.getName());
	changeBonusDamage(ci.getBonusDamage());
	changeBonusMana(ci.getBonusMana());
	changeBonusHealth(ci.getBonusHealth());*/

}

void Resource::genParchemin()
{
	selected->changeName("parchemin");
	random_device rd;
	default_random_engine gen(rd());
	uniform_int_distribution<int> dist(0, type.size()-1);
	int rc = dist(gen);
	int r = dist(gen) + 1;

	switch (rc) {
	case 0:
		selected->changeName(selected->getName() += type[rc]);
		changeCapacity({ 10 * r * 2, 0, -2 * r * 2 });
		break;
	case 1:
		selected->changeName(selected->getName() += type[rc]);
		changeCapacity({ -2 * r * 2, 10 * r * 2, 0 });
		break;
	case 2:
		selected->changeName(selected->getName() += type[rc]);
		changeCapacity({ 0, -2 * r * 2, 10 * r * 2 });
		break;
	default:
		break;
	}

	r--;

	switch (r) {
	case 0:
		selected->changeName(selected->getName() += power[r]);
		break;
	case 1:
		selected->changeName(selected->getName() += power[r]);
		break;
	case 2:
		selected->changeName(selected->getName() += power[r]);
		break;
	default:
		break;
	}

	selected->changeBonusHealth(getCapacity()[0]);
	selected->changeBonusMana(getCapacity()[1]);
	selected->changeBonusDamage(getCapacity()[2]);
}
