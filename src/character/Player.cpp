#include "Player.h"
#include <iostream>

// 생성자: 이름과 기본 스탯(레벨 1, HP 200, 공격력 30, 경험치 0/100) 초기화
Player::Player(std::string Name, int Hp, int Mp, int Power, int Defence)
    : Name(Name), Job("초보자"), Level(1), Hp(200), Mp(Mp), Power(Power), Defence(Defence), Exp(0), MaxExp(100) {
}

void Player::Level() {
    Level++;
    Exp = 0;


int main() {
    string name;
    const int SIZE = 4;
    int stat[SIZE] = { 0 };


    return 0;
}
