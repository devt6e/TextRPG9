#pragma once
#include "Monster.h"
#include "item/Item.h"
#include "core/UIManager.h"


class Slime : public Monster {
public:
	Slime(int PlayerLevel);

	void SpeakEncounter() const override;
	void SpeakBattleStart() const override;
	void SpeakVictory() const override;
	void SpeakDefeat() const override;

	void Attack() override;
	Item* DropItem() override;
protected:
	mutable UI um;
};