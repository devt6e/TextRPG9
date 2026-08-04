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

    // 상황별 대사 가상 함수 추가
    virtual void SpeakEncounter() const = 0; // 조우 시
    virtual void SpeakBattleStart() const = 0; // 전투 시작 시
    virtual void SpeakVictory() const = 0;    // 플레이어 승리 시 (몬스터의 유언)
    virtual void SpeakDefeat() const = 0;     // 플레이어 패배 시 (몬스터의 승리 대사)

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
