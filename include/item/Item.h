#pragma once
#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

//임시 플레이어 
class Player;


class Item {

protected:
	string Name;
	int Price, Count;

public:

	Item(string Name, int Price, int Count);

	virtual ~Item() {}
	virtual bool UseItem(Player* player) = 0;
	void PrintInfo() const;
};

class HpPotion : public Item {
protected:
	int PotionHeal = 50;

public:

	HpPotion() : Item("HP 포션", 50, 1) {}

	bool UseItem(Player* player) override;
};
