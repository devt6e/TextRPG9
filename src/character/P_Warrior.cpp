#include "character/P_Warrior.h"
#include <iostream>

Warrior :: Warrior(std::string Name) : Player(Name) {
        Job = "전사";
        SetMaxHp(GetMaxHp() + 30); // 최대 체력 상승
        SetHp(GetMaxHp());         // 현재 체력 맞춰주기
    }

    void Warrior::Attack() {
        std::cout << "전사가 자세를 고쳐잡습니다." << std::endl;
    };
