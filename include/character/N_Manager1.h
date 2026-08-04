#pragma once
#include "character/Npc.h"

class Manager1 : public NPC {
private:
    int currentQuizIndex; // 현재 출제된 퀴즈의 인덱스 저장용

public:
    Manager1();

    void SpeakEncounter() const override;
    void AskQuiz() override;
    bool CheckAnswer(int playerAnswer); // 정답 판별 함수
    void OnCorrect() override;
    void OnWrong() const override;
    void GiveReward() const override;
};
