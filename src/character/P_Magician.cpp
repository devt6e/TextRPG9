#include "character/P_Magician.h"
#include <iostream>
#include <string>

Magician::Magician(std::string Name) : Player(Name) {
    Job = "TIL 우수 작성 수강생";
    SetDefence(GetDefence() + 2); // 특화 스탯: 방어력 +2
}

void Magician::Attack() {
    std::string s = "TIL 우수 작성 수강생이 날카로운 글쓰기 공격을 퍼붓습니다!";
    um.PrintLog(s);
}

int Magician::Skill() {
    if (UseMp(30)) {
        // 1. 스킬 발동 텍스트 출력
        std::string s1 = "[스킬 발동] TIL 1일 1commit 버프! 지식의 빛으로 적의 방어력을 무력화합니다!";
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
    return 0;
}