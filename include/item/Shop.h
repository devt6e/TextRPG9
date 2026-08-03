#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "item/Item.h"
#include "item/Inventory.h"
#include "character/Player.h"

using namespace std;

//int GetGold() const { return Gold; }            // 현재 골드 조회
//void SetGold(int Value) { Gold = Value; }       // 골드량 수정

class ShopManager {
private:
	vector<Item> shopItems_;

public:
	ShopManager() {
        shopItems_.push_back(HpPotion());
        shopItems_.push_back(TempABPotion());
        shopItems_.push_back(MpPotion());
	}

    void PrintShopItems() {
        cout << "\n[ 구매 목록 ]\n";
        for (int i = 0; i < shopItems_.size(); i++) {
            cout << i + 1 << ". " << shopItems_[i].Name << " - " << shopItems_[i].Price << "G\n";
        }
    }

    void BuyItem(Player* player, InventoryManager& inventoryManager) {
        PrintShopItems();

        cout << "살 아이템 번호 (취소 0): ";
        int buyChoice;
        cin >> buyChoice;

        if (buyChoice == 0) return;

        if (buyChoice < 1 || buyChoice > shopItems_.size()) {
            cout << "[오류] 잘못된 번호입니다.\n";
            return;
        }

        Item buyItem = shopItems_[buyChoice - 1];
        if (player->GetGold() >= buyItem.Price) {
            player->SetGold(player->GetGold() - buyItem.Price);

            inventoryManager.AddConsumable(buyItem);
            cout << "[System] " << buyItem.Name << "을(를) 구매했습니다!\n";
        }
        else {
            cout << "[System] 골드가 부족합니다!\n";
        }
    }

    void SellItem(Player* player, InventoryManager& inventoryManager) {
        cout << "\n어떤 가방의 아이템을 파시겠습니까?\n";
        cout << "1. 소비 아이템 팔기\n2. 재료 아이템 팔기\n선택: ";
        int bagChoice;
        cin >> bagChoice;

        Inventory<Item>* selectedBag = nullptr;
        if (bagChoice == 1) {
            selectedBag = &inventoryManager.GetConsumableBag();
        }
        else if (bagChoice == 2) {
            selectedBag = &inventoryManager.GetMaterialBag();
        }
        else {
            cout << "[오류] 잘못된 선택입니다.\n";
            return;
        }

        selectedBag->PrintSummary();

        cout << "팔 아이템 번호 (취소 0): ";
        int sellChoice;
        cin >> sellChoice;

        if (sellChoice == 0) return;

        Item* targetItem = selectedBag->GetItem(sellChoice);

        if (targetItem != nullptr) {
            cout << "몇 개를 파시겠습니까? (최대 " << targetItem->ItemCount << "개): ";
            int amount;
            cin >> amount;

            if (amount <= 0) {
                cout << "[오류] 1개 이상 판매해야 합니다.\n";
                return;
            }

            if (amount > targetItem->ItemCount) {
                cout << "[오류] 가진 갯수보다 많이 팔 수 없습니다!\n";
                return;
            }

            int sellPrice = (targetItem->Price * amount * 60) / 100;

            if (selectedBag->RemoveItem(sellChoice, amount)) {
                player->SetGold(player->GetGold() + sellPrice);
                cout << "[System] " << sellPrice << "G를 획득했습니다!\n";
            }
        }
    }

    void EnterShop(Player* player, InventoryManager& inventoryManager) {
        while (true) {
            cout << "\n=== [ 마을 상점 ] (보유 골드: " << player->GetGold() << "G) ===\n";
            cout << "1. 아이템 구매\n";
            cout << "2. 아이템 판매\n";
            cout << "3. 인벤토리 확인\n";
            cout << "4. 상점 나가기\n";
            cout << "선택: ";

            int choice;
            cin >> choice;

            if (choice == 1) {
                BuyItem(player, inventoryManager);
            }
            else if (choice == 2) {
                SellItem(player, inventoryManager);
            }
            else if (choice == 3) {
                cout << "\n[ 내 가방 확인 ]\n";
                inventoryManager.PrintAllSummary();
            }
            else if (choice == 4) {
                break;
            }
            else {
                cout << "[오류] 잘못된 입력입니다. 다시 선택해주세요.\n";
            }
        }
    }
};