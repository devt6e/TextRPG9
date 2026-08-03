// 아이템 기능 테스트용 임시 메인

/*
//해주님 개발 테스트용 메인
//=======테스트절차=======
// 1. src/core/main.cpp 전체주석처리(ctrl+a 하고 ctrl+/ 하기)
// 2. 본인이름.cpp 에서 테스트 하기
// 3. 오류없으면
// 4. 본인이름.cpp 전체주석처리
// 5. src/core/main.cpp 전체주석처리 해제(ctrl+a 하고 ctrl+/ 하기)
// 6. 커밋하고 pr하기
// *테스트 내용은 남겨주세요!

#include <iostream>
#include <limits>
#include "item/Item.h"
#include "item/Inventory.h"
#include "character/Player.h"
#include "character/P_Warrior.h"

using namespace std;




void PrintStatus(const Player& player, InventoryManager& invManager) {
	cout << "\n----------------------------------------" << endl;
	cout << "[플레이어: " << player.GetName() << "]"
		<< " | HP: " << player.GetHp() << " / " << player.GetMaxHp()
		<< " | MP: " << player.GetMp() << " / " << player.GetMaxMp() << endl
		<< " | 기본 공격력: " << player.GetPower()
		<< " | 버프: +" << player.GetTempAttackBuff()
		<< " | 최종 공격력: " << player.GetTotalPower() << endl
		<< " | 기본 방어력: " << player.GetDefence()
		<< " | 버프: +" << player.GetTempDEFBuff()
		<< " | 최종 방어력: " << player.GetTotalDEF() << endl;
	cout << "----------------------------------------" << endl;

	invManager.GetConsumableBag().PrintSummary();
	cout << endl << endl;
}

int main() {
	Player* player = new Warrior("전사");
	player->SetHp(50);
	player->SetMp(30);
	InventoryManager invManager;


	HpPotion hpPotion;
	hpPotion.ItemCount = 2;

	MpPotion mpPotion;
	mpPotion.ItemCount = 2;

	TempABPotion buffPotion;
	buffPotion.ItemCount = 2;

	TempDEFPotion defBuffPotion;
	defBuffPotion.ItemCount = 2;


	invManager.AddConsumable(hpPotion);
	invManager.AddConsumable(mpPotion);
	invManager.AddConsumable(buffPotion);
	invManager.AddConsumable(defBuffPotion);

	cout << endl << "테스트 시작" << endl;

	bool running = true;

	while (running) {

		cout << "==========================================" << endl;
		cout << "[메인 메뉴]" << endl;
		cout << "1. 아이템 직접 선택" << endl;
		cout << "2. 랜덤 사용" << endl;
		cout << "3. 현재 스탯" << endl;
		cout << "4. 전투 종료 / 공격력 버프 해제" << endl; 
		cout << "0. 프로그램 종료" << endl;
		cout << "==========================================" << endl;
		cout << "메뉴 입력 >> ";
		cout << endl << endl;

		int menuChoice{ 0 };
		if (!(cin >> menuChoice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << " 잘못된 입력" << endl;
			continue;
		}

		switch (menuChoice) {
		case 1:
		
			cout << "아이템 선택!" << endl;
			SelectAndUseConsumableItem(player, invManager);
			break;

		case 2:
			cout << "아이템 랜덤 선택!" << endl;
			UseRandomConsumableItem(player, invManager);
			break;

		case 3:
			cout << "현재 스탯" << endl;
			PrintStatus(*player, invManager);
			break;

		case 4:
			cout << "전투 종료" << endl;
			player->ResetBuff();
			break;

		case 0:
			cout << "게임종료" << endl;
			running = false;
			break;

		default:
			cout << "X" << endl;
			break;
		}
	}

	return 0;
}
*/