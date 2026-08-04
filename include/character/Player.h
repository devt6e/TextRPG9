#pragma once
#include <string>
#include <iostream>
#include "item/Item.h"

//Windows의 인쇄 작업 관련 매크로 강제 해제
#undef SetJob
#undef GetJob

// 플레이어 기본 클래스 (직업 클래스들의 부모 클래스)
class Player {
public: 
    // 이름, 체력, 마나, 공격력, 방어력을 받아 플레이어 생성
    Player(std::string Name) : Name(Name) {}

    // 가상 소멸자 (자식 클래스 동적 할당 해제용)
    virtual ~Player() {}

    int TempAttackBuff = 0;  // 공격력 임시 버프
    int TempDEFBuff = 0; // 방어력 임시 버프

    // Getter
    std::string GetName() const { return Name; }    // 이름 조회
    std::string GetJob() const { return Job; }      // 직업 조회
    int GetLevel() const { return Level; }          // 현재 레벨 조회
    int GetHp() const { return Hp; }                // 현재 체력 조회
    int GetMaxHp() const { return MaxHp; }              // 최대 체력...
    int GetMp() const { return Mp; }                // 현재 마나 조회
    int GetMaxMp() const { return MaxMp; }              // 최대 마나...
    int GetPower() const { return Power; }          // 현재 공격력 조회
    int GetDefence() const { return Defence; }      // 현재 방어력 조회
    int GetExp() const { return Exp; }              // 현재 경험치 조회
    int GetMaxExp() const { return MaxExp; }        // 레벨업 필요 경험치 조회 (100 고정)
    int GetTempAttackBuff() const { return TempAttackBuff; } //임시 버프 수치 조회
    int GetTotalPower() const { return Power + TempAttackBuff; } //(기본 공격력 + 버프)
    int GetTempDEFBuff() const { return TempDEFBuff; }
    int GetTotalDEF() const { return Defence + TempDEFBuff; }
    int GetGold() const { return Gold; }            // 현재 골드 조회

    // Setter
    void SetHp(int Value);                          // 현재 체력 수정 (Player.cpp에서 예외처리)
    void SetMaxHp(int Value) { MaxHp = Value; }         // 최대 체력 수정
    void SetMp(int Value);                          // 현재 마나 수정 (Player.cpp에서 예외처리)
    void SetMaxMp(int Value) { MaxMp = Value; }         // 최대 마나 수정
    void SetPower(int Value) { Power = Value; }     // 현재 공격력 수정
    void SetDefence(int Value) { Defence = Value; } // 현재 방어력 수정
    void SetLevel(int Value) { Level = Value; }         // 레벨 수정
    void SetExp(int Value) { Exp = Value; }         // 경험치 수정
    void SetJob(std::string Value) { Job = Value; } // 직업 명칭 수정?

    void SetGold(int Value) { Gold = Value; }       // 골드량 수정

    void AddExp(int Amount); // 경험치 획득 함수 추가

    virtual void Attack() = 0;
    void ResetBuff() { TempAttackBuff = 0; TempDEFBuff = 0; } // 임시 버프 수치를 0으로 초기화

protected: // 초기 스탯
    std::string Name;   // 이름
    std::string Job = "초보자";        // 직업 (기본값: 초보자?)
    int Level = 1 ;         // 레벨 (초기값: 1)
    int Hp = 200;             // 체력 (초기값: 200)
    int MaxHp = 200;
    int Mp = 100;             // 마나
    int MaxMp = 100;
    int Power = 30;          // 공격력 (초기값: 30)
    int Defence = 20;        // 방어력
    int Exp = 0;            // 현재 경험치 (초기값: 0)
    int MaxExp = 100;         // 레벨업에 필요 경험치 (기본값: 100)
    int Gold = 0; 
};
