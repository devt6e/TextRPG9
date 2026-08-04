#pragma once
#include "character/Player.h"
#include "core/UIManager.h"

class Thief : public Player {
public:
    Thief(std::string Name);

    void Attack() override;
    int Skill() override;
protected:
    mutable UI um;
};


