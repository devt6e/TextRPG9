#pragma once
#include "character/Player.h"
#include "core/UIManager.h"

class Magician : public Player {
public:
    Magician(std::string Name);

    void Attack() override;
    int Skill() override;
protected:
    mutable UI um;
};