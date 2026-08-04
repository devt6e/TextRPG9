#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include"character/Player.h"

class DungeonManager;//던전

class UI
{

public:


    void DisplayDungeonMap(const DungeonManager& dungeon);//????
    void Gotoxy(int x, int y);//??? ???
    void PrintTitle(); //LOSTZEP ????
    void PrintMain(); //UI ?
    void PrintBuilding(); //??? ???? 
    void PrintTown();//??? ???? 
    void PrintIntro();//??? ????
    void PrintStatus(Player* p);//?????
    void PrintMenu(std::vector<std::string> menu);//??? ???
    std::string InputSelection(std::string text);//???
    void PrintMessage(const std::string&);

    void PrintDungeonMoveOptions(
        bool canMoveUp,
        bool canMoveDown,
        bool canMoveLeft,
        bool canMoveRight);


    //NPC 아스키아트
    void NPC_M();
    void NPC_K();

    
};