#include "character/Player.h"
#include <iostream>

// 생성자: 이름과 기본 스탯(레벨 1, HP 200, 공격력 30, 경험치 0/100) 초기화
Player::Player(std::string Name) : Name(Name) {
}
