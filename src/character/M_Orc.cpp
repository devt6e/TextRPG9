#include "character/M_Orc.h"

Orc::Orc(int PlayerLevel) : Monster("ZEM 탈취범", PlayerLevel) {}

void Orc::SpeakEncounter() const {
    std::string s = "\n 품에 가득 ZEM 주머니를 꽁꽁 숨긴 채 도망칠 준비를 하는 수상한 자가 나타났습니다!";
    um.PrintLog(s);
}

void Orc::SpeakBattleStart() const {
    std::string s = Name;
    s.append(": \"네가 고생해서 모은 ZEM, 잘 쓸게! 되찾고 싶다면 한번 해보시지!\"");
    um.PrintLog(s);
}

void Orc::SpeakVictory() const {
    std::string s = Name;
    s.append(": \"하하하! 역시 남의 ZEM으로 하는 꾸미기가 제일 재밌어!\"");
    um.PrintLog(s);
}

void Orc::SpeakDefeat() const {
    std::string s = Name;
    s.append(": \"크윽... 이렇게 악착같이 훔친 ZEM을 다시 돌려줘야하다니...!\"");
    um.PrintLog(s);
}

void Orc::Attack() {
    std::string s = Name;
    s.append("이 뿅망치를 사정없이 휘두르며 위협합니다!");
    um.PrintLog(s);
}

Item* Orc::DropItem() {
    std::string s = Name;
    s.append("이(가) 흘리고 간 [젬 주머니]를 발견했습니다!");
    um.PrintLog(s);

    return new ZemPouch();
}