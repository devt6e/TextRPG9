#include "character/P_Thief.h"
#include <iostream>

Thief::Thief(std::string Name) : Player(Name) {
    Job = "도적";
    SetPower(GetPower() + 30); // 특화 스탯: 공격력 +30
}

void Thief::Attack() {
    std::cout << "도적이 기회를 엿봅니다." << std::endl;
};
