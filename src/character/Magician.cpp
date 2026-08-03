#include "chatacter/Magician.h"
#include <iostream>

Magician::Magician(std::string Name) : Player(Name) {
    Job = "마법사";
    SetMp(GetMp() + 30); // 특화 스탯: 마나 +30
}

void Magician::Attack() {
    std::cout << "마법사가 주문을 외웁니다." << std::endl;
};
;

