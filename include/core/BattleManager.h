#pragma once
#include <iostream>
#include <string>

//임시 플레이어 몬스터 보고 가져올 예정임
class Player;
class Monster;
class InventoryManager;
class UI;

enum class BattleResult
{
    Victory,//승리
    Defeat,//패배
    Escaped//런
};

class BattleManager
{
public:
    //메인에서? 전투 할때 사용
    BattleResult StartBattle(Player& player, 
        Monster& monster, 
        UI& ui,
        InventoryManager& inventoryManager);

private://임시
    void PlayerAttack(Player& player, Monster& monster, UI& ui);//공격
    bool PlayerSkill(Player& player, Monster& monster, UI& ui);//스킬
    void MonsterAttack(Monster& monster, Player& player, UI& ui);//몬스터 공격
    bool TryEscape();//런 시도
    bool UseItem(Player& player, InventoryManager& inventoryManager);// 템사용
};

