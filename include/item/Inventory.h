#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "../../include/item/Item.h"

//string Name;				// 아이템 이름
//string ItemDescription;		// 아이템 설명
//string ItemDropLocation;	// 아이템 드롭 장소
//int Price;					// 아이템 가격
//int ItemCount;				// 아이템 갯수
//int ItemMaxStack;			// 아이템 최대 갯수

using namespace std;

<<<<<<< Updated upstream
struct Item {
    string name;            // 아이템 이름
    int price;              // 아이템 가격
    int count;              // 현재 중첩 갯수
    int maxStack;           // 최대 중첩 가능 갯수
    string description;     // 상세 설명
    string dropLocation;    // 드랍 위치
};

=======
>>>>>>> Stashed changes
template <typename T>
bool CompareByName(const T& a, const T& b) {
    return a.Name < b.Name;
}

template <typename T>
bool CompareByPrice(const T& a, const T& b) {
    return a.Price > b.Price;
}

template <typename T>
class Inventory {
private:
    vector<T> items_;
    int capacity_;    // 현재 인벤토리 최대 칸 수

public:
    vector<T>& GetAllItems() {
        return items_;
    }

    Inventory(int StartCapacity = 10) {
        capacity_ = StartCapacity;
    }

    void ExpandCapacity() {
        capacity_ += 5; // 한 번에 5칸씩 증가
        cout << "[System] 인벤토리 가방이 확장되었습니다! (현재 최대 " << capacity_ << "칸)\n";
    }

    void AddItem(T newItem) {
        for (int i = 0; i < items_.size(); i++) {
            if (items_[i].Name == newItem.Name) {
                int SpaceLeft = items_[i].ItemMaxStack - items_[i].ItemCount;

                if (SpaceLeft > 0) {
                    if (SpaceLeft >= newItem.ItemCount) {
                        items_[i].ItemCount += newItem.ItemCount;
                        cout << "-> " << newItem.Name << " " << newItem.ItemCount << "개를 기존 슬롯에 합쳤습니다.\n";
                        return;
                    }
                    else {
                        items_[i].ItemCount += SpaceLeft;
                        newItem.ItemCount -= SpaceLeft;
                        cout << "-> " << newItem.Name << " " << SpaceLeft << "개를 합치고 나머지는 새 슬롯에 넣습니다.\n";
                    }
                }
            }
        }

        if (items_.size() >= capacity_) {
            ExpandCapacity();
        }

        items_.push_back(newItem);
        cout << "-> " << newItem.Name << " " << newItem.ItemCount << "개를 새 슬롯에 획득했습니다!\n";
    }

    void SortByName() {
        sort(items_.begin(), items_.end(), CompareByName<T>);
        cout << "[System] 아이템을 이름순으로 정렬했습니다.\n";
    }

    void SortByPrice() {
        sort(items_.begin(), items_.end(), CompareByPrice<T>);
        cout << "[System] 아이템을 금액순으로 정렬했습니다.\n";
    }

    void PrintSummary() {
        cout << "\n========== [ 인벤토리 (" << items_.size() << "/" << capacity_ << ") ] ==========\n";
        if (items_.empty()) {
            cout << "가방이 텅 비어있습니다.\n";
        }
        else {
            for (int i = 0; i < items_.size(); i++) {
                cout << i + 1 << ". " << items_[i].Name
                    << " (x" << items_[i].ItemCount << ") - "
                    << items_[i].Price << "G\n";
            }
        }
        cout << "==============================================\n";
    }
};

class InventoryManager {
private:
    Inventory<Item> consumableBag_;
    Inventory<Item> materialBag_;

public:
    void AddConsumable(Item item) {
        cout << "[소비 가방] ";
        consumableBag_.AddItem(item);
    }

    void AddMaterial(Item item) {
        cout << "[재료 가방] ";
        materialBag_.AddItem(item);
    }
};