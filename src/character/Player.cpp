#include "character/Player.h"
#include <iostream>

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
    std::cout << Amount << "의 경험치를 획득했습니다!" << std::endl;

    while (Exp >= MaxExp) { // 레벨업 조건 
        Level++;
        Exp -= MaxExp; // 남은 경험치 보존

        // 레벨업 보상: 능력치 상승
        MaxHp += 20;
        Hp = MaxHp;
        Power += 5;

        std::cout << "레벨 업! " << Level << "레벨이 되었습니다! (현재 경험치: " << Exp << "/" << MaxExp << ")" << std::endl;
        std::cout << "최대 체력과 공격력이 상승했습니다." << std::endl;
    }
}
