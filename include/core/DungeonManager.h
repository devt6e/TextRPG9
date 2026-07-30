#pragma once
#include <iostream>
#include <string>

#include "BattleManager.h"

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
    int currentRoom;

public:
    DungeonManager();

    void StartDungeon(Player& player);
    void MoveRoom(Player& player);

private:
    //임시
    RoomType DecideRoomType();
    void HandleRoom(Player& player, RoomType roomType);
    void HandleBattleResult(BattleResult result);
};
