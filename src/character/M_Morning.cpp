#include "character/M_Morning.h"

Morning::Morning(int PlayerLevel) : Monster("아침마다 모닝콜로 노래 부르는 수강생", PlayerLevel) {}

void Morning::SpeakEncounter() const {
    std::cout << "\n 아침만 되면 ZEP 마이크를 켜고 노래를 부르기 시작하는 수강생이 나타났습니다!\n";
}

void Morning::SpeakBattleStart() const {
    std::cout << "아침마다 모닝콜로 노래 부르는 수강생: \"다들 잠 안 깼지? 목 풀기용 4단 고음 들어간다~ 소리질러!!\"\n";
}

void Morning::SpeakVictory() const {
    std::cout << "아침마다 모닝콜로 노래 부르는 수강생: \"하하하! 내 모닝콘서트 어땠냐? 귀가 아주 그냥 뻥 뚫렸지!\"\n";
}

void Morning::SpeakDefeat() const {
    std::cout << "아침마다 모닝콜로 노래 부르는 수강생: \"크윽... 고음이 삑사리나다니... 내 목상태가 이럴 리가 없어...!\"\n";
}

void Morning::Attack() {
    std::cout << "아침마다 모닝콜로 노래 부르는 수강생이 ZEP 맵 전체가 울리는 고음 폭탄을 날립니다!\n";
}