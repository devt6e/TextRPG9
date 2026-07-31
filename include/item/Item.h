#pragma once
#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

//ÀÓ½Ã ÇÃ·¹ÀÌ¾î 
struct Player {
	int Hp{ 50 };
	int MaxHp{ 200 };
	int Power{ 50 };
	int TempAttackBuff{ 0 };

	void setHp(int newHp) { Hp = newHp; }
	void setMaxHp(int MH) { MaxHp = MH; }
	void setPower(int p) { Power = Power; }

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
	int Price, ItemCount, ItemMaxStack;

	Item(string Name, int Price, int ItemCount);

	virtual ~Item() {}
	virtual bool UseItem(Player* player) { return false; }
	virtual void ResetBuff(Player* player) {}

	void PrintInfo() const;
};

class HpPotion : public Item {
protected:
	int PotionHeal = 50;

public:

	HpPotion() : Item("HP Potion", 50, 1) {}

	bool UseItem(Player* player) override;
};

class  TempABPotion : public Item {
protected:
	int T_AttackBuff = 10;

public:
	TempABPotion() : Item("TempAttackBuff Potion", 100, 1) {}
	bool UseItem(Player* player) override;
	void ResetBuff(Player* player) override;
};
