#include <iostream>
#include <string>
#include <algorithm>
#include <random>

#include "item/Item.h"
#include "item/Inventory.h"

// #include "Player.h"

using namespace std;

Item::Item(string Name, int Price, int ItemCount, int HealAmount, int BuffAmount)
	: Name(Name), Price(Price), ItemCount(ItemCount), HealAmount(HealAmount), BuffAmount(BuffAmount) {}

void Item::PrintInfo() const {
	cout << Name << "(" << Price << "G)" << endl;
}

bool Item::UseItem(Player* player) {
	if (ItemCount <= 0) {
		cout << Name << "의 수량이 부족함" << endl;
		return false;
	}

	if (HealAmount > 0) {
		player->setHp(min(player->getHp() + HealAmount, player->getMaxHp()));
		cout << "* " << Name << " 사용! HP 회복: " << player->getHp()
			<< " (남은 수량: " << ItemCount - 1 << "개)" << endl;
		return true;
	}
	else if (BuffAmount > 0) {
		player->TempAttackBuff += BuffAmount;
		cout << "* " << Name << " 사용! 공격력 + " << BuffAmount << endl
			<< "현재 공격력: " << player->getTotalPower()
			<< " (남은 수량: " << ItemCount - 1 << "개)" << endl;
		return true;
	}

	return false;
}

void Item::ResetBuff(Player* player) {
	if (player->getTempAttackBuff() > 0) {
		player->TempAttackBuff = 0;
		cout << "버프 해제" << endl;
	}
}

HpPotion::HpPotion()
	: Item("HP 회복 포션", 50, 1, 50, 0) {}

bool HpPotion::UseItem(Player* player) {
	return Item::UseItem(player);
}

TempABPotion::TempABPotion()
	: Item("공격력 임시 버프", 100, 1, 0, 10) {}

bool TempABPotion::UseItem(Player* player) {
	return Item::UseItem(player);
}

void TempABPotion::ResetBuff(Player* player) {
	Item::ResetBuff(player);
}

bool UseConsumableItem(Player* player, InventoryManager& invManager, size_t index)
{
	vector<Item>& consumables = invManager.GetConsumableBag().GetAllItems();

	if (index >= consumables.size())
	{
		cout << "번호를 다시 입력하세요" << endl;
		return false;
	}

	Item& selectedItem = consumables[index];

	bool used = selectedItem.UseItem(player);

	if (used)
	{
		invManager.GetConsumableBag().RemoveItem(static_cast<int>(index) + 1, 1);
		return true;
	}

	return false;
}

bool UseRandomConsumableItem(Player* player, InventoryManager& invManager)
{
	vector<Item>& consumables = invManager.GetConsumableBag().GetAllItems();

	if (consumables.empty())
	{
		cout << "* 가방이 비어있습니다." << endl;
		return false;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<size_t> dist(0, consumables.size() - 1);

	size_t randomIndex = dist(gen);

	Item& selectedItem = consumables[randomIndex];

	bool used = selectedItem.UseItem(player);

	if (used)
	{
		invManager.GetConsumableBag().RemoveItem(static_cast<int>(randomIndex) + 1, 1);
		return true;
	}

	return false;
}

bool SelectAndUseConsumableItem(Player* player, InventoryManager& invManager) {
	vector<Item>& consumables = invManager.GetConsumableBag().GetAllItems();

	if (consumables.empty()) {
		cout << "* 가방이 비어있습니다." << endl;
		return false;
	}

	cout << endl;
	cout << "아이템 번호 입력" << endl;
	cout << endl;

	for (size_t i = 0; i < consumables.size(); ++i) {
		cout << i + 1 << ". " << consumables[i].Name
			<< " (수량: " << consumables[i].ItemCount << "개)" << endl;
	}
	cout << "0. 취소 (사용하지 않음)" << endl;
	cout << "==========================================" << endl;
	cout << "선택할 번호 입력 >> ";

	int choice{ 0 };

	if (!(cin >> choice)) {
		cin.clear();
		cin.ignore();
		cout << "숫자를 다시 입력하세요" << endl;
		return false;
	}

	if (choice == 0) {
		cout << "아이템 사용 취소" << endl;
		return false;
	}

	size_t selectedIndex = static_cast<size_t>(choice - 1);

	return UseConsumableItem(player, invManager, selectedIndex);
}