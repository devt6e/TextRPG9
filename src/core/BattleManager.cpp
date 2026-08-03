#include <iostream>
#include <string>
#include <random>

#include "core/BattleManager.h"
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
    // 임시
    return BattleResult::Victory;
}

