#include "../../include/item/Item.h"
#include <iostream>
#include <string>
#include <algorithm>

// #include "Player.h"

using namespace std;

Item::Item(string Name, int Price, int ItemCount)
	: Name(Name), Price(Price), ItemCount(ItemCount) {}

void Item::PrintInfo() const {
	cout << Name << "(" << Price << "G)" << endl;
}

bool HpPotion::UseItem(Player* player) {

	if (ItemCount <= 0) {
		cout << Name << "의 수량이 부족함" << endl;
		return false;
	}

	ItemCount--;

	player->setHp(min(player->getHp() + PotionHeal, player->getMaxHp()));

	cout << "* " << Name << " 사용! HP 회복: " << player->getHp()
		<< " (남은 수량: " << ItemCount << "개)" << endl;

	return true;
}

bool TempABPotion::UseItem(Player* player) {

	if (ItemCount <= 0) {
		cout << Name << "의 수량이 부족함" << endl;
		return false;
	}

	ItemCount--;

	player->TempAttackBuff += T_AttackBuff;

	cout << "* " << Name << " 사용! 공격력 + " << T_AttackBuff << endl << "현재 공격력: " << player->getTotalPower() << " (남은 수량: " << ItemCount << "개)" << endl;

	return true;
}

void TempABPotion::ResetBuff(Player* player) {
	if (player->getTempAttackBuff() > 0) {
		player->TempAttackBuff = 0;

		cout << "버프 해제" << endl;
	}
}