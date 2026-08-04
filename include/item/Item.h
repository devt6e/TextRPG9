#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <random>

class Player;

// 아이템 부모 클래스
class Item {
public:
	std::string Name, ItemDescription, ItemDropLocation;
	int Price = 0, ItemCount = 1, ItemMaxStack = 99, HealAmount = 0, BuffAmount = 0, MpAmount = 0, DEFBuffAmount = 0;

	Item(std::string Name = "", int Price = 0, int ItemCount = 1, int HealAmount = 0, int BuffAmount = 0, int MpAmount = 0, int DEFBuffAmount = 0);

	virtual ~Item() {}
	virtual bool UseItem(Player* player);
	virtual void ResetBuff(Player* player);

	void PrintInfo() const;
};

class HpPotion : public Item {
public:
	HpPotion();
	bool UseItem(Player* player) override;
}; // HP포션

class MpPotion : public Item {
public:
	MpPotion();
	bool UseItem(Player* player) override;
}; // MP포션

class TempABPotion : public Item {
public:
	TempABPotion();
	bool UseItem(Player* player) override;
	void ResetBuff(Player* player) override;
}; // 공격력 임시 버프

class TempDEFPotion : public Item {
public:
	TempDEFPotion();
	bool UseItem(Player* player) override;
	void ResetBuff(Player* player) override;
}; // 방어력 임시 버프

class InventoryManager;

bool UseConsumableItem(Player* player, InventoryManager& invManager, size_t index);
bool UseRandomConsumableItem(Player* player, InventoryManager& invManager);
bool SelectAndUseConsumableItem(Player* player, InventoryManager& invManager);

// 1. 쿠키
class CookieCat : public Item {
public:
	CookieCat();
	bool UseItem(Player* player) override;
};

// 2. 젬 주머니
class ZemPouch : public Item {
public:
	ZemPouch();
	bool UseItem(Player* player) override;
};

// 3. 지각생의 알람시계
class AlarmClock : public Item {
public:
	AlarmClock();
	bool UseItem(Player* player) override;
};

// 4. 마이크
class Microphone : public Item {
public:
	Microphone();
	bool UseItem(Player* player) override;
};