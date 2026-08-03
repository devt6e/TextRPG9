#include "Item/Inventory.h"

Inventory<Item>& InventoryManager::GetConsumableBag() {
	return consumableBag_;
}

Inventory<Item>& InventoryManager::GetMaterialBag() {
	return materialBag_;
}

void InventoryManager::AddConsumable(Item item) {
	cout << "[소비 가방] ";
	consumableBag_.AddItem(item);
}

void InventoryManager::AddMaterial(Item item) {
	cout << "[재료 가방] ";
	materialBag_.AddItem(item);
}

void InventoryManager::PrintAllSummary() {
	cout << "\n======== [ 전체 인벤토리 ] ========";
	cout << "\n\n▶ [ 소비 아이템 ]";
	consumableBag_.PrintSummary();

	cout << "\n▶ [ 재료 아이템 ]";
	materialBag_.PrintSummary();
	cout << "===================================\n";
}


//#include <iostream>
//#include "item/Item.h" 
//
//using namespace std;
//
//int main() {
//    // 1. 테스트용 객체 준비 (플레이어 & 인벤토리)
//    Player player;
//    InventoryManager invenManager;
//
//    cout << "--- 초기 상태  ---\n";
//    cout << "플레이어 체력: " << player.getHp() << " / " << player.getMaxHp() << "\n";
//    cout << "플레이어 공격력: " << player.getTotalPower() << "\n\n";
//
//    // 2. 아이템 생성 및 인벤토리에 추가
//    HpPotion hpPotion;     // 기본 생성 시 1개
//    hpPotion.ItemCount = 3; // 테스트를 위해 3개로 늘림
//
//    TempABPotion buffPotion;
//    buffPotion.ItemCount = 2; // 테스트를 위해 2개로 늘림
//
//    invenManager.AddConsumable(hpPotion);
//    invenManager.AddConsumable(buffPotion);
//
//    invenManager.PrintAllSummary();
//
//    // 3. 수동 선택 사용 테스트
//    cout << "\n--- 수동 아이템 사용 테스트 ---\n";
//    player.setHp(10); // 몬스터에게 맞아서 체력이 10이 되었다고 가정
//    cout << "[System] 몬스터의 공격 -> 현재 체력: " << player.getHp() << "\n";
//
//    // 유저가 직접 번호를 입력해서 포션을 먹는 함수 호출
//    SelectAndUseConsumableItem(&player, invenManager);
//
//    // 사용 후 인벤토리에서 잘 지워졌는지 확인
//    invenManager.PrintAllSummary();
//
//    // 4. 랜덤 사용 테스트
//    cout << "\n--- 랜덤 아이템 사용 테스트 ---\n";
//    UseRandomConsumableItem(&player, invenManager);
//
//    invenManager.PrintAllSummary();
//
//    return 0;
//}