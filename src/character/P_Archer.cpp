#include "character/P_Archer.h"
#include <iostream>

Archer::Archer(std::string Name) : Player(Name) {
    Job = "궁수";
    SetPower(GetPower() + 30); // 특화 스탯: 공격력 +30
}

void Archer::Attack() {
    std::cout << "궁수가 활 시위를 당깁니다." << std::endl;
};