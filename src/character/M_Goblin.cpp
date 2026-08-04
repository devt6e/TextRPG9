#include "character/M_Goblin.h"

Goblin::Goblin(int PlayerLevel) : Monster("쿠키 납치범", PlayerLevel) {}

void Goblin::SpeakEncounter() const {
    std::cout << "\n 품에 귀여운 고양이 '쿠키'를 꽁꽁 묶어 안고 있는 수상한 자가 나타났습니다!\n";
}

void Goblin::SpeakBattleStart() const {
    std::cout << "쿠키 납치범: \"크하하! 이 녀석을 되찾고 싶다면 나를 쓰러뜨려 보시지!\"\n";
}

void Goblin::SpeakVictory() const {
    std::cout << "쿠키 납치범: \"크윽... 이렇게 쿠키를 다시 잃다니...!\"\n";
}

void Goblin::SpeakDefeat() const {
    std::cout << "쿠키 납치범: \"하하하! 고양이 한 마리도 못 구하는 실력으로 뭘 하겠나!\"\n";
}

void Goblin::Attack() {
    std::cout << "쿠키 납치범이 마성의 츄르 폭탄을 던져 위협합니다!\n";
}