#include "character/M_husband.h"

husband::husband(int PlayerLevel) : Monster("매니저님 남편 꿈나무", PlayerLevel) {}

void husband::SpeakEncounter() const {
    std::cout << "\n 매니저님을 향한 불타는 순애보를 품은 '매니저님 남편 꿈나무' 수강생이 나타났습니다!\n";
}

void husband::SpeakBattleStart() const {
    std::cout << "매니저님 남편 꿈나무: \"내가 꼭 매니저님의 남편이 되고 말겠어!\"\n";
}

void husband::SpeakVictory() const {
    std::cout << "매니저님 남편 꿈나무: \"하하하! 봤지? 이 정도 패기면 매니저님 남편.. 할 수 있을거 같지 않아?\"\n";
}

void husband::SpeakDefeat() const {
    std::cout << "매니저님 남편 꿈나무: \"크윽... 아직 매니저님 눈에 들려면 공부를 더 하고 와야 하는가...!\"\n";
}

void husband::Attack() {
    std::cout << "매니저님 남편 꿈나무가 정성이 가득 담긴 러브레터를 사정없이 던집니다!\n";
}