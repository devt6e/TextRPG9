#pragma once
#include "Player.h"

class Warrior : public Player {
public:
    Warrior(std::string Name);

    void Attack() override;
};

