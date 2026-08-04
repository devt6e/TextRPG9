#include <iostream>
#include <string>
#include <algorithm>
#include "item/Shop.h" 

//using namespace std;

// 1. 생성자
ShopManager::ShopManager() {
    shopItems_.push_back(HpPotion());
    shopItems_.push_back(MpPotion());
    shopItems_.push_back(TempABPotion());
    shopItems_.push_back(TempDEFPotion());
}

// 2. 아이템 목록 출력
void ShopManager::PrintShopItems() {
    um.PrintLog("[ 구매 목록 ]");
    um.PrintSelection(shopItems_);
    //for (int i = 0; i < shopItems_.size(); i++) {
    //    cout << i + 1 << ". " << shopItems_[i].Name << " - " << shopItems_[i].Price << "G\n";
    //}
    /*um.PrintMenu();*/

}

// 3. 구매 기능
void ShopManager::BuyItem(Player* player, InventoryManager& inventoryManager) {
    PrintShopItems();

    int buyChoice = um.InputSelection("살 아이템 번호 (취소 0): ");

    if (buyChoice == 0) return;

    if (buyChoice < 1 || buyChoice > shopItems_.size()) {
        um.PrintLog("[오류] 잘못된 번호입니다.");
        return;
    }

    Item buyItem = shopItems_[buyChoice - 1];
    if (player->GetGold() >= buyItem.Price) {
        player->SetGold(player->GetGold() - buyItem.Price);

        inventoryManager.AddConsumable(buyItem);
        um.PrintLog("[System] " + buyItem.Name + "을(를) 구매했습니다!");
    }
    else {
        um.PrintLog("[System] 잼이 부족합니다!");
    }
}

// 4. 판매 기능
void ShopManager::SellItem(Player* player, InventoryManager& inventoryManager) {
    
    std::vector<std::string> options = { "1. 소비 아이템 팔기","2. 재료 아이템 팔기" };
    um.PrintSelection(options);
    int bagChoice = um.InputSelection("어떤 가방의 아이템을 파시겠습니까?");
    
    Inventory<Item>* selectedBag = nullptr;
    if (bagChoice == 1) {
        selectedBag = &inventoryManager.GetConsumableBag();
    }
    else if (bagChoice == 2) {
        selectedBag = &inventoryManager.GetMaterialBag();
    }
    else {
        um.PrintLog("[오류] 잘못된 선택입니다.");
        return;
    }

    selectedBag->PrintSummary();

    int sellChoice= um.InputSelection("팔 아이템 번호 (취소 0): ");
    if (sellChoice == 0) return;

    Item* targetItem = selectedBag->GetItem(sellChoice);

    if (targetItem != nullptr) {
        int amount= um.InputSelection("몇 개를 파시겠습니까? (최대 " + std::to_string(targetItem->ItemCount) + "개): ");

        if (amount <= 0) {
            um.PrintLog("[오류] 1개 이상 판매해야 합니다.");
            return;
        }

        if (amount > targetItem->ItemCount) {
            um.PrintLog("[오류] 가진 갯수보다 많이 팔 수 없습니다!");
            return;
        }

        int sellPrice = (targetItem->Price * amount * 60) / 100;

        if (selectedBag->RemoveItem(sellChoice, amount)) {
            player->SetGold(player->GetGold() + sellPrice);
            um.PrintLog("[System] " + std::to_string(sellPrice) + "ZEM을 획득했습니다!");
        }
    }
}

// 5. 상점 메인
void ShopManager::EnterShop(Player* player, InventoryManager& inventoryManager) {
    while (true) {
        std::vector<std::string> shopMenu = { "1. 아이템 구매","2. 아이템 판매","3. 인벤토리 확인","4. 상점 나가기" };
        um.PrintSelection(shopMenu);
        int choice=um.InputSelection("=== [ 마을 상점 ] (보유 잼: " + std::to_string(player->GetGold()) + "ZEM) ===");

        if (choice == 1) {
            BuyItem(player, inventoryManager);
        }
        else if (choice == 2) {
            SellItem(player, inventoryManager);
        }
        else if (choice == 3) {
            um.PrintLog("[ 내 가방 확인 ]");
            inventoryManager.PrintAllSummary();
        }
        else if (choice == 4) {
            break;
        }
        else {
            um.PrintLog("[오류] 잘못된 입력입니다. 다시 선택해주세요.");
        }
    }
}

//6. 상점 아이템 반환 함수
std::vector<Item>& ShopManager::GetItems()
{
    return this->shopItems_;
}