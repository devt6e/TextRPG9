#include <iostream>
#include <string>
#include <random>
#include <limits>

#include "core/BattleManager.h"
#include "core/UIManager.h"

#include "character/Player.h"
#include "character/Monster.h"

#include "item/Item.h"
#include "item/Inventory.h"



/*
// 1. 랜덤 생성기 준비
std::random_device rd;
std::mt19937 gen(rd());

// 2. 범위 설정: 1부터 10까지
std::uniform_int_distribution<int> dist(1, 10);

// 3. 랜덤 숫자 뽑기
int number = dist(gen);

std::cout << number << '\n';
*/


BattleResult BattleManager::StartBattle(
	Player& player,
	Monster& monster,
	UI& ui,
	InventoryManager& inventoryManager)
{
	int choice;
	while (player.GetHp() > 0 && monster.GetHp() > 0)
	{
		ui.PrintSelection({
			"공격",
			"아이템",
			"도망"
			});

		int choice = ui.InputSelection("선택: ");

		switch (choice)
		{
		case 1:
			PlayerAttack(player, monster, ui);
			break;

		case 2:
			if (!UseItem(player, inventoryManager))
			{
				continue;
			}
			break;

		case 0:
			if (TryEscape())
			{
				ui.PrintLog("도망 성공!!");
				return BattleResult::Escaped;
			}
			else
			{
				ui.PrintLog("도망 실패!!");
			}
			break;

		default:
			ui.PrintLog("0~2 중에서 선택해주세요.");
			continue;
		}

		if (monster.GetHp() <= 0) {
			monster.SpeakDefeat(); //패배 대사
			break;
		}
		MonsterAttack(monster, player, ui);
		if (player.GetHp() <= 0)
			break;

	}
	if (player.GetHp() <= 0)
	{
		return BattleResult::Defeat;
	}

	//드랍아이템 인벤토리에
	Item* droppedItem = monster.DropItem();

	if (droppedItem != nullptr)
	{
		inventoryManager.AddMaterial(*droppedItem); // 재료 가방에 추가
		delete droppedItem;
	}

	return BattleResult::Victory;
}

void BattleManager::PlayerAttack(Player& player, Monster& monster, UI& ui)
{
	player.Attack();
	int damage = player.GetTotalPower() - monster.GetDefence();
	if (damage < 1)
	{
		damage = 1;
	}
	monster.SetHp(monster.GetHp() - damage);

	ui.PrintLog(
		player.GetName() + "의 공격! " +
		monster.GetName() + "에게 " +
		std::to_string(damage) +
		"의 피해를 입혔습니다.");
	ui.PrintLog(
		monster.GetName() + "의 남은 HP: " +
		std::to_string(monster.GetHp()) + " / " +
		std::to_string(monster.GetMaxHp()));
}
void BattleManager::MonsterAttack(Monster& monster, Player& player, UI& ui)
{
	monster.Attack();
	int damage = monster.GetPower() - player.GetTotalDEF();
	if (damage < 1)
	{
		damage = 1;
	}
	player.SetHp(player.GetHp() - damage);

	ui.PrintLog(
		monster.GetName() + "의 공격! " +
		player.GetName() + "에게 " +
		std::to_string(damage) +
		"의 피해를 입혔습니다.");
	ui.PrintLog(
		player.GetName() + "의 남은 HP: " +
		std::to_string(player.GetHp()) + " / " +
		std::to_string(player.GetMaxHp()));
}
bool BattleManager::TryEscape()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 99);
	int number = dist(gen);
	bool isEscape = false;
	if (number < 50)
	{
		isEscape = true;
	}
	else
	{
		isEscape = false;
	}
	return isEscape;
}
bool BattleManager::UseItem(
	Player& player,
	InventoryManager& inventoryManager)
{
	return SelectAndUseConsumableItem(&player, inventoryManager);
}