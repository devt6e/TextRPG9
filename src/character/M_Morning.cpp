#include "character/M_Morning.h"

Morning::Morning(int PlayerLevel) : Monster("아침마다 모닝콜로 노래 부르는 수강생", PlayerLevel) {}

void Morning::SpeakEncounter() const {
    std::string s = "\n 아침만 되면 ZEP 마이크를 켜고 노래를 부르기 시작하는 수강생이 나타났습니다!";
    um.PrintLog(s);
}

void Morning::SpeakBattleStart() const {
    std::string s = Name;
    s.append(": \"다들 잠 안 깼지? 목 풀기용 4단 고음 들어간다~ 소리질러!!\"");
    um.PrintLog(s);
}

void Morning::SpeakVictory() const {
    std::string s = Name;
    s.append(": \"하하하! 내 모닝콘서트 어땠냐? 귀가 아주 그냥 뻥 뚫렸지!\"");
    um.PrintLog(s);
}

void Morning::SpeakDefeat() const {
    std::string s = Name;
    s.append(": \"크윽... 고음이 삑사리나다니... 내 목상태가 이럴 리가 없어...!\"");
    um.PrintLog(s);
}

void Morning::Attack() {
    std::string s = Name;
    s.append("이 ZEP 맵 전체가 울리는 고음 폭탄을 날립니다!");
    um.PrintLog(s);
}

Item* Morning::DropItem() {
    std::string s = Name;
    s.append("이 도망간 후, [마이크]가 덩그러니 남았습니다.");
    um.PrintLog(s);

    return new Microphone();
}