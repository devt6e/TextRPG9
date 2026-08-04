#pragma once
#include "character/Npc.h"

class Manager4 : public NPC {
private:
    int currentQuizIndex;

public:
    Manager4();

    void SpeakEncounter() const override;
    void AskQuiz() const override;
    bool CheckAnswer(int playerAnswer); // 정답 판별 함수
    void OnCorrect() override;
    void OnWrong() const override;
    void GiveReward() const override;
};