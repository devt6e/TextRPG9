#pragma once
#include <iostream>
#include <string>

#include "BattleManager.h"
#include "core/UIManager.h"

//임시
class Player;
class Monster;
class UI;
class InventoryManager;

enum class RoomType
{   //
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
    //static const int MapSize = 5; //방 사이즈 5*5 6이면 6*6임
    static const int MapHeight = 5;
    static const int MapWidth = 8;
    int dungeonMap[MapWidth][MapHeight];
    int playerLoc[2];
    int bossLoc[2];
    bool hasCheckpoint;
    int checkpointLoc[2];
    bool visitedMap[MapWidth][MapHeight];
    bool hasNpcAppeared;//NPC 던전에 나옴?
    bool clearedMap[MapWidth][MapHeight];//맵클리어함?
    bool shouldExitDungeon;

public:
    DungeonManager();

    void StartDungeon(Player& player, UI& ui, InventoryManager& inventoryManager);
    int GetMapWidth() const;
    int GetMapHeight() const;
    bool HasRoom(int x, int y) const;
    bool IsRoomVisited(int x, int y) const;
    bool IsPlayerAt(int x, int y) const;
    bool IsBossAt(int x, int y) const;
    bool IsRoomVisible(int x, int y) const;


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
    void HandleRoom(Player& player, RoomType roomType, UI& ui, InventoryManager& inventoryManager);
    // 전투 결과
    void HandleBattleResult(Player& player,
        Monster& monster,
        BattleResult result,
        UI& ui,
        InventoryManager& inventoryManager);

    void DropRandomItem(
        UI& ui,
        InventoryManager& inventoryManager);

    //void DisplayDungeonMap() const;




};


