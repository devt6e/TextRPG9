#include "Item/Inventory.h"

Inventory<Item>& InventoryManager::GetConsumableBag() {
	return consumableBag_;
}

Inventory<Item>& InventoryManager::GetMaterialBag() {
	return materialBag_;
}

void InventoryManager::AddConsumable(Item item) {
	//std::cout << "[소비 가방] ";
	consumableBag_.AddItem(item);
}

void InventoryManager::AddMaterial(Item item) {
	//std::cout << "[재료 가방] ";
	materialBag_.AddItem(item);
}

void InventoryManager::PrintAllSummary() {
	//std::cout << "\n======== [ 전체 인벤토리 ] ========";
	//std::cout << "▶ [ 소비 아이템 ]";
	um.PrintInventory(consumableBag_.GetAllItems(),"[ 소비 아이템 ]", 0);
	//consumableBag_.PrintSummary();

	um.PrintInventory(materialBag_.GetAllItems(), "[ 재료 아이템 ]", 2);
	//materialBag_.PrintSummary();
	//std::cout << "\n▶ [ 재료 아이템 ]";
	//materialBag_.PrintSummary();
	//std::cout << "===================================\n";
}
