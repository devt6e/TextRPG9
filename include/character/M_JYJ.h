#pragma once
#include "Monster.h"
#include "core/UIManager.h"

class JYJ : public Monster {
public:
	JYJ(int PlayerLevel);

	void SpeakEncounter() const override;
	void SpeakBattleStart() const override;
	void SpeakVictory() const override;
	void SpeakDefeat() const override;

	void Attack() override;

protected:
	mutable UI um;
};