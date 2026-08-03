#pragma once
#include "Player.h"

class Thief : public Player {
public:
    Thief(std::string Name);

    void Attack() override;
};


