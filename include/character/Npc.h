#pragma once
#include <string>
#include <iostream>

class NPC {
protected:
    std::string name;
    bool isRescued; // 감금 상태 여부 (false: 감금됨, true: 구출됨)

public:
    NPC(const std::string& npcName);
    virtual ~NPC() = default;

    std::string GetName() const;
    bool GetIsRescued() const;
    void SetIsRescued(bool rescued);

    virtual void SpeakEncounter() const = 0; // 조우시
    virtual void AskQuiz() const = 0;        // 퀴즈
    virtual void OnCorrect() const = 0;      // 정답
    virtual void OnWrong() const = 0;        // 실패
    virtual void GiveReward() const = 0;     // 보상
};