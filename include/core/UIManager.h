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

    void DisplayDungeonMap(const DungeonManager& dungeon);//던전
    void Gotoxy(int x, int y);//출력 좌표
    void PrintTitle(); //LOSTZEP 타이틀
    void PrintMain(); //UI 틀
    void PrintBuilding(); //초반 스토리 
    void NBCTown(); //초반 스토리 
    void PrintStatus(Player*& p);//스탯창
    void PrintMenu(std::vector<std::string> menu);//메뉴 출력
    std::string InputSelection(std::string text);//입력

    //NPC 아스키아트
    void NPC_M();
    void NPC_K();

    
};