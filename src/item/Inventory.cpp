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
