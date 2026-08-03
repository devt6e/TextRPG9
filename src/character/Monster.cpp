#include "character/Monster.h"
#include <random>

Monster::Monster(std::string Name, int PlayerLevel) : Name(Name) {
    std::random_device rd;
    std::mt19937 gen(rd());

    // 체력: (레벨 * 20) ~ (레벨 * 30)
    std::uniform_int_distribution<int> hpDist(PlayerLevel * 20, PlayerLevel * 30); // 범위 - (PlayerLevel * 20, PlayerLevel * 30)
    Hp = hpDist(gen);
    MaxHp = Hp; // 최대 체력으로 현재 체력 동기화

    // 공격력: (레벨 * 5) ~ (레벨 * 10)
    std::uniform_int_distribution<int> powerDist(PlayerLevel * 5, PlayerLevel * 10);
    Power = powerDist(gen);

    // 보상 
    std::uniform_int_distribution<int> expDist(1, 10); // 경험치 획득량을 1~10으로 지정
    DropExp = expDist(gen);

    std::uniform_int_distribution<int> goldDist(5, 10); // 템 구현은 아직, 5~10의 재화 드랍
    DropGold = goldDist(gen);
}