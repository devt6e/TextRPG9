#include "character/P_Magician.h"
#include <iostream>

Magician::Magician(std::string Name) : Player(Name) {
    Job = "TIL 우수 작성 수강생";
    SetDefence(GetDefence() + 30); // 특화 스탯: 방어력 +30
}

void Magician::Attack() {
    std::cout << "TIL 우수 작성 수강생이 날카로운 글쓰기 공격을 퍼붓습니다!" << std::endl;
};

int Magician::Skill() {
    if (UseMp(30)) {
        std::cout << "[스킬 발동] TIL 1일 1commit 버프! 지식의 빛으로 적의 방어력을 무력화합니다!\n";
        std::cout << "(소모 마나: 30 | 남은 마나: " << Mp << "/" << MaxMp << ")\n";

        int skillDamage = Power * 2; // 데미지 계산 (공격력 * 2)
        std::cout << "적에게 " << skillDamage << "의 피해를 입힙니다!\n";
        return skillDamage;
    }
    return 0;
}