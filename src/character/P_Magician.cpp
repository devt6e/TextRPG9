#include "character/P_Magician.h"
#include <iostream>

Magician::Magician(std::string Name) : Player(Name) {
    Job = "마법사";
    SetMaxMp(GetMaxMp() + 30); // 최대 마나 상승
    SetMp(GetMaxMp());         // 현재 마나 맞춰주기
}

void Magician::Attack() {
    std::cout << "마법사가 주문을 시전합니다." << std::endl;
};

