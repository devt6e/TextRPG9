#include "character/M_Goblin.h"

Goblin::Goblin(int PlayerLevel) : Monster("쿠키 납치범", PlayerLevel) {}

void Goblin::SpeakEncounter() const {
    std::string s = "\n 품에 귀여운 고양이 '쿠키'를 꽁꽁 묶어 안고 있는 수상한 자가 나타났습니다!";
    um.PrintLog(s);
}

void Goblin::SpeakBattleStart() const {
    std::string s = Name;
    s.append(": \"크하하! 이 녀석을 되찾고 싶다면 나를 쓰러뜨려 보시지!\"");
    um.PrintLog(s);
}

void Goblin::SpeakVictory() const {
    std::string s = Name;
    s.append(": \"하하하! 고양이 한 마리도 못 구하는 실력으로 뭘 하겠나!\"");
    um.PrintLog(s);
}

void Goblin::SpeakDefeat() const {
    std::string s = Name;
    s.append(": \"크윽... 이렇게 쿠키를 다시 잃다니...!\""); 
    um.PrintLog(s);
}

void Goblin::Attack() {
    std::string s = Name;
    s.append("이(가) 마성의 츄르 폭탄을 던져 위협합니다!");
    um.PrintLog(s);
}

Item* Goblin::DropItem() {
    std::string s = Name;
    s.append("이(가) [쿠키]를 남겨두고 떠났습니다!");
    um.PrintLog(s);

    return new CookieCat();
}