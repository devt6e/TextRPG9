#pragma once
#include <iostream>
#include <string>

#include "BattleManager.h"
//#include "../../include/core/UI/UI2.h"

//임시
class Player;
class Monster;

enum class RoomType
{   
    Monster,
    NPC,
    Boss
};

class DungeonManager
{
private:
    BattleManager battleManager;

    int currentFloor;
    int currentRoom;
    static const int MapSize = 10; //방 사이즈 5*5 6이면 6*6임
    int dungeonMap[MapSize][MapSize];
    int playerLoc[2];
    int bossLoc[2];
    bool hasCheckpoint;
    int checkpointLoc[2];
    bool visitedMap[MapSize][MapSize];

public:
    DungeonManager();

    void StartDungeon(Player& player);

    

private:
    //던전 생성기
    void GenerateDungeonMap();
    // 목적지로 이동 가능?
    bool CanMoveTo(int destination) const;
    // 현재 위치 변경
    void MoveRoom(int destination);
    // 방의 종류
    RoomType DecideRoomType();
    // 방에 들어갔을 때
    void HandleRoom(Player& player, RoomType roomType);
    // 전투 결과
    void HandleBattleResult(BattleResult result);
    
    void DisplayDungeonMap() const;

};


