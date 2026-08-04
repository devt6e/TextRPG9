#pragma once
#include "character/Player.h"

class Magician : public Player {
public:
    Magician(std::string Name);

    void Attack() override;
};