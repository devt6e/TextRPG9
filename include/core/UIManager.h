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

    void DisplayDungeonMap(const DungeonManager& dungeon);//����
    void Gotoxy(int x, int y);//��� ��ǥ
    void PrintTitle(); //LOSTZEP Ÿ��Ʋ
    void PrintMain(); //UI Ʋ
    void PrintBuilding(); //�ʹ� ���丮 
    void PrintTown();//�ʹ� ���丮 
    void PrintIntro();//�ʹ� ���丮
    void PrintStatus(Player* p);//����â
    void PrintInventory(std::vector<string> Inv);
    void PrintMenu(std::vector<std::string> menu);//�޴� ���
    std::string InputSelection(std::string text);//�Է�
    void PrintMessage(const std::string&);


    //NPC 아스키아트
    void NPC_M();
    void NPC_K();

    
};