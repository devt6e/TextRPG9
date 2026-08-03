#include "character/M_Goblin.h"

Goblin::Goblin(int PlayerLevel) : Monster("고블린", PlayerLevel) {}

void Goblin::Attack() {
	std::cout << "고블린이 비열하게 웃습니다." << std::endl;
}