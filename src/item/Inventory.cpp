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
	um.EraseLog();
	um.PrintLog("[ 내 가방 확인 ]");

	auto printBag = [&](const std::string& title, const std::vector<Item>& items)
	{
		um.PrintLog(title);
		if (items.empty())
		{
			um.PrintLog("  가방이 비어 있습니다.");
			return;
		}

		for (size_t index = 0; index < items.size(); ++index)
		{
			const Item& item = items[index];
			um.PrintLog(
				"  " + std::to_string(index + 1) + ". " + item.Name +
				" (" + std::to_string(item.Price) + " ZEM, " +
				std::to_string(item.ItemCount) + "개)");
		}
	};

	printBag("[ 소비 아이템 ]", consumableBag_.GetAllItems());
	printBag("[ 재료 아이템 ]", materialBag_.GetAllItems()); // ysg: 좁은 스탯창 대신 로그 영역에 가방 목록 출력
}
