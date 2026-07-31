#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Item {
    string name;            // 아이템 이름
    int price;              // 아이템 가격
    int count;              // 현재 중첩 갯수
    int maxStack;           // 최대 중첩 가능 갯수
    string description;     // 상세 설명
    string dropLocation;    // 드랍 위치
};

template <typename T>
bool CompareByName(const T& a, const T& b) {
    return a.name < b.name;
}

template <typename T>
bool CompareByPrice(const T& a, const T& b) {
    return a.price > b.price;
}

template <typename T>
class Inventory {
private:
    vector<T> items_;
    int capacity_;    // 현재 인벤토리 최대 칸 수

public:
    Inventory(int startCapacity = 10) {
        capacity_ = startCapacity;
    }

    // 인벤토리 자동 확장 기능
    void ExpandCapacity() {
        capacity_ += 5; // 한 번에 5칸씩 증가
        cout << "[System] 인벤토리 가방이 확장되었습니다! (현재 최대 " << capacity_ << "칸)\n";
    }

    void SortByName() {
        sort(items_.begin(), items_.end(), CompareByName<T>);
        cout << "[System] 아이템을 이름순으로 정렬했습니다.\n";
    }

    void SortByPrice() {
        sort(items_.begin(), items_.end(), CompareByPrice<T>);
        cout << "[System] 아이템을 금액순으로 정렬했습니다.\n";
    }
};