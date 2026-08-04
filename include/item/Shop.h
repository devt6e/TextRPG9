#pragma once

#include <vector>
#include "item/Item.h"
#include "item/Inventory.h"
#include "character/Player.h"

using namespace std;

class ShopManager {
private:
    vector<Item> shopItems_;
    UI um; //UI Manager -- 작업자: 김태형 

public:
    ShopManager();
    vector<Item> GetItems() const;  //김태형
    void PrintShopItems();
    void BuyItem(Player* player, InventoryManager& inventoryManager);
    void SellItem(Player* player, InventoryManager& inventoryManager);
    void EnterShop(Player* player, InventoryManager& inventoryManager);
};