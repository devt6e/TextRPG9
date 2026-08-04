#include "character/NPC.h"

NPC::NPC(const std::string& npcName) : name(npcName), isRescued(false) {}

std::string NPC::GetName() const {
    return name;
}

bool NPC::GetIsRescued() const {
    return isRescued;
}

void NPC::SetIsRescued(bool rescued) {
    isRescued = rescued;
}