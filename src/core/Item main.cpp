// 아이템 기능 테스트용 임시 메인

/*

#include <iostream>
#include <limits>
#include "Item.h"
#include "Inventory.h"
#include "player.h"

using namespace std;

void PrintStatus(const Player& player, InventoryManager& invManager) {
	cout << "\n----------------------------------------" << endl;
	cout << "[플레이어] HP: " << player.GetHp() << " / " << player.GetMaxHp()
		<< " | 공격력: " << player.GetPower()
		<< " | 기본 마나: " << player.GetMp()
		<< " | 버프: +" << player.GetTempAttackBuff()
		<< " | 최종 공격력: " << player.GetTotalPower() << endl;
	cout << "----------------------------------------" << endl;

	invManager.GetConsumableBag().PrintSummary();
	cout << endl << endl;
}

int main() {
	Player player;
	InventoryManager invManager;

	player.SetHp(50);
	player.SetPower(50);
	player.SetMp(50);

	HpPotion hpPotion;
	hpPotion.ItemCount = 2;

	MpPotion mpPotion;
	mpPotion.ItemCount = 2;

	TempABPotion buffPotion;
	buffPotion.ItemCount = 2;

	invManager.AddConsumable(hpPotion);
	invManager.AddConsumable(mpPotion);
	invManager.AddConsumable(buffPotion);

	cout << endl << "테스트 시작" << endl;

	bool running = true;

	while (running) {

		cout << "==========================================" << endl;
		cout << "[메인 메뉴]" << endl;
		cout << "1. 아이템 직접 선택" << endl;
		cout << "2. 랜덤 사용" << endl;
		cout << "3. 현재 스탯" << endl;
		cout << "3. 전투 종료 / 공격력 버프 해제" << endl;
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
			cout << endl << endl;
			cout << "아이템 선택!" << endl;
			SelectAndUseConsumableItem(&player, invManager);
			break;

		case 2:
			cout << endl << endl;
			cout << "아이템 랜덤 선택!" << endl;
			UseRandomConsumableItem(&player, invManager);
			break;

		case 3:
			cout << endl << endl;
			cout << "현재 스탯" << endl;
			PrintStatus(player, invManager);
			break;

		case 4:
			cout << endl << endl;
			cout << "전투 종료" << endl;
			player.ResetBuff();
			break;


		case 0:
			cout << endl << endl;
			cout << "게임종료" << endl;
			running = false;
			break;

		default:
			cout << endl << endl;
			cout << "X" << endl;
			break;
		}
	}

	return 0;
}


*/