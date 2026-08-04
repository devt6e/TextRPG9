#include "character/P_Thief.h"
#include <iostream>

Thief::Thief(std::string Name) : Player(Name) {
    Job = "슬랙 이모지 잘 누르는 수강생";
    SetPower(GetPower() + 30); // 특화 스탯: 공격력 +30
}

void Thief::Attack() {
    std::cout << "슬랙 이모지 잘 누르는 수강생이 재빠른 손놀림으로 이모지를 난사합니다!" << std::endl;
};

int Thief::Skill() {
    if (UseMp(30)) {
        std::cout << "[스킬 발동] 빛의 속도로 눈알 이모지(👀) 남기기! 적의 허를 찌르는 은밀한 공격!\n";
        std::cout << "(소모 마나: 30 | 남은 마나: " << Mp << "/" << MaxMp << ")\n";

        int skillDamage = Power * 2; // 데미지 계산 (공격력 * 2)
        std::cout << "적에게 " << skillDamage << "의 피해를 입힙니다!\n";
        return skillDamage;
    }
    return 0;
}