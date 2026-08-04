#pragma once
#include <string>
#include <iostream>

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

protected:
    std::string Name;    // 몬스터 이름 (예: 슬라임)
    int Hp;              // 현재 체력
    int MaxHp;           // 최대 체력
    int Power;           // 공격력
    int Defence = 10;         // 방어력

    // 드랍 관련 스탯
    int DropExp;         // 처치 시 줄 경험치
    int DropGold;        // 처치 시 줄 골드 (아이템 확장용) 
};