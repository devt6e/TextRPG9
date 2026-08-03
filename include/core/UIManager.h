#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <vector>

class DungeonManager;//던전

class UI
{

public:

    void DisplayDungeonMap(const DungeonManager& dungeon);//던전

    void MainTitle(); //LOSTZEP 타이틀
    void MiniTitle(); //미니 타이틀
    void ZepBuilding(); //초반 스토리 
    void NBCTown(); //초반 스토리 
    void PrintStatus(std::string name, std::string job, int level, int hp, int maxhp, int mp, int maxmp, int power, int defense);//스탯창
    void PrintMenu(std::vector<std::string> Pvector);//메뉴 출력
    std::string InputSelection(std::string text);//입력
    void PrintBattle(std::string MonsterName, bool IsWin);

    //NPC 아스키아트
    void NPC_M();
    void NPC_K();

    
};