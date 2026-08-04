#include "character/M_Slime.h"

Slime::Slime(int PlayerLevel) : Monster("만년 지각생", PlayerLevel) {}

void Slime::SpeakEncounter() const {
    std::cout << "\n 핸드폰에 매니저님의 부재중이 찍힌 지각생이 나타났습니다!\n";
}

void Slime::SpeakBattleStart() const {
    std::cout << "만년 지각생: \"아 좀만 더 자도 될 것 같은데?\"\n";
}

void Slime::SpeakVictory() const {
    std::cout << "만년 지각생: \"이미 늦은거 출석 안하고 자야겠다~\"\n";
}

void Slime::SpeakDefeat() const {
    std::cout << "만년 지각생: \"네... 컴 킬게요 매니저님...\"\n";
}

void Slime::Attack() {
    std::cout << "만년 지각생이 인터넷 선을 끊습니다.\n";
}