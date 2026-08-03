//채원님 개발 테스트용 메인
//=======테스트절차=======
// 1. src/core/main.cpp 전체주석처리(ctrl+a 하고 ctrl+/ 하기)
// 2. 본인이름.cpp 에서 테스트 하기
// 3. 오류없으면
// 4. 본인이름.cpp 전체주석처리
// 5. src/core/main.cpp 전체주석처리 해제(ctrl+a 하고 ctrl+/ 하기)
// 6. 커밋하고 pr하기
// *테스트 내용은 남겨주세요!

#include <iostream>
#include "item/Item.h" 
#include "item/Inventory.h"
#include "character/Player.h"
#include "item/Shop.h"

using namespace std;

class TestPlayer : public Player {
public:
    TestPlayer(string name) : Player(name) {}

    void Attack() override {
        cout << "테스트 공격!\n";
    }
};

int main() {
    // 1. 테스트 준비 (플레이어 & 인벤토리)
    TestPlayer myPlayer("테스터");
    InventoryManager inventoryManager;
    ShopManager shop;
    myPlayer.SetGold(5000);

    cout << "--- 초기 상태  ---\n";
    cout << "플레이어 체력: " << myPlayer.GetHp() << " / " << myPlayer.GetMaxHp() << "\n";
    cout << "플레이어 공격력: " << myPlayer.GetTotalPower() << "\n\n";

    // 2. 아이템 생성 및 인벤토리에 추가
    HpPotion hpPotion;     // 기본 생성 시 1개
    hpPotion.ItemCount = 3; // 테스트를 위해 3개로 늘림

    TempABPotion buffPotion;
    buffPotion.ItemCount = 2; // 테스트를 위해 2개로 늘림

    inventoryManager.AddConsumable(hpPotion);
    inventoryManager.AddConsumable(buffPotion);

    inventoryManager.PrintAllSummary();

    // 3. 수동 선택 사용 테스트
    cout << "\n--- 수동 아이템 사용 테스트 ---\n";
    myPlayer.SetHp(10); // 몬스터에게 맞아서 체력이 10이 되었다고 가정
    cout << "[System] 몬스터의 공격 -> 현재 체력: " << myPlayer.GetHp() << "\n";

    // 직접 번호를 입력해서 포션을 먹는 함수 호출
    SelectAndUseConsumableItem(&myPlayer, inventoryManager);

    // 사용 후 인벤토리에서 잘 지워졌는지 확인
    inventoryManager.PrintAllSummary();

    // 4. 랜덤 사용 테스트
    cout << "\n--- 랜덤 아이템 사용 테스트 ---\n";
    UseRandomConsumableItem(&myPlayer, inventoryManager);

    inventoryManager.PrintAllSummary();
    shop.EnterShop(&myPlayer, inventoryManager);

    return 0;
}