#include "../../include/core/DungeonManager.h"
#include "../../include/core/UI/UI2.h"

#include <iostream>
#include <string>
#include <random>

// 1. 랜덤 생성기 준비
std::random_device rd;
std::mt19937 gen(rd());

// 2. 범위 설정: 1부터 10까지
std::uniform_int_distribution<int> dist(1, 10);

// 3. 랜덤 숫자 뽑기
int number = dist(gen);

//std::cout << number << '\n';


DungeonManager::DungeonManager()
    : currentFloor(1),
    currentRoom(0),
    dungeonMap{},
    playerLoc{},
    bossLoc{}
{
}

void DungeonManager::GenerateDungeonMap()
{
    //i= 가로, j=세로
    for (int i = 0; i < MapSize; i++)
    {
        for (int j = 0 ;j < MapSize; j++)
        {
            dungeonMap[i][j] = 0;
        }
    }
}

void DungeonManager::StartDungeon(Player& player, UI& ui)
{
   // ui.Maps1();//일단 대기
}

bool DungeonManager::CanMoveTo(int destination) const    // 목적지로 이동 가능?
{
    
}
void DungeonManager::MoveRoom(int destination)    // 현재 위치 변경
{

}

void DungeonManager::HandleRoom(Player& player, RoomType roomType)    // 방에 들어갔을 때
{

}
void DungeonManager::HandleBattleResult(BattleResult result)    // 전투 결과
{

}

