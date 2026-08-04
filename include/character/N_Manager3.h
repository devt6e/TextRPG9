#pragma once
#include "character/Npc.h"
#include "core/UIManager.h"

class Manager3 : public NPC {
private:
    int currentQuizIndex;

public:
    Manager3();

    void SpeakEncounter() const override;
    void AskQuiz() override;
    bool CheckAnswer(int playerAnswer); // 정답 판별 함수
    void OnCorrect() override;
    void OnWrong() const override;
    void GiveReward() const override;
protected:
    mutable UI um;
};
