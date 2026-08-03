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
    int choice;
    while (player.GetHp() > 0 && monster.GetHp() > 0)
    {
        std::cout << "1. 공격\n"
            << "2. 아이템\n"
            << "3. 도망\n"
            << "선택 : \n";

        std::cin >> choice;
        switch (choice)
        {
        case 1:
            PlayerAttack(player, monster);
            break;

        case 2:
            std::cout << "아이템 기능 준비 중입니다.\n";
            break;

        case 3:
            if (TryEscape())
            {
                std::cout << "도망성공!!\n";
                return BattleResult::Escaped;
            }
            else
            {
                std::cout << "도망실패!!\n";
            }
            break;

        default:
            std::cout << "잘못된 입력입니다.\n";
            continue;
        }

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

    std::cout << player.GetName() << "의 공격! " << monster.GetName() 
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

    std::cout << monster.GetName() << "의 공격! " << player.GetName()
        << "에게 " << damage << "의 피해를 입혔습니다\n";
    std::cout << player.GetName() << "의 남은 HP: "
        << player.GetHp() << " / "
        << player.GetMaxHp() << std::endl;
}
bool BattleManager::TryEscape()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 99);
    int number = dist(gen);
    bool isEscape=false;
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

    