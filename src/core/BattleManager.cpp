#include <iostream>
#include <string>
#include <random>

#include "core/BattleManager.h"
#include "character/Player.h"
#include "character/Monster.h"
//#include "../../include/core/UI/UI2.h"

// 임시
// #include "Player.h"
// #include "Monster.h"


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
    Monster& monster)
{
    while (player.GetHp() > 0 && monster.GetHp() > 0)
    {
        PlayerAttack(player, monster);
        if (monster.GetHp() <= 0)
            break;
        MonsterAttack(monster, player);
        if (player.GetHp() <= 0)
            break;

    }
    if (player.GetHp() <= 0)
    {
        return BattleResult::Defeat;
    }

    return BattleResult::Victory;
}

void BattleManager::PlayerAttack(Player& player, Monster& monster)
{
    player.Attack();
    int damage = player.GetTotalPower() - monster.GetDefence();
    if (damage < 1)
    {
        damage = 1;
    }
    monster.SetHp(monster.GetHp() - damage);

    std::cout << player.GetName() << "가 " << monster.GetName() 
        << "에게 " << damage << "의 피해를 입혔습니다\n";
    std::cout << monster.GetName() << "의 남은 HP: "
        << monster.GetHp() << " / " 
        << monster.GetMaxHp() << std::endl;
}
void BattleManager::MonsterAttack(Monster& monster, Player& player)
{
    monster.Attack();
    int damage = monster.GetPower() - player.GetDefence();
    if (damage < 1)
    {
        damage = 1;
    }
    player.SetHp(player.GetHp() - damage);

    std::cout << monster.GetName() << "가 " << player.GetName()
        << "에게 " << damage << "의 피해를 입혔습니다\n";
    std::cout << player.GetName() << "의 남은 HP: "
        << player.GetHp() << " / "
        << player.GetMaxHp() << std::endl;
}
