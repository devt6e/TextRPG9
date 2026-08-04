#pragma once
#include "Monster.h"


class husband : public Monster {
public:
	husband(int PlayerLevel);

	void SpeakEncounter() const override;
	void SpeakBattleStart() const override;
	void SpeakVictory() const override;
	void SpeakDefeat() const override;

	void Attack() override;
};