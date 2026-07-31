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

public:
    void MainTitle();//LOSTZEP 타이틀
    void MiniTitle();//미니 타이틀
    void ZepBuilding(); //초반 스토리 
    void NBCTown(); //초반 스토리 
    void Status();
    void Dungeon();//예비
    void PrintMenu(std::vector<std::string> Pvector);//메뉴 출력
    std::string InputSelection(string text);//입력

    //NPC 아스키아트
    void NPC_M();
    void NPC_K();

    //예비
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
  
    
    

};