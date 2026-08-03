#pragma once
#include <string>

// 플레이어 기본 클래스 (직업 클래스들의 부모 클래스)
class Player {
public: 
    // 이름, 체력, 마나, 공격력, 방어력을 받아 플레이어 생성
    Player(std::string Name, int Hp, int Mp, int Power, int Defence);

    // 가상 소멸자 (자식 클래스 동적 할당 해제용)
    virtual ~Player() {}  

    // Getter
    std::string GetName() const { return Name; }    // 이름 반환
    std::string GetJob() const { return Job; }      // 직업 반환
    int GetLevel() const { return Level; }          // 현재 레벨 반환
    int GetHp() const { return Hp; }                // 현재 체력 반환
    int GetMp() const { return Mp; }                // 현재 마나 반환
    int GetPower() const { return Power; }          // 현재 공격력 반환
    int GetDefence() const { return Defence; }      // 현재 방어력 반환
    int GetExp() const { return Exp; }              // 현재 경험치 반환
    int GetMaxExp() const { return MaxExp; }        // 레벨업 필요 경험치 반환

    // Setter
    void setHp(int Value) { Hp = Value; }           // 현재 체력 설정
    void setMp(int Value) { Mp = Value; }           // 현재 마나 설정
    void setPower(int Value) { Power = Value; }     // 현재 공격력 설정
    void setDefence(int Value) { Defence = Value; } // 현재 방어력 설정
    void SetJob(std::string Value) { Job = Value; }

    virtual void Attack() = 0;
    void GainExp(int amount);

protected: // 초기 스탯
    std::string Name;   // 이름
    std::string Job;    // 직업 (기본값: 초보자?)
    int Level;          // 레벨 (초기값: 1)
    int Hp;             // 체력 (초기값: 200)
    int Mp;             // 마나
    int Power;          // 공격력 (초기값: 30)
    int Defence;        // 방어력
    int Exp;            // 현재 경험치 (초기값: 0)
    int MaxExp;         // 레벨업에 필요 경험치 (기본값: 100)
};
