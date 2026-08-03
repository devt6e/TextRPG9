#include "character/M_Slime.h"

Slime::Slime(int PlayerLevel) : Monster("슬라임", PlayerLevel) {}

	void Slime::Attack() {
		std::cout << "슬라임이 말랑해보입니다." << std::endl;
	}