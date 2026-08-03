#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

struct Player {
	int Hp{ 50 };
	int MaxHp{ 200 };
	int Power{ 50 };
	int TempAttackBuff{ 0 };

	void setHp(int newHp) { Hp = newHp; }
	void setMaxHp(int MH) { MaxHp = MH; }
	void setPower(int p) { Power = p; }

	int getHp() const { return Hp; }
	int getMaxHp() const { return MaxHp; }

	int getTempAttackBuff() const { return TempAttackBuff; }
	int getPower() const { return Power; }
	int getTotalPower() const { return Power + TempAttackBuff; }

	void ResetBuff() { TempAttackBuff = 0; }
};

class Item {
public:
	string Name, ItemDescription, ItemDropLocation;
	int Price = 0, ItemCount = 1, ItemMaxStack = 99, HealAmount = 0, BuffAmount = 0;

	Item(string Name, int Price, int ItemCount, int HealAmount, int BuffAmount);

	virtual ~Item() {}
	virtual bool UseItem(Player* player);
	virtual void ResetBuff(Player* player);

	void PrintInfo() const;
};

class HpPotion : public Item {
public:
	HpPotion();
	bool UseItem(Player* player) override;
};

class TempABPotion : public Item {
public:
	TempABPotion();
	bool UseItem(Player* player) override;
	void ResetBuff(Player* player) override;
};

class InventoryManager;

bool UseConsumableItem(Player* player, InventoryManager& invManager, size_t index);
bool UseRandomConsumableItem(Player* player, InventoryManager& invManager);
bool SelectAndUseConsumableItem(Player* player, InventoryManager& invManager);