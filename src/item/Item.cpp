#include <iostream>
#include <string>
#include <algorithm>
#include <random>

#include "item/Item.h"
#include "item/Inventory.h"
#include "character/Player.h"

//using namespace std;

Item::Item(std::string Name, int Price, int ItemCount, int HealAmount, int BuffAmount, int MpAmount, int DEFBuffAmount)
	: Name(Name), Price(Price), ItemCount(ItemCount), HealAmount(HealAmount), BuffAmount(BuffAmount), MpAmount(MpAmount), DEFBuffAmount(DEFBuffAmount) {}

void Item::PrintInfo() const {
	std::cout << Name << "(" << Price << "G)" << std::endl;
}

bool Item::UseItem(Player* player) {
	if (ItemCount <= 0) { //아이템 0개 이하인 경우 사용 불가
		std::cout << Name << "의 수량이 부족함" << std::endl;
		return false;
	}

	if (HealAmount > 0) { // HP포션 | 에너지 드링크
		player->SetHp(min(player->GetHp() + HealAmount, player->GetMaxHp()));
		std::cout << std::endl << "* " << Name << " 사용! HP 회복: " << player->GetHp()
			<< " (남은 수량: " << ItemCount - 1 << "개)" << std::endl;
		return true;
	}

	else if (MpAmount > 0) { // MP포션 | 아메리카노
		player->SetMp(min(player->GetMp() + MpAmount, player->GetMaxMp()));
		std::cout << std::endl << "* " << Name << " 사용! MP 회복: " << player->GetMp()
			<< " (남은 수량: " << ItemCount - 1 << "개)" << std::endl;
		return true;
	}


	else if (BuffAmount > 0) { //공격력 임시버프 | 쿠키의 장난감
		player->TempAttackBuff += BuffAmount;
		std::cout << std::endl << "* " << Name << " 사용! 공격력 + " << BuffAmount << std::endl
			<< "현재 공격력: " << player->GetTotalPower()
			<< " (남은 수량: " << ItemCount - 1 << "개)" << std::endl;
		return true;
	}

	else if (DEFBuffAmount > 0) { //방어력 임시버프 | 온열 안대
		player->TempDEFBuff += DEFBuffAmount;
		std::cout << std::endl << "* " << Name << " 사용! 방어력 + " << DEFBuffAmount << std::endl
			<< "현재 방어력: " << player->GetTotalDEF()
			<< " (남은 수량: " << ItemCount - 1 << "개)" << std::endl;
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
		std::cout << "번호를 다시 입력하세요" << std::endl;
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
		std::cout << "* 가방이 비어있습니다." << std::endl;
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

	if (consumables.empty()) {
		std::cout << "* 가방이 비어있습니다." << std::endl;
		return false;
	}

	std::cout << std::endl;
	std::cout << "아이템 번호 입력" << std::endl;
	std::cout << std::endl;

	for (size_t i = 0; i < consumables.size(); ++i) {
		std::cout << i + 1 << ". " << consumables[i].Name
			<< " (수량: " << consumables[i].ItemCount << "개)" << std::endl;
	}
	std::cout << "0. 취소 (사용하지 않음)" << std::endl;
	std::cout << "==========================================" << std::endl;
	std::cout << "선택할 번호 입력 >> ";

	int choice{ 0 };

	if (!(std::cin >> choice)) {
		std::cin.clear();
		std::cin.ignore();
		std::cout << "숫자를 다시 입력하세요" << std::endl;
		return false;
	}

	if (choice == 0) {
		std::cout << "아이템 사용 취소" << std::endl;
		return false;
	}

	size_t selectedIndex = static_cast<size_t>(choice - 1);

	return UseConsumableItem(player, invManager, selectedIndex);
}
CookieCat::CookieCat()
	: Item("쿠키", 0, 1)
{
	ItemDescription = "쿠키 납치범에게서 되찾은 쿠키입니다.";
	ItemDropLocation = "쿠키 납치범";
}

bool CookieCat::UseItem(Player*)
{
	return false;
}

ZemPouch::ZemPouch()
	: Item("ZEM 주머니", 0, 1)
{
	ItemDescription = "ZEM 탈취범에게서 되찾은 주머니입니다.";
	ItemDropLocation = "ZEM 탈취범";
}

bool ZemPouch::UseItem(Player*)
{
	return false;
}

AlarmClock::AlarmClock()
	: Item("지각생의 알람시계", 0, 1)
{
	ItemDescription = "만년 지각생이 떨구고 간 알람시계입니다.";
	ItemDropLocation = "만년 지각생";
}

bool AlarmClock::UseItem(Player*)
{
	return false;
}

Microphone::Microphone()
	: Item("마이크", 0, 1)
{
	ItemDescription = "모닝콜 수강생이 남기고 간 마이크입니다.";
	ItemDropLocation = "모닝콜 수강생";
}

bool Microphone::UseItem(Player*)
{
	return false;
}