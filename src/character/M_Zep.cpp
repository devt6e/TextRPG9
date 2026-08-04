#include "character/M_Zep.h"

Zep::Zep(int PlayerLevel) : Monster("일 안하는 ZEP 본사 직원", PlayerLevel) {}

void Zep::SpeakEncounter() const {
    std::cout << "\n 아바타만 세워두고 도망간 '일 안하는 ZEP 본사 직원'이 나타났습니다!\n";
}

void Zep::SpeakBattleStart() const {
    std::cout << "일 안하는 ZEP 본사 직원: \"어... 저 지금 칼퇴해야 해서 바쁩니다만 어쩐 일이신지?\"\n";
}

void Zep::SpeakVictory() const {
    std::cout << "일 안하는 ZEP 본사 직원: \"휴, 오늘도 무사히 일 안 하고 버텼다.\"\n";
}

void Zep::SpeakDefeat() const {
    std::cout << "일 안하는 ZEP 본사 직원: \"아니 다들 일 안하고 월급 받고 싶잖아요!!\"\n";
}

void Zep::Attack() {
    std::cout << "일 안하는 ZEP 본사 직원이 무한 로딩 걸리는 감자 서버 링크를 던집니다!\n";
}