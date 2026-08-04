#pragma once

#include <vector>
#include "item/Item.h"
#include "item/Inventory.h"
#include "character/Player.h"

using namespace std;

class ShopManager {
private:
    vector<Item> shopItems_;

public:
    ShopManager();

    void PrintShopItems();
    void BuyItem(Player* player, InventoryManager& inventoryManager);
    void SellItem(Player* player, InventoryManager& inventoryManager);
    void EnterShop(Player* player, InventoryManager& inventoryManager);
};