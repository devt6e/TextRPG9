#pragma once
#include "Player.h"

class Magician : public Player {
public:
    Magician(std::string Name);

    void Attack() override;
};