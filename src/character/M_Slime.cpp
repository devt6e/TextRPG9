#include "character/M_Slime.h"

Slime::Slime(int PlayerLevel) : Monster("만년 지각생", PlayerLevel) {}

void Slime::SpeakEncounter() const {
    std::string s = "\n 핸드폰에 매니저님의 부재중이 찍힌 지각생이 나타났습니다!";
    um.PrintLog(s);
}

void Slime::SpeakBattleStart() const {
    std::string s = Name;
    s.append(": \"아 좀만 더 자도 될 것 같은데?\"");
    um.PrintLog(s);
}

void Slime::SpeakVictory() const {
    std::string s = Name;
    s.append(": \"이미 늦은거 출석 안하고 자야겠다~\"");
    um.PrintLog(s);
}

void Slime::SpeakDefeat() const {
    std::string s = Name;
    s.append(": \"네... 컴 킬게요 매니저님...\"");
    um.PrintLog(s);
}

void Slime::Attack() {
    std::string s = Name;
    s.append("이 인터넷 선을 끊습니다.");
    um.PrintLog(s);
}

Item* Slime::DropItem() {
    std::string s = Name;
    s.append("이(가) [지각생의 알람시계]를 두고 도망갔습니다.");
    um.PrintLog(s);

    return new AlarmClock();
}