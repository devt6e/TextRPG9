#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Item {
    string name;
    int price;
    int count;              // 현재 중첩 갯수
    int maxStack;           // 최대 중첩 가능 갯수
    string description;     // 상세 설명
    string dropLocation;    // 드랍 위치
};