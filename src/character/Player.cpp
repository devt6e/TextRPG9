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
