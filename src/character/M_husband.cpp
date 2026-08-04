#include "character/M_husband.h"

husband::husband(int PlayerLevel) : Monster("매니저님 남편 꿈나무", PlayerLevel) {}

void husband::SpeakEncounter() const {
    std::string s = "\n 매니저님을 향한 불타는 순애보를 품은 '";
    s.append(Name);
    s.append("' 수강생이 나타났습니다!");
    um.PrintLog(s);
}

void husband::SpeakBattleStart() const {
    std::string s = Name;
    s.append(": \"내가 꼭 매니저님의 남편이 되고 말겠어!\"");
    um.PrintLog(s);
}

void husband::SpeakVictory() const {
    std::string s = Name;
    s.append(": \"하하하! 봤지? 이 정도 패기면 매니저님 남편.. 할 수 있을거 같지 않아?\"");
    um.PrintLog(s);
}

void husband::SpeakDefeat() const {
    // 1. 몬스터 패배 대사 출력
    std::string s = Name;
    s.append(": \"크윽... 아직 매니저님 눈에 들려면 공부를 더 하고 와야 하는가...!\"");
    um.PrintLog(s);

    // 2. 매니저님 구출 시스템 메시지 출력
    std::string systemMsg = "\n[시스템] 납치됐던 동현 매니저님이 무사히 풀려났습니다!";
    um.PrintLog(systemMsg);
}

void husband::Attack() {
    std::string s = Name;
    s.append("가 정성이 가득 담긴 러브레터를 사정없이 던집니다!");
    um.PrintLog(s);
}