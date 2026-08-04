#pragma once
#include "character/Player.h"

class Archer : public Player {
public:
    Archer(std::string Name);

    void Attack() override;
};