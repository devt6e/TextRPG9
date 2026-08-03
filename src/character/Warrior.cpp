#include "chatacter/Warrior.h"
#include <iostream>

Warrior :: Warrior(std::string Name) : Player(Name) {
        Job = "전사";
        SetHp(GetHp() + 30); // 특화 스탯: 체력 +30
    }

    void Warrior::Attack() {
        std::cout << "전사가 자세를 고쳐잡습니다." << std::endl;
    };
;
