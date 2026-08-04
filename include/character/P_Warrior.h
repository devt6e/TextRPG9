#pragma once
#include "character/Player.h"
#include "core/UIManager.h"

class Warrior : public Player {
public:
    Warrior(std::string Name);

    void Attack() override;
    int Skill() override;
protected:
    mutable UI um;
};

