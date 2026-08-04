#include "character/P_Warrior.h"
#include <iostream>
#include <string>

Warrior::Warrior(std::string Name) : Player(Name) {
    Job = "열정 가득 수강생";
    SetMaxHp(GetMaxHp() + 5); // 특화 스탯: +5
    SetHp(GetMaxHp());         // 현재 체력 맞춰주기
}

void Warrior::Attack() {
    std::string s = "열정 가득 수강생이 키보드를 파괴할 기세로 강력하게 내리칩니다!";
    um.PrintLog(s);
}

int Warrior::Skill() {
    if (UseMp(30)) {
        // 1. 스킬 발동 텍스트 출력
        std::string s1 = "[스킬 발동] 열정 폭발! 밤샘 코딩으로 적에게 강력한 일격을 날립니다!";
        um.PrintLog(s1);

        // 2. 마나 소모량 출력 (숫자 변수들을 문자열로 변환하여 append)
        std::string s2 = "(소모 마나: 30 | 남은 마나: ";
        s2.append(std::to_string(Mp));
        s2.append("/");
        s2.append(std::to_string(MaxMp));
        s2.append(")");
        um.PrintLog(s2);

        // 3. 데미지 계산 및 결과 출력
        int skillDamage = Power * 2; // 데미지 계산 (공격력 * 2)

        std::string s3 = "적에게 ";
        s3.append(std::to_string(skillDamage));
        s3.append("의 피해를 입힙니다!");
        um.PrintLog(s3);

        return skillDamage;
    }
    return 0; // 마나 부족 시 데미지 0
}