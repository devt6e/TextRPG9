#include "character/M_JYJ.h"

JYJ::JYJ(int PlayerLevel) : Monster("남자는_태어나서_세번_컴파일한다_정윤재", PlayerLevel) {}

void JYJ::SpeakEncounter() const {
    std::string s = "\n '남자는 태어나서 세 번 컴파일한다'며 비장하게 키보드를 잡는 정윤재가 나타났습니다!";
    um.PrintLog(s);
}

void JYJ::SpeakBattleStart() const {
    std::string s = Name;
    s.append(": \"첫 번째 컴파일은 태어날 때, 두 번째는 배포할 때, 마지막 세 번째는... 바로 지금이다!\"");
    um.PrintLog(s);
}

void JYJ::SpeakVictory() const {
    std::string s = Name;
    s.append(": \"크하하! 에러 없는 클린 빌드의 맛을 보아라! 완벽해!\"");
    um.PrintLog(s);
}

void JYJ::SpeakDefeat() const {
    std::string s = Name;
    s.append(": \"크윽... 빌드 에러 99개라니... 네 번 컴파일하게 생겼잖아...?!\"");
    um.PrintLog(s);
}

void JYJ::Attack() {
    std::string s = Name;
    s.append("가 음침하게 남의 TIL을 염탐합니다!");
    um.PrintLog(s);
}