#pragma once
#include "character/Player.h"

class Warrior : public Player {
public:
    Warrior(std::string Name);

    void Attack() override;
    int Skill() override;
};

