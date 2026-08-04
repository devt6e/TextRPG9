#include "character/P_Thief.h"
#include <iostream>
#include <string> 

Thief::Thief(std::string Name) : Player(Name) {
    Job = "슬랙 이모지 잘 누르는 수강생";
    SetPower(GetPower() + 30); // 특화 스탯: 공격력 +30
}

void Thief::Attack() {
    std::string s = "슬랙 이모지 잘 누르는 수강생이 재빠른 손놀림으로 이모지를 난사합니다!";
    um.PrintLog(s);
}

int Thief::Skill() {
    if (UseMp(30)) {
        // 1. 스킬 발동 텍스트 출력
        std::string s1 = "[스킬 발동] 빛의 속도로 눈알 이모지(👀) 남기기! 적의 허를 찌르는 은밀한 공격!";
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