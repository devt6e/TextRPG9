//보빈님 개발 테스트용 메인
//=======테스트절차=======
// 1. src/core/main.cpp 전체주석처리(ctrl+a 하고 ctrl+/ 하기)
// 2. 본인이름.cpp 에서 테스트 하기
// 3. 오류없으면
// 4. 본인이름.cpp 전체주석처리
// 5. src/core/main.cpp 전체주석처리 해제(ctrl+a 하고 ctrl+/ 하기)
// 6. 커밋하고 pr하기
// *테스트 내용은 남겨주세요!


/*#include <iostream>
#include <string>
#include "character/P_Warrior.h"
#include "character/P_Archer.h"
#include "character/P_Magician.h"
#include "character/P_Thief.h"

void PrintStatus(Player* p) {
    std::cout << "\n--- [ " << p->GetName() << "의 스탯 ] ---" << std::endl;
    std::cout << "직업: " << p->GetJob() << " | 레벨: " << p->GetLevel() << std::endl;
    std::cout << "HP: " << p->GetHp() << "/" << p->GetMaxHp() << std::endl;
    std::cout << "MP: " << p->GetMp() << "/" << p->GetMaxMp() << std::endl;
    std::cout << "공격력: " << p->GetPower() << " | 방어력: " << p->GetDefence() << std::endl;
    std::cout << "---------------------------\n" << std::endl;
}

int main() {
        std::string name;
        int choice;

        std::cout << "이름을 입력하세요: ";
        std::cin >> name;

        std::cout << "직업을 선택하세요 (1.전사 2.궁수 3.마법사 4.도적): ";
        std::cin >> choice;

        Player* player = nullptr;

        switch (choice) {
        case 1: player = new Warrior(name); break;
        case 2: player = new Archer(name); break;
        case 3: player = new Magician(name); break;
        case 4: player = new Thief(name); break;
        default: player = new Warrior(name); // 기본값
        }

        PrintStatus(player);
        player->Attack();

        player->AddExp(125);

        delete player;
        return 0;
}*/