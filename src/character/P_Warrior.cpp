#include "character/P_Warrior.h"
#include <iostream>

Warrior :: Warrior(std::string Name) : Player(Name) {
        Job = "열정 가득 수강생";
        SetMaxHp(GetMaxHp() + 30); // 최대 체력 상승
        SetHp(GetMaxHp());         // 현재 체력 맞춰주기
    }

    void Warrior::Attack() {
        std::cout << "열정 가득 수강생이 키보드를 파괴할 기세로 강력하게 내리칩니다!" << std::endl;
    };

    int Warrior::Skill() {
        if (UseMp(30)) {
            std::cout << "[스킬 발동] 열정 폭발! 밤샘 코딩으로 적에게 강력한 일격을 날립니다!\n";
            std::cout << "(소모 마나: 30 | 남은 마나: " << Mp << "/" << MaxMp << ")\n";

            int skillDamage = Power * 2; // 데미지 계산 (공격력 * 2)
            std::cout << "적에게 " << skillDamage << "의 피해를 입힙니다!\n";
            return skillDamage;
        }
        return 0; // 마나 부족 시 데미지 0
    }