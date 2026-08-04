#pragma once
#include "Monster.h"


class Morning : public Monster {
public:
	Morning(int PlayerLevel);

	void SpeakEncounter() const override;
	void SpeakBattleStart() const override;
	void SpeakVictory() const override;
	void SpeakDefeat() const override;

	void Attack() override;
};