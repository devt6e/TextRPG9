#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "item/Item.h"
//#include "character/Player.h"

using namespace std;

class ShopManager {
private:
	vector<Item> shopItems_;

public:

    int tempTestGold = 10000; //임시 지갑

	ShopManager() {
        shopItems_.push_back(HpPotion());
        shopItems_.push_back(TempABPotion());
	}

    void BuyItem(Player* player, InventoryManager& inventoryManager) {
        cout << "\n[ 구매 목록 ]\n";
        for (int i = 0; i < shopItems_.size(); i++) {
            cout << i + 1 << ". " << shopItems_[i].Name << " - " << shopItems_[i].Price << "G\n";
        }

        cout << "살 아이템 번호 (취소 0): ";
        int buyChoice;
        cin >> buyChoice;

        if (buyChoice == 0) return;

        Item buyItem = shopItems_[buyChoice - 1];
        //player->Gold ---> tempTestGold(임시지갑)
        if (tempTestGold >= buyItem.Price) {
            tempTestGold -= buyItem.Price;

            inventoryManager.AddConsumable(buyItem);
            cout << "[System] " << buyItem.Name << "을(를) 구매했습니다!\n";
        }
        else {
            cout << "[System] 골드가 부족합니다!\n";
        }
    }
};