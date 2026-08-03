#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include "core/UIManager.h"
#include "core/DungeonManager.h"

void UI::DisplayDungeonMap(const DungeonManager& dungeon)
{
    system("cls");

    int mapSize = dungeon.GetMapSize();
    int mapWidth = mapSize * 6 - 3;

    std::cout << std::string(mapWidth, '=') << '\n';
    std::cout << "ZEP TOWER - 1F\n";
    std::cout << std::string(mapWidth, '=') << '\n';
    for (int y = 0; y < mapSize; y++)
    {
        for (int x = 0; x < mapSize; x++)
        {
            std::string symbol = "   ";

            if (dungeon.IsPlayerAt(x, y))
            {
                symbol = "[P]";
            }
            else if (dungeon.IsBossAt(x, y))
            {
                symbol = "[B]";
            }
            else if (dungeon.IsRoomVisited(x, y))
            {
                symbol = "[.]";
            }
            else if (dungeon.IsRoomVisible(x, y))
            {
                symbol = "[?]";
            }

            std::cout << symbol;
            if (x < mapSize - 1)
            {
                bool connected =
                    dungeon.HasRoom(x, y) &&
                    dungeon.HasRoom(x + 1, y) &&
                    dungeon.IsRoomVisible(x, y) &&
                    dungeon.IsRoomVisible(x + 1, y);

                if (connected)
                {
                    std::cout << "---";
                }
                else
                {
                    std::cout << "   ";
                }
            }
        }

        std::cout << '\n';
        if (y < mapSize - 1)
        {
            for (int x = 0; x < mapSize; x++)
            {
                bool connected =
                    dungeon.HasRoom(x, y) &&
                    dungeon.HasRoom(x, y + 1) &&
                    dungeon.IsRoomVisible(x, y) &&
                    dungeon.IsRoomVisible(x, y + 1);

                if (connected)
                {
                    std::cout << " | ";
                }
                else
                {
                    std::cout << "   ";
                }

                if (x < mapSize - 1)
                {
                    std::cout << "   ";
                }
            }

            std::cout << '\n';
        }
    }
    std::cout << std::string(mapWidth, '=') << '\n';
    std::cout << "[P] 현재 위치  [B] 보스\n";
    std::cout << "[.] 탐색 완료  [?] 미확인 방\n";
    std::cout << std::string(mapWidth, '=') << '\n';
}
void UI::MainTitle()
{
    system("cls");
    std::cout << "   ::                                                                                                                                         " << std::endl;
    std::cout << "    -.                                                                                                                                        " << std::endl;
    std::cout << "    -.                                         .-       ..                      ..                                      .     .               " << std::endl;
    std::cout << "    -.                  :.=:.  ..+..        .:-::.:-     ...=---=:     ..==:--=..-    ---.:....:--..-         :..::::::.+.      .. -.. ...    " << std::endl;
    std::cout << "    +.                 ..:        -..      .:             -.      :.  ::       :-     =         ..:           ....              .. .     .:.. " << std::endl;
    std::cout << "    #=-              -..:          +. .   -..              :      ..  ..       :              .. =             . .              .: :      ...." << std::endl;
    std::cout << "    #*=              +**.          +=-.    +=                     ..  ::                    ...:*              -:.     .        ....     .=+. " << std::endl;
    std::cout << "    #+-.             #++.          =**=      ` =-:::.             -   :.                   =***               .**: ... -=       .*+:.*+**.    " << std::endl;
    std::cout << "    %+-              -++:          ===:          :-==:            :-. =-                 :+=+:                .++-              :+=:          " << std::endl;
    std::cout << "    %=:               +=.          ::-             ---            :=. +=               :-==-           .      .--:              :=-:          " << std::endl;
    std::cout << "   .*:..              .#:..       ::*             .-:-            :-. =              .:===.         ..=       .:::       .-     .::-          " << std::endl;
    std::cout << "  ::::............      .=*..  ..*-        .-*:...#::              :  =             ...:::::::::......:       ::-::----:::     :.:::.         " << std::endl;
    std::cout << "                                                                   +  -                                                                       " << std::endl;
    std::cout << "                                                                  =  =.                                                                       " << std::endl;
    std::cout << "                                                                   =  :                                                                       " << std::endl;
    std::cout << "                                                                   .  ;                                                                       " << std::endl;
    std::cout << "                                                                      .                                                                       " << std::endl;
    system("pause");
    system("cls");
}
void UI::MiniTitle()
{
    system("cls");
    std::cout << "========================================================" << std::endl;
    std::cout << "                        Lost ZEP                        " << std::endl;
    std::cout << "========================================================" << std::endl;
}
void UI::NBCTown()
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
    std::cout << "평화로운 내일배움캠프 마을... " << std::endl << std::endl;
    std::cout << "어느 날 ZEP 회사에서 포인트 제도를 폐지하게 되고..." << std::endl << std::endl;
    std::cout << "그에 반발하던 매니저님들, 튜터님들을 납치해 갔다!!" << std::endl << std::endl;
    system("pause");       
}
void UI::ZepBuilding()
{
    system("cls");
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
    std::cout << "당신은 납치된 사람들과 포인트를 되찾기 위해 ZEP 빌딩을 오르기로 한다" << std::endl;
    system("pause");
}
void UI::PrintMenu(std::vector<std::string> Pvector)
{
    std::cout << std::endl << "====================" << std::endl;
    for (int i = 0; i < Pvector.size(); ++i)
    {
        if (i == Pvector.size()-1)
        {
            std::cout << "0)." << Pvector[i] << std::endl;
            break;
        }
        std::cout<<i+1<<")." << Pvector[i] << std::endl;
    }
}
void UI::PrintStatus(std::string name,std::string job, int level,int hp,int maxhp,int mp,int maxmp,int power,int defense)
{
    std::cout << std::endl << "================================================" << std::endl;
    std::cout << "이름: " << name << " | 직업: " << job << " | Lv." << level << std::endl;
    std::cout << "HP: " << hp << "/" << maxhp << " | MP: " << mp << "/" << maxmp << " | 공격력: " << power << " | 방어력: " << defense;
    std::cout << std::endl << "================================================" << std::endl;
}
int UI::BattleSelection(std::string text)
{
    int choice;
    std::cout << text << std::endl;
    std::cin >> choice;
    return choice;
}
void UI::PrintBattle(std::string MonsterName,bool IsWin)
{
    //몬스터 아스키아트
    std::cout << MonsterName << "(이)가 나타났다!" << std::endl;
    system("pause");
    while (!IsWin)
    {
        //몬스터 아스키아트
        UI::PrintStatus();
        UI::BattleSelection();
    }

}
std::string UI::InputSelection(std::string text)
{
    std::string s;
    std::cout << text;
    std::cin >> s;
    return s;

}
void UI::NPC_M()
{
    MiniTitle();
    std::cout << "                  ---          " << std::endl;
    std::cout << "                /     \\        " << std::endl;
    std::cout << "                ((o_o))        " << std::endl;
    std::cout << "                \\     /         " << std::endl;
    std::cout << "              -(|    |)-       " << std::endl;
    std::cout << "             ( |      | )      " << std::endl;
    std::cout << "             | |      | |      " << std::endl;
    std::cout << "             (_|______|_)      " << std::endl;
    std::cout << "                | ___ |        " << std::endl;
    std::cout << "  /\\ =^._.^=    | | | |        " << std::endl;
    std::cout << "    \\ |   |     | | | |        " << std::endl;
    std::cout << "     \\|___|    (__| |__)       " << std::endl;

}
void UI::NPC_K()
{
    MiniTitle();
    std::cout << R"(
                    /\
                   /  \          
                  /    \        
                 /      \      
         ____   /________\    ____
        (    \   (  o.o  )   /    )
         \    \   \  =  /   /    /
          \    \  /`---'\  /    /
           \    \/   |   \/    /
            /   /|   |   |\   \
           (   ( |   |   | )   )
           /    \|   |   |/    \
          /     /|___|___|\     \
         (____ /  /     \  \_____)
                 /       \
                |    |    |
                |    |    |
               (_____|_____)
)" << std::endl;
}



