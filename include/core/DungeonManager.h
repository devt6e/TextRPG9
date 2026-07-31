#pragma once
#include <iostream>
#include <string>

#include "BattleManager.h"
#include "../../include/core/UI/UI2.h"

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
    static const int MapSize = 5;
    int dungeonMap[MapSize][MapSize];
    int playerLoc[2];
    int bossLoc[2];



public:
    DungeonManager();

    void StartDungeon(Player& player, UI& ui);

    

private:
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
};


