#pragma once
#include <iostream>
#include <string>

//임시 플레이어 몬스터 보고 가져올 예정임
class Player;
class Monster;

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
    BattleResult StartBattle(Player& player, Monster& monster);

private://임시
    void PlayerAttack(Player& player, Monster& monster);//공격
    void MonsterAttack(Monster& monster, Player& player);//몬스터 공격
    bool TryEscape();//런 시도
    bool UseItem(Player& player);// 템사용
};

