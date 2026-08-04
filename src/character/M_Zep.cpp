#include "character/M_Zep.h"

Zep::Zep(int PlayerLevel) : Monster("일 안하는 ZEP 본사 직원", PlayerLevel) {}

void Zep::SpeakEncounter() const {
    // 특정 이름이 맨 앞에 오지 않는 문장이므로 전체를 문자열에 담습니다.
    std::string s = "\n 아바타만 세워두고 도망간 '일 안하는 ZEP 본사 직원'이 나타났습니다!";
    um.PrintLog(s);
}

void Zep::SpeakBattleStart() const {
    std::string s = Name;
    s.append(": \"어... 저 지금 칼퇴해야 해서 바쁩니다만 어쩐 일이신지?\"");
    um.PrintLog(s);
}

void Zep::SpeakVictory() const {
    std::string s = Name;
    s.append(": \"휴, 오늘도 무사히 일 안 하고 버텼다.\"");
    um.PrintLog(s);
}

void Zep::SpeakDefeat() const {
    std::string s = Name;
    s.append(": \"아니 다들 일 안하고 월급 받고 싶잖아요!!\"");
    um.PrintLog(s);
}

void Zep::Attack() {
    std::string s = Name;
    s.append("이 무한 로딩 걸리는 감자 서버 링크를 던집니다!");
    um.PrintLog(s);
}