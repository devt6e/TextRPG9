#include <iostream>
#include <string>
#include <algorithm>
#include <random>

#include "item/Item.h"
#include "item/Inventory.h"
#include "character/Player.h"
#include "core/UIManager.h"

//using namespace std;

Item::Item(std::string Name, int Price, int ItemCount, int HealAmount, int BuffAmount, int MpAmount, int DEFBuffAmount)
	: Name(Name), Price(Price), ItemCount(ItemCount), HealAmount(HealAmount), BuffAmount(BuffAmount), MpAmount(MpAmount), DEFBuffAmount(DEFBuffAmount) {}

void Item::PrintInfo() const {
	std::cout << Name << "(" << Price << "G)" << std::endl;
}

bool Item::UseItem(Player* player) {
	UI ui;
	if (ItemCount <= 0) { //아이템 0개 이하인 경우 사용 불가
		ui.PrintLog(Name + "의 수량이 부족합니다.");
		return false;
	}

	if (HealAmount > 0) { // HP포션 | 에너지 드링크
		player->SetHp(min(player->GetHp() + HealAmount, player->GetMaxHp()));
		ui.PrintLog("* " + Name + " 사용! HP 회복: " +
			std::to_string(player->GetHp()) + " (남은 수량: " +
			std::to_string(ItemCount - 1) + "개)");
		return true;
	}

	else if (MpAmount > 0) { // MP포션 | 아메리카노
		player->SetMp(min(player->GetMp() + MpAmount, player->GetMaxMp()));
		ui.PrintLog("* " + Name + " 사용! MP 회복: " +
			std::to_string(player->GetMp()) + " (남은 수량: " +
			std::to_string(ItemCount - 1) + "개)");
		return true;
	}


	else if (BuffAmount > 0) { //공격력 임시버프 | 쿠키의 장난감
		player->TempAttackBuff += BuffAmount;
		ui.PrintLog("* " + Name + " 사용! 공격력 + " +
			std::to_string(BuffAmount) + " / 현재 공격력: " +
			std::to_string(player->GetTotalPower()) + " (남은 수량: " +
			std::to_string(ItemCount - 1) + "개)");
		return true;
	}

	else if (DEFBuffAmount > 0) { //방어력 임시버프 | 온열 안대
		player->TempDEFBuff += DEFBuffAmount;
		ui.PrintLog("* " + Name + " 사용! 방어력 + " +
			std::to_string(DEFBuffAmount) + " / 현재 방어력: " +
			std::to_string(player->GetTotalDEF()) + " (남은 수량: " +
			std::to_string(ItemCount - 1) + "개)");
		return true;
	}

	return false;
}

void Item::ResetBuff(Player* player) { //임시 버프 초기화 함수
	if (player->GetTempAttackBuff() > 0) {
		player->TempAttackBuff = 0; //버프 수치를 0으로 초기화
		std::cout << "버프 해제" << std::endl;
	}
}

HpPotion::HpPotion()
	: Item("에너지 드링크", 5, 1, 50, 0, 0, 0) {}

bool HpPotion::UseItem(Player* player) {
	return Item::UseItem(player);
}

MpPotion::MpPotion()
	: Item("아이스 아메리카노", 5, 1, 0, 0, 20, 0) {}

bool MpPotion::UseItem(Player* player) {
	return Item::UseItem(player);
}

TempABPotion::TempABPotion()
	: Item("쿠키의 장난감", 5, 1, 0, 10, 0, 0) {}

bool TempABPotion::UseItem(Player* player) {
	return Item::UseItem(player);
}

void TempABPotion::ResetBuff(Player* player) {
	Item::ResetBuff(player);
}

TempDEFPotion::TempDEFPotion()
	: Item("온열안대", 5, 1, 0, 0, 0, 10) {}

bool TempDEFPotion::UseItem(Player* player) {
	return Item::UseItem(player);
}

void TempDEFPotion::ResetBuff(Player* player) {
	Item::ResetBuff(player);
}




//인덱스의 아이템을 사용
bool UseConsumableItem(Player* player, InventoryManager& invManager, size_t index)
{
	std::vector<Item>& consumables = invManager.GetConsumableBag().GetAllItems();

	if (index >= consumables.size())
	{
		UI ui;
		ui.PrintLog("번호를 다시 입력하세요.");
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


//랜덤 아이템 사용
bool UseRandomConsumableItem(Player* player, InventoryManager& invManager)
{
	std::vector<Item>& consumables = invManager.GetConsumableBag().GetAllItems();

	if (consumables.empty())
	{
		UI ui;
		ui.PrintLog("가방이 비었습니다.");
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

//아이템 지정 사용 시 플레이어에게 번호를 입력받아 사용하는 함수
bool SelectAndUseConsumableItem(Player* player, InventoryManager& invManager) {
	std::vector<Item>& consumables = invManager.GetConsumableBag().GetAllItems();
	UI ui;

	if (consumables.empty()) {
		ui.PrintLog("가방이 비었습니다.");
		return false;
	}

	std::vector<std::string> itemMenu;
	for (size_t i = 0; i < consumables.size(); ++i) {
		itemMenu.push_back(
			consumables[i].Name + " (수량: " +
			std::to_string(consumables[i].ItemCount) + "개)");
	}
	itemMenu.push_back("취소 (사용하지 않음)");
	ui.PrintSelection(itemMenu);

	int choice = ui.InputSelection("선택: ");

	if (choice == 0) {
		ui.PrintLog("아이템 사용을 취소했습니다.");
		return false;
	}

	if (choice < 0 || choice > static_cast<int>(consumables.size())) {
		ui.PrintLog("번호를 다시 입력하세요.");
		return false;
	}

	size_t selectedIndex = static_cast<size_t>(choice - 1);

	return UseConsumableItem(player, invManager, selectedIndex);
}
CookieCat::CookieCat()
	: Item("쿠키", -2147483648, 1)
{
	ItemDescription = "쿠키 납치범에게서 되찾은 쿠키입니다.";
	ItemDropLocation = "쿠키 납치범";
}

bool CookieCat::UseItem(Player*)
{
	return false;
}

ZemPouch::ZemPouch()
	: Item("ZEM 주머니", 100, 1)
{
	ItemDescription = "ZEM 탈취범에게서 되찾은 주머니입니다.";
	ItemDropLocation = "ZEM 탈취범";
}

bool ZemPouch::UseItem(Player*)
{
	return false;
}

AlarmClock::AlarmClock()
	: Item("지각생의 알람시계", 10, 1)
{
	ItemDescription = "만년 지각생이 흘리고 간 알람시계입니다.";
	ItemDropLocation = "만년 지각생";
}

bool AlarmClock::UseItem(Player*)
{
	return false;
}

Microphone::Microphone()
	: Item("마이크", 15, 1)
{
	ItemDescription = "모닝콜 수강생이 남기고 간 마이크입니다.";
	ItemDropLocation = "모닝콜 수강생";
}

bool Microphone::UseItem(Player*)
{
	return false;
}
