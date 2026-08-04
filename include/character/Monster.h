#pragma once
#include <string>
#include <iostream>
#include "item/Item.h"
#include "core/UIManager.h"

class Monster {
public:
    Monster(std::string Name, int PlayerLevel);

    virtual ~Monster() {}

    // Getter
    std::string GetName() const { return Name; }
    int GetHp() const { return Hp; }
    int GetMaxHp() const { return MaxHp; }
    int GetPower() const { return Power; }
    int GetDefence() const { return Defence; }
    int GetDropExp() const { return DropExp; }   // 경험치 드랍
    int GetDropGold() const { return DropGold; } // 골드 드랍

    // Setter 
    void SetHp(int Value); // 현재 체력 수정 (Monster.cpp에서 예외처리)


    virtual void Attack() = 0;
    virtual Item* DropItem() { return nullptr; }

protected:
    UI um;
    std::string Name;    // 몬스터 이름 (예: 슬라임)
    int Hp;              // 현재 체력
    int MaxHp;           // 최대 체력
    int Power;           // 공격력
    int Defence = 10;         // 방어력

    // 드랍 관련 스탯
    int DropExp;         // 처치 시 줄 경험치
    int DropGold;        // 처치 시 줄 골드 (아이템 확장용) 
};

// 1. 몬스터쿠키 납치범 (해주님)
class CookieKidnapper : public Monster {
public:
    CookieKidnapper(int PlayerLevel);
    void Attack() override;
    Item* DropItem() override;
};

// 2. ZEM 탈취범 (채원님)
class ZemThief : public Monster {
public:
    ZemThief(int PlayerLevel);
    void Attack() override;
    Item* DropItem() override;
};

// 3. 만년 지각생
class Latecomer : public Monster {
public:
    Latecomer(int PlayerLevel);
    void Attack() override;
    Item* DropItem() override;
};

// 4. 모닝콜 수강생
class MorningCallStudent : public Monster {
public:
    MorningCallStudent(int PlayerLevel);
    void Attack() override;
    Item* DropItem() override;
};