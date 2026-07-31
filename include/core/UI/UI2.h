#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <vector>


class UI
{
private:
    int RoomChoice;
    int MenuChoice;
    int PlayerLocation = 0;
    int CurrentFloor = 1;
    std::vector<std::string> MainMenu = { "던전","인벤토리","제작소","게임종료"};
    std::vector<std::string> CraftMenu = { "레시피 전체 조회","레시피 검색","제작" };

public:
    void MainTitle();
    void MiniTitle();
    void ZepBuilding();
    void NBCTown();
    void Intro();
    void Status();
    void Dungeon();
    void PlayerMenu();
    void Maps1();
    void Maps1_1();
    void Maps1_2();
    void Maps1_3();
    void Maps1_4();
    void Maps1_5();
    void Maps2();
    void Maps2_1();
    void Maps2_2();
    void Maps2_3();
    void Maps2_4();
    void Maps2_5();
    void NPC_M();
    void NPC_K();
    
    

};