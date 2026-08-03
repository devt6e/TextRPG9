#include "character/M_Orc.h"

Orc::Orc(int PlayerLevel) : Monster("오크", PlayerLevel) {}

void Orc::Attack() {
	std::cout << "오크가 근육을 과시합니다." << std::endl;
}