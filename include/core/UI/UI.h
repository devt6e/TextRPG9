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
    bool IsClear1 = false;
    std::vector<std::string> menu = { "던전","인벤토리" };
    
public:

    
	void Title()
	{
		system("cls");
        std::cout << "====================" << std::endl;
        std::cout << "     rpg 제목     " << std::endl;
        std::cout << "====================" << std::endl;
	}

	void ZepBuilding()
	{
        std::cout << "======================================================== \n";
        std::cout << "                        +---------------+                \n";
        std::cout << "                        | [Z E P TOWER] |                \n";
        std::cout << "                        |===============|                \n";
        std::cout << "                        | [#]  [#]  [#] |                \n";
        std::cout << "                        |---------------|                \n";
        std::cout << "                        | [#]  [#]  [#] |                \n";
        std::cout << "                        |---------------|                \n";
        std::cout << "                        | [#]  [#]  [#] |                \n";
        std::cout << "                        |---------------|                \n";
        std::cout << "                        | [#]  [#]  [#] |                \n";
        std::cout << "                        |---------------|                \n";
        std::cout << "                        | [#]  [#]  [#] |                \n";
        std::cout << "                        |---------------|                \n";
        std::cout << "               o        |   _  ____  _  |                \n";
        std::cout << "              /|\\       |  | | |  | | | |               \n";
        std::cout << "              / \\       |==|_|=|==|_|=|=|               \n";
        std::cout << "======================================================== \n";
	}
    void NBCTown()
    {
        std::cout << "================================================================= \n";
        std::cout << "                                                                  \n";
        std::cout << "           o                       o                       o      \n"; 
        std::cout << "          /|\\                     /|\\                     /|\\  \n"; 
        std::cout << "          / \\                     / \\                     / \\  \n"; 
        std::cout << "     +--------------------------------------------------------+   \n";
        std::cout << "     |  [====]                  [====]                  [====]|   \n"; 
        std::cout << "     |   |__|                    |__|                    |__| |   \n"; 
        std::cout << "     |--------------------------------------------------------|   \n";
        std::cout << "     |   |__|                    |__|                    |__| |   \n"; 
        std::cout << "     |  [====]                  [====]                  [====]|   \n"; 
        std::cout << "     +--------------------------------------------------------+   \n";
        std::cout << "          \\ /                    \\ /                      \\ /  \n"; 
        std::cout << "          \\|/                    \\|/                      \\|/  \n"; 
        std::cout << "           o                      o                        o      \n"; 
        std::cout << "                                                                  \n";
        std::cout << "================================================================= \n";
   
    }
    
    void Intro()
    {
        NBCTown();
        std::cout << "평화로운 내일배움캠프 마을.. " << std::endl << std::endl;
        std::cout << "어느 날 ZEP 회사에서 매니저님, 튜터님들을 납치한다." << std::endl << std::endl;
        system("pause");
        system("cls");
        ZepBuilding();
        std::cout << "당신은 납치된 사람들을 구하기 위해 ZEP 빌딩을 오르기로 한다" << std::endl << std::endl;
        std::cout << "당신의 이름은? : ";
        system("pause");

    }
    void Dungeon();
    void Inventory();
    void PlayerMenu()
    {
        Title();
        std::cout << menu[0] << std::endl << menu[1] << std::endl;
        std::cin >> MenuChoice;
        switch (MenuChoice)
        {
        case 1:
            Dungeon();
            break;
        case 2:
            Inventory();
            break;
        default:
            std::cout << "잘못된 입력입니다.";
            system("pause");
            break;
        
        }

    }
    void Maps1_1()
    {
        Title();
        std::cout << std::endl;
        std::cout << "========================================================  \n";
        std::cout << "                   [ Zep Tower 1F ]                       \n";
        std::cout << "========================================================  \n";
        std::cout << "                    [ @ ]                                 \n";
        std::cout << "                     │                                    \n";
        std::cout << "        [  ] ─────  [ 2 ] ──── [ 4 ]                      \n";
        std::cout << "                     │          │                         \n";
        std::cout << "                    [ 3 ] ──── [ 5 ] ───── [B6]           \n";
        std::cout << "                                                          \n";
        std::cout << "========================================================  \n";
        std::cout << "  [@ ] 플레이어         [B ] 보스         [  ] 일반 방      \n";
        std::cout << "========================================================  \n";
    }
    void Maps1_2()
    {
        Title();
        std::cout << std::endl;
        std::cout << "========================================================  \n";
        std::cout << "                   [ Zep Tower 1F ]                       \n";
        std::cout << "========================================================  \n";
        std::cout << "                    [ 1 ]                                 \n";
        std::cout << "                     │                                    \n";
        std::cout << "        [  ] ─────  [ @ ] ──── [ 4 ]                      \n";
        std::cout << "                     │          │                         \n";
        std::cout << "                    [ 3 ] ──── [ 5 ] ───── [B6]           \n";
        std::cout << "                                                          \n";
        std::cout << "========================================================  \n";
        std::cout << "  [@ ] 플레이어         [B ] 보스         [  ] 일반 방      \n";
        std::cout << "========================================================  \n";
    }
    void Maps1_3()
    {
        Title();
        std::cout << std::endl;
        std::cout << "========================================================  \n";
        std::cout << "                   [ Zep Tower 1F ]                       \n";
        std::cout << "========================================================  \n";
        std::cout << "                    [ 1 ]                                 \n";
        std::cout << "                     │                                    \n";
        std::cout << "        [  ] ─────  [ 2 ] ──── [ 4 ]                      \n";
        std::cout << "                     │          │                         \n";
        std::cout << "                    [ @ ] ──── [ 5 ] ───── [B6]           \n";
        std::cout << "                                                          \n";
        std::cout << "========================================================  \n";
        std::cout << "  [@ ] 플레이어         [B ] 보스         [  ] 일반 방      \n";
        std::cout << "========================================================  \n";
    }
    void Maps1_4()
    {
        Title();
        std::cout << std::endl;
        std::cout << "========================================================  \n";
        std::cout << "                   [ Zep Tower 1F ]                       \n";
        std::cout << "========================================================  \n";
        std::cout << "                    [ 1 ]                                 \n";
        std::cout << "                     │                                    \n";
        std::cout << "        [  ] ─────  [ 2 ] ──── [ @ ]                      \n";
        std::cout << "                     │          │                         \n";
        std::cout << "                    [ 3 ] ──── [ 5 ] ───── [B6]           \n";
        std::cout << "                                                          \n";
        std::cout << "========================================================  \n";
        std::cout << "  [@ ] 플레이어         [B ] 보스         [  ] 일반 방      \n";
        std::cout << "========================================================  \n";
    }

    void Maps1_5()
    {
        Title();
        std::cout << std::endl;
        std::cout << "========================================================  \n";
        std::cout << "                   [ Zep Tower 1F ]                       \n";
        std::cout << "========================================================  \n";
        std::cout << "                    [ 1 ]                                 \n";
        std::cout << "                     │                                    \n";
        std::cout << "        [  ] ─────  [ 2 ] ──── [ 4 ]                      \n";
        std::cout << "                     │          │                         \n";
        std::cout << "                    [ 3 ] ──── [ @ ] ───── [B6]           \n";
        std::cout << "                                                          \n";
        std::cout << "========================================================  \n";
        std::cout << "  [@ ] 플레이어         [B ] 보스         [  ] 일반 방      \n";
        std::cout << "========================================================  \n";
    }

    void Maps1()
    {
        std::cout << std::endl;
        std::cout << "========================================================  \n";
        std::cout << "                   [ Zep Tower 1F ]                       \n";
        std::cout << "========================================================  \n";
        std::cout << "                    [ 1 ]                                 \n";
        std::cout << "                     │                                    \n";
        std::cout << "        [@ ] ─────  [ 2 ] ──── [ 4 ]                      \n";
        std::cout << "                     │          │                         \n";
        std::cout << "                    [ 3 ] ──── [ 5 ] ───── [B6]           \n"; 
        std::cout << "                                                          \n";
        std::cout << "========================================================  \n";
        std::cout << "  [@ ] 플레이어         [B ] 보스         [  ] 일반 방      \n";
        std::cout << "========================================================  \n";

        while (PlayerLocation!=6)
        {
            std::cout << "목적지를 선택하세요. : ";
            std::cin >> RoomChoice;
            switch (RoomChoice)
            {
            case 1:
                if (PlayerLocation == 2)
                {
                    PlayerLocation = 1;
                    Maps1_1();
                    break;
                }
                else
                {
                    std::cout << "잘못된 입력입니다.";
                    system("pause");
                    break;
                }
            case 2:
                if (PlayerLocation == 1 || PlayerLocation == 3 || PlayerLocation == 4||PlayerLocation == 0)
                {
                    PlayerLocation = 2;
                    Maps1_2();
                    break;
                }
                else
                {
                    std::cout << "잘못된 입력입니다.";
                    system("pause");
                    break;
                }
            case 3:
                if (PlayerLocation == 2 || PlayerLocation == 5)
                {
                    PlayerLocation = 3;
                    Maps1_3();
                    break;
                }
                else
                {
                    std::cout << "잘못된 입력입니다.";
                    system("pause");
                    break;
                }
            case 4:
                if (PlayerLocation == 2 || PlayerLocation == 5)
                {
                    PlayerLocation = 4;
                    Maps1_4();
                    break;
                }
                else
                {
                    std::cout << "잘못된 입력입니다.";
                    system("pause");
                    break;
                }
            case 5:
                if (PlayerLocation == 3 || PlayerLocation == 4)
                {
                    PlayerLocation = 5;
                    Maps1_5();
                    break;
                }
                else
                {
                    std::cout << "잘못된 입력입니다.";
                    system("pause");
                    break;
                }
            case 6:
                if (PlayerLocation == 5)
                {
                    PlayerLocation = 6;
                    break;
                }
            default:
                std::cout << "잘못된 입력입니다.";
                system("pause");
                break;
            
            }
           


        }
    }
    
};