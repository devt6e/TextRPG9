#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "item/Item.h"

//string Name;				// 아이템 이름
//string ItemDescription;		// 아이템 설명
//string ItemDropLocation;	// 아이템 드롭 장소
//int Price;					// 아이템 가격
//int ItemCount;				// 아이템 갯수
//int ItemMaxStack;			// 아이템 최대 갯수

using namespace std;

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
    int capacity_;    // ���� �κ��丮 �ִ� ĭ ��

public:

    vector<T>& GetAllItems() {
        return items_;
    }

    Inventory(int StartCapacity = 10) {
        capacity_ = StartCapacity;
    }

    void ExpandCapacity() {
        capacity_ += 5; // �� ���� 5ĭ�� ����
        cout << "[System] �κ��丮 ������ Ȯ��Ǿ����ϴ�! (���� �ִ� " << capacity_ << "ĭ)\n";
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
        cout << "[System] �������� �̸������� �����߽��ϴ�.\n";
    }

    void SortByPrice() {
        sort(items_.begin(), items_.end(), CompareByPrice<T>);
        cout << "[System] �������� �ݾ׼����� �����߽��ϴ�.\n";
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

    bool ConsumeItem(int index) {
        int realIndex = index - 1;

        if (realIndex < 0 || realIndex >= items_.size()) {
            cout << "[오류] 사용할 수 없는 슬롯입니다.\n";
            return false;
        }

        items_[realIndex].ItemCount--;
        cout << "-> " << items_[realIndex].Name << "을(를) 사용했습니다! (남은 갯수: " << items_[realIndex].ItemCount << ")\n";

        if (items_[realIndex].ItemCount <= 0) {
            cout << "[System] " << items_[realIndex].Name << "을(를) 모두 소모하여 인벤토리에서 비웁니다.\n";
            items_.erase(items_.begin() + realIndex);
        }

        return true;
    }

    bool HasEnoughItem(string targetName, int requiredCount) {
        auto it = find_if(items_.begin(), items_.end(), [&](const T& item) {
            return item.Name == targetName;
            });

        if (it == items_.end() || it->ItemCount < requiredCount) {
            return false;
        }

        return true;
    }

    T* GetItem(int index) {
        int RealIndex = index - 1;
        if (RealIndex < 0 || RealIndex >= items_.size()) {
            return nullptr;
        }
        return &items_[RealIndex];
    }

    bool RemoveItem(int index, int amount) {
        int RealIndex = index - 1;

        if (RealIndex < 0 || RealIndex >= items_.size()) {
            cout << "[오류] 잘못된 슬롯입니다.\n";
            return false;
        }

        if (items_[RealIndex].ItemCount < amount) { 
            cout << "[오류] 가진 갯수보다 많이 팔 수 없습니다!\n";
            return false;
        }

        items_[RealIndex].ItemCount -= amount;

        if (items_[RealIndex].ItemCount <= 0) {
            items_.erase(items_.begin() + RealIndex);
        }

        return true;
    }
};

class InventoryManager {
private:
    Inventory<Item> consumableBag_;
    Inventory<Item> materialBag_;

public:

    Inventory<Item>& GetConsumableBag() { return consumableBag_; }
    Inventory<Item>& GetMaterialBag() { return materialBag_; }

    void AddConsumable(Item item) {
        cout << "[소비 가방] ";
        consumableBag_.AddItem(item);
    }

    void AddMaterial(Item item) {
        cout << "[재료 가방] ";
        materialBag_.AddItem(item);
    }

    void PrintAllSummary() {
        cout << "\n======== [ 전체 인벤토리 ] ========";
        cout << "\n\n▶ [ 소비 아이템 ]";
        consumableBag_.PrintSummary();

        cout << "\n▶ [ 재료 아이템 ]";
        materialBag_.PrintSummary();
        cout << "===================================\n";
    }
};
