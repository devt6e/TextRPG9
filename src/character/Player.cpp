#include "character/Player.h"
#include <iostream>
#include <string> // std::to_string을 사용하기 위해 필요합니다.

// 최대 체력을 넘거나 0 미만으로 떨어지지 않게 하는 함수
void Player::SetHp(int Value) {
    Hp = Value;
    if (Hp > MaxHp) Hp = MaxHp;
    if (Hp < 0) Hp = 0;
}

// 최대 마나을 넘거나 0 미만으로 떨어지지 않게 하는 함수
void Player::SetMp(int Value) {
    Mp = Value;
    if (Mp > MaxMp) Mp = MaxMp;
    if (Mp < 0) Mp = 0;
}

void Player::AddExp(int Amount) {
    Exp += Amount;

    // 1. 경험치 획득 메시지 (숫자를 문자로 변환)
    std::string s1 = std::to_string(Amount);
    s1.append("의 경험치를 획득했습니다!");
    um.PrintLog(s1);

    while (Exp >= MaxExp) { // 레벨업 조건 
        Level++;
        Exp -= MaxExp; // 남은 경험치 보존

        // 레벨업 보상: 능력치 상승
        MaxHp += 20;
        Hp = MaxHp;
        Power += 5;

        // 2. 레벨 업 상세 메시지 (여러 숫자 변수들을 이어 붙이기)
        std::string s2 = "레벨 업! ";
        s2.append(std::to_string(Level));
        s2.append("레벨이 되었습니다! (현재 경험치: ");
        s2.append(std::to_string(Exp));
        s2.append("/");
        s2.append(std::to_string(MaxExp));
        s2.append(")");
        um.PrintLog(s2);

        // 3. 스탯 상승 메시지 (순수 문자열이므로 바로 출력)
        um.PrintLog("최대 체력과 공격력이 상승했습니다.");
    }
}