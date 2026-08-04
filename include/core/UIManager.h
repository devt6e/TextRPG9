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
private:
    std::vector<int> Offsets = { 0,0 };
public:

    void DisplayDungeonMap(const DungeonManager& dungeon);//ï¿½ï¿½ï¿½ï¿½
    void Gotoxy(int x, int y);//ï¿½ï¿½ï¿½ ï¿½ï¿½Ç¥
    void Gotoxy(std::vector<int> coor);
    void PrintTitle(); //LOSTZEP Å¸ï¿½ï¿½Æ²
    void PrintMain(); //UI Æ²
    void PrintBuilding(); //ï¿½Ê¹ï¿½ ï¿½ï¿½ï¿½ä¸® 
    void PrintTown();//ï¿½Ê¹ï¿½ ï¿½ï¿½ï¿½ä¸® 
    void PrintIntro();//ï¿½Ê¹ï¿½ ï¿½ï¿½ï¿½ä¸®
    void PrintStatus(Player* p);//ï¿½ï¿½ï¿½ï¿½Ã¢
    void PrintInventory(std::vector<string> Inv);
    void PrintMenu(std::vector<std::string> menu);//ï¿½Þ´ï¿½ ï¿½ï¿½ï¿½
    std::string InputSelection(std::string text);//ï¿½Ô·ï¿½
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