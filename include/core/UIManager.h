#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include "item/Item.h"

class DungeonManager;//던전
class Player;

class UI
{
private:
    std::vector<int> Offsets = { 0,0 };
public:

    void DisplayDungeonMap(const DungeonManager& dungeon);//맵 출력
    void Gotoxy(int x, int y);//좌표 설정
    void Gotoxy(std::vector<int> coor);
    void Erase(std::vector<int> coord, int rangeX, int rangeY);
    void EraseArt();
    void EraseLog();
    void EraseSelection();
    void EraseStat();
    void PrintTitle(); //LOSTZEP 타이틀
    void PrintMain(); //UI 뼈대
    void PrintBuilding(); //초반 스토리 
    void PrintTown();//초반 스토리 
    void PrintIntro();//초반 스토리
    void PrintStatus(Player* p);//스탯창 출력
    void PrintInventory(std::vector<std::string> Inv);//인벤토리 출력
    void PrintInventory(std::vector<Item> Inv, std::string str, int offset); //오버로딩. 가방 종류 출력
    void PrintSelection(std::vector<std::string> menu);//선택지 출력
    void UI::PrintSelection(std::vector<Item> menu);//
    std::string InputString(std::string text);// 입력 스트링
    int InputSelection(std::string text);//입력 정수
    void WaitForAnyKey(const std::string& text);//키 하나 입력 대기
    void PrintLog(const std::string&);
    void UI::PrintArt(std::string_view s);
    void Pause();

    void PrintDungeonMoveOptions(
        bool canMoveUp,
        bool canMoveDown,
        bool canMoveLeft,
        bool canMoveRight);


    //NPC 아스키아트
    void NPC_M();
    void NPC_K();

    
};
