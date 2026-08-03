#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include"character/Player.h"

class DungeonManager;//ë˜ì „

class UI
{

public:

<<<<<<< HEAD
    void DisplayDungeonMap(const DungeonManager& dungeon);//´øÀü
    void Gotoxy(int x, int y);//Ãâ·Â ÁÂÇ¥
    void PrintTitle(); //LOSTZEP Å¸ÀÌÆ²
    void PrintMain(); //UI Æ²
    void PrintBuilding(); //ÃÊ¹İ ½ºÅä¸® 
    void PrintTown();//ÃÊ¹İ ½ºÅä¸® 
    void PrintIntro();//ÃÊ¹İ ½ºÅä¸®
    void PrintStatus(Player* p);//½ºÅÈÃ¢
    void PrintMenu(std::vector<std::string> menu);//¸Ş´º Ãâ·Â
    std::string InputSelection(std::string text);//ÀÔ·Â
    void PrintMessage(const std::string&);
=======
    void DisplayDungeonMap(const DungeonManager& dungeon);//ë˜ì „
    void Gotoxy(int x, int y);//ì¶œë ¥ ì¢Œí‘œ
    void PrintTitle(); //LOSTZEP íƒ€ì´í‹€
    void PrintMain(); //UI í‹€
    void PrintBuilding(); //ì´ˆë°˜ ìŠ¤í† ë¦¬ 
    void NBCTown(); //ì´ˆë°˜ ìŠ¤í† ë¦¬ 
    void PrintStatus(Player*& p);//ìŠ¤íƒ¯ì°½
    void PrintMenu(std::vector<std::string> menu);//ë©”ë‰´ ì¶œë ¥
    std::string InputSelection(std::string text);//ì…ë ¥
>>>>>>> main

    //NPC ì•„ìŠ¤í‚¤ì•„íŠ¸
    void NPC_M();
    void NPC_K();

    
};