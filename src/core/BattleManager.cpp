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
	InventoryManager& inventoryManager,
	bool canEscape)
{
	int choice;
	ui.PrintStatus(&player); // ysg: 전투 시작 시 현재 플레이어 스탯 표시
	while (player.GetHp() > 0 && monster.GetHp() > 0)
	{
		if (canEscape)
		{
			ui.PrintSelection({ "공격", "스킬", "아이템", "도망" });
		}
		else
		{
			ui.PrintSelection({ "공격", "스킬", "아이템" }); // ysg: 최종 보스전에서는 도망 선택지 숨김
		}

		int choice = ui.InputSelection("선택: ");

		switch (choice)
		{
		case 1:
			PlayerAttack(player, monster, ui);
			break;

		case 2:
			if (!PlayerSkill(player, monster, ui))
			{
				continue;
			}
			break;

		case 3:
			if (!UseItem(player, inventoryManager))
			{
				continue;
			}
			ui.PrintStatus(&player); // ysg: 회복/버프 아이템 사용 결과를 즉시 스탯창에 반영
			ui.WaitForAnyKey("계속하려면 아무 키나 입력하세요: "); // ysg: 아이템 사용 결과를 확인한 뒤 몬스터 턴 진행
			break;

		case 4:
			if (!canEscape)
			{
				ui.PrintLog("최종 보스전에서는 도망칠 수 없습니다.");
				continue;
			}
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
			ui.PrintLog(canEscape
				? "1~4 중에서 선택해주세요."
				: "1~3 중에서 선택해주세요.");
			continue;
		}

		if (monster.GetHp() <= 0) {
			monster.SpeakDefeat(); //패배 대사
			break;
		}
		MonsterAttack(monster, player, ui);
		if (player.GetHp() <= 0)
			break;
		ui.PrintStatus(&player); //kth: 전투 중 STAT UI 업데이트
	}
	if (player.GetHp() <= 0)
	{
		return BattleResult::Defeat;
	}

	//드랍아이템 인벤토리에
	Item* droppedItem = monster.DropItem();

	if (droppedItem != nullptr)
	{
		ui.PrintItemArt(droppedItem->Name); // ysg: 몬스터 드롭 아이템을 획득하는 순간 아스키 아트 출력
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
bool BattleManager::PlayerSkill(Player& player, Monster& monster, UI& ui)
{
	constexpr int skillMpCost = 30;
	if (player.GetMp() < skillMpCost)
	{
		ui.PrintLog(
			"마나가 부족하여 스킬을 사용할 수 없습니다! (현재 MP: " +
			std::to_string(player.GetMp()) + " / " +
			std::to_string(player.GetMaxMp()) + ")");
		return false; // ysg: MP 부족 시 몬스터에게 턴을 넘기지 않고 다시 선택
	}

	int damage = player.Skill();
	if (damage <= 0)
	{
		return false;
	}

	monster.SetHp(monster.GetHp() - damage);
	ui.PrintStatus(&player); // ysg: 스킬 사용 직후 소모된 MP를 스탯창에 반영
	ui.PrintLog(
		monster.GetName() + "의 남은 HP: " +
		std::to_string(monster.GetHp()) + " / " +
		std::to_string(monster.GetMaxHp()));

	return true;
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
	ui.PrintStatus(&player); // ysg: 몬스터에게 피해를 받은 직후 HP를 전투 중 스탯창에 갱신

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
