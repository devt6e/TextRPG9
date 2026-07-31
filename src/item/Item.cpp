#include "../../include/item/Item.h"
#include <iostream>
#include <string>
#include <algorithm>

// #include "Player.h"

using namespace std;

Item::Item(string Name, int Price, int Count)
	: Name(Name), Price(Price), Count(Count) {}

void Item::PrintInfo() const {
	cout << Name << "(" << Price << "G)" << endl;
}

bool HpPotion::UseItem(Player* player) {

	if (Count <= 0) {
		cout << Name << "의 수량이 부족함" << endl;
		return false;
	}

	Count--;

	player->setHp(min(player->getHp() + PotionHeal, player->getMaxHp()));

	cout << "* " << Name << " 사용! HP 회복: " << player->getHp()
		<< " (남은 수량: " << Count << "개)" << endl;

	return true;
}