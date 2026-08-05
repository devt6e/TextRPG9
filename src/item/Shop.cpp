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
    //um.PrintLog("[ 구매 목록 ]");
    um.PrintSelection(shopItems_);
    //for (int i = 0; i < shopItems_.size(); i++) {
    //    cout << i + 1 << ". " << shopItems_[i].Name << " - " << shopItems_[i].Price << "G\n";
    //}
    /*um.PrintMenu();*/

}

// 3. 구매 기능
void ShopManager::BuyItem(Player* player, InventoryManager& inventoryManager) {
    PrintShopItems();

    int buyChoice = um.InputSelection("구매할 아이템의 번호를 입력하세요: ");

    //if (buyChoice == 0) return; //todo 수정하기
    if (buyChoice != 0)
    {
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
}

// 4. 판매 기능
void ShopManager::SellItem(Player* player, InventoryManager& inventoryManager) {
    
    std::vector<std::string> options = { "소비 아이템 팔기","재료 아이템 팔기", "뒤로가기" };
    um.PrintSelection(options);
    int bagChoice = um.InputSelection("어떤 가방의 아이템을 파시겠습니까?");
    
    //inventoryManager.GetConsumableBag().PrintSummary();
    //inventoryManager.GetMaterialBag().PrintSummary();

    Inventory<Item>* selectedBag = nullptr;
    if (bagChoice == 1) {
        selectedBag = &inventoryManager.GetConsumableBag();
    }
    else if (bagChoice == 2) {
        selectedBag = &inventoryManager.GetMaterialBag();
    }
    else {
        um.PrintLog("[system] 잘못된 선택입니다.");
        return;
    }

    um.EraseLog();
    um.PrintLog("[ 판매 목록 ]");
    const std::vector<Item>& sellItems = selectedBag->GetAllItems();
    if (sellItems.empty())
    {
        um.PrintLog("판매할 아이템이 없습니다.");
        return;
    }

    for (size_t index = 0; index < sellItems.size(); ++index)
    {
        const Item& item = sellItems[index];
        if (item.Name == "쿠키")
        {
            um.PrintLog(
                std::to_string(index + 1) + ". " + item.Name +
                "(" + std::to_string(item.Price) + " ZEM, " +
                std::to_string(item.ItemCount) + "개)");
            continue; // ysg: 쿠키의 음수 가격은 실제 판매가가 아닌 전용 상점 이벤트 식별값
        }

        if (item.Price <= 0)
        {
            um.PrintLog(
                std::to_string(index + 1) + ". " + item.Name +
                " (판매 불가, " + std::to_string(item.ItemCount) + "개)");
            continue;
        }

        int unitSellPrice = bagChoice == 1
            ? (item.Price * 60) / 100
            : item.Price;
        um.PrintLog(
            std::to_string(index + 1) + ". " + item.Name +
            " (판매가: " + std::to_string(unitSellPrice) + " ZEM, " +
            std::to_string(item.ItemCount) + "개)");
    } // ysg: 원가 대신 실제 가방별 판매 가격을 목록에 표시

    int sellChoice= um.InputSelection("판매할 아이템 번호: ");
    if (sellChoice == 0) return;

    Item* targetItem = selectedBag->GetItem(sellChoice);

    if (targetItem != nullptr) {
        if (targetItem->Name == "쿠키")
        {
            std::string str = "상인: \"" + targetItem->Name + "? 쿠키를 팔려고하다니...자네 혹시 zep 사람인가?\"";
            um.PrintLog(str);
            return;
        }

        if (targetItem->Price <= 0) {
            std::string str = "상인: \"" + targetItem->Name + "? 그런 잡동사니는 사지 않소!\"";
            um.PrintLog(str);
            return; // 함수 종료 (판매 취소)
        }
        int amount= um.InputSelection("몇 개를 파시겠습니까? (최대 " + std::to_string(targetItem->ItemCount) + "개): ");

        if (amount <= 0) {
            um.PrintLog("[오류] 1개 이상 판매해야 합니다.");
            return;
        }

        if (amount > targetItem->ItemCount) {
            um.PrintLog("[오류] 가진 갯수보다 많이 팔 수 없습니다!");
            return;
        }

        int sellPrice = targetItem->Price * amount;
        if (bagChoice == 1)
        {
            sellPrice = (sellPrice * 60) / 100; // ysg: 구매 가능한 소비 아이템은 구매가의 60%로 판매
        }
        // ysg: 몬스터에게서 획득하는 재료 아이템은 설정 가격의 100%로 판매

        if (selectedBag->RemoveItem(sellChoice, amount)) {
            player->SetGold(player->GetGold() + sellPrice);
            um.PrintLog("[System] " + std::to_string(sellPrice) + "ZEM을 획득했습니다!");
        }
        //selectedBag->PrintSummary();
    }
}

// 5. 상점 메인
void ShopManager::EnterShop(Player* player, InventoryManager& inventoryManager) {
    while (true) {
        um.PrintStatus(player); // ysg: 구매·판매 후 오른쪽 스탯창의 보유 ZEM을 즉시 갱신
        std::vector<std::string> shopMenu = { "아이템 구매","아이템 판매","인벤토리 확인","뒤로가기" };
        um.PrintSelection(shopMenu);
        int choice=um.InputSelection("입력(보유 잼: " + std::to_string(player->GetGold()) + "ZEM): ");

        if (choice == 1) {
            BuyItem(player, inventoryManager);
        }
        else if (choice == 2) {
            SellItem(player, inventoryManager);
        }
        else if (choice == 3) {
            inventoryManager.PrintAllSummary();
            um.WaitForAnyKey("가방 확인을 마치려면 아무 키나 입력하세요: "); // ysg: 상점 메뉴가 가방 목록을 즉시 덮어쓰지 않도록 대기
        }
        else if (choice == 0) {
            um.EraseStat();
            um.PrintStatus(player);
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
