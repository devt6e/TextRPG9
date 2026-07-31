#include "../../include/core/DungeonManager.h"
#include "../../include/core/UI/UI2.h"

#include <iostream>
#include <string>
#include <random>

/*// 1. 랜덤 생성기 준비
std::random_device rd;
std::mt19937 gen(rd());

// 2. 범위 설정: 1부터 10까지
std::uniform_int_distribution<int> dist(0, 4);

// 3. 랜덤 숫자 뽑기
int number = dist(gen);

std::cout << number << '\n';*/




DungeonManager::DungeonManager()
    : currentFloor(1),
    currentRoom(0),
    dungeonMap{},
    playerLoc{},
    bossLoc{}
{
    GenerateDungeonMap();

}

void DungeonManager::GenerateDungeonMap()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> edgeDist(0, 3);
    std::uniform_int_distribution<int> positionDist(0, MapSize - 1);
    int edge = edgeDist(gen);
    int position = positionDist(gen);
    int bossPosition = positionDist(gen);
    // 랜덤최신 버전?이라고함 ran()은 구버전이라고함 무튼 이게 더 좋은거같음

    //i= 가로, j=세로
    for (int i = 0; i < MapSize; i++)
    {
        for (int j = 0 ;j < MapSize; j++)
        {
            dungeonMap[i][j] = 0;
        }
    }

   /*   
   edge 0 → player : 랜덤, 0   
   edge 1 → player : 랜덤, 4
   edge 2 → player : 0, 랜덤
   edge 3 → player : 4, 랜덤
    */
   // 플레이어와 보스 좌표 결정

    switch (edge)
    {
    case 0:
        playerLoc[0] = position;
        playerLoc[1] = 0;
        
        bossLoc[0] = bossPosition;
        bossLoc[1] = MapSize - 1;

        break;

    case 1:
        playerLoc[0] = position;
        playerLoc[1] = MapSize - 1;

        bossLoc[0] = bossPosition;
        bossLoc[1] = 0;
        break;

    case 2:
        playerLoc[0] = 0;
        playerLoc[1] = position;

        bossLoc[0] = MapSize - 1;
        bossLoc[1] = bossPosition;
        break;

    case 3:
        playerLoc[0] = MapSize - 1;
        playerLoc[1] = position;

        bossLoc[0] = 0;
        bossLoc[1] = bossPosition;
        break;
    }
    
    // 좌표가 모두 결정된 다음 맵에 표시
    /*  0 = 이동 불가
        1 = 이동 가능한 길
        2 = 보스방*/
    dungeonMap[playerLoc[0]][playerLoc[1]] = 1;
    dungeonMap[bossLoc[0]][bossLoc[1]] = 2;

    std::cout << "edge: " << edge << '\n';
    std::cout << "position: " << position << '\n';
    std::cout << "player: "
        << playerLoc[0] << ", "
        << playerLoc[1] << '\n';
    std::cout << "boss: "
        << bossLoc[0] << ", "
        << bossLoc[1] << '\n';
}

void DungeonManager::StartDungeon(Player& player, UI& ui)
{
   // ui.Maps1();//일단 대기
}

/*bool DungeonManager::CanMoveTo(int destination) const    // 목적지로 이동 가능?
{
    
}*/
void DungeonManager::MoveRoom(int destination)    // 현재 위치 변경
{

}

void DungeonManager::HandleRoom(Player& player, RoomType roomType)    // 방에 들어갔을 때
{

}
void DungeonManager::HandleBattleResult(BattleResult result)    // 전투 결과
{

}

