#pragma once
#include <string>

// 플레이어 기본 클래스 (직업 클래스들의 부모 클래스)
class Player {
public: 
    // 이름, 체력, 마나, 공격력, 방어력을 받아 플레이어 생성
    Player(std::string Name);

    // 가상 소멸자 (자식 클래스 동적 할당 해제용)
    virtual ~Player() {}  

    // Getter
    std::string GetName() const { return Name; }    // 이름 조회
    std::string GetJob() const { return Job; }      // 직업 조회
    int GetLevel() const { return Level; }          // 현재 레벨 조회
    int GetHp() const { return Hp; }                // 현재 체력 조회
    int GetMp() const { return Mp; }                // 현재 마나 조회
    int GetPower() const { return Power; }          // 현재 공격력 조회
    int GetDefence() const { return Defence; }      // 현재 방어력 조회
    int GetExp() const { return Exp; }              // 현재 경험치 조회
    int GetMaxExp() const { return MaxExp; }        // 레벨업 필요 경험치 조회 (100 고정)

    // Setter
    void SetHp(int Value) { Hp = Value; }           // 현재 체력 수정
    void SetMp(int Value) { Mp = Value; }           // 현재 마나 수정
    void SetPower(int Value) { Power = Value; }     // 현재 공격력 수정
    void SetDefence(int Value) { Defence = Value; } // 현재 방어력 수정
    void SetExp(int Value) { Exp = Value; }         // 경험치 수정
    void SetJob(std::string Value) { Job = Value; } // 직업 명칭 수정?

    virtual void Attack() = 0;

protected: // 초기 스탯
    std::string Name;   // 이름
    std::string Job;        // 직업 (기본값: 초보자?)
    int Level = 1 ;         // 레벨 (초기값: 1)
    int Hp = 200;             // 체력 (초기값: 200)
    int Mp = 100;             // 마나
    int Power = 30;          // 공격력 (초기값: 30)
    int Defence = 20;        // 방어력
    int Exp = 0;            // 현재 경험치 (초기값: 0)
    int MaxExp = 100;         // 레벨업에 필요 경험치 (기본값: 100)
};
