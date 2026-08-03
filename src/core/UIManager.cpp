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
void UI::Dungeon()
{
    if (CurrentFloor == 1)
    {
        Maps1();
        while (PlayerLocation != 6)
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
                if (PlayerLocation == 1 || PlayerLocation == 3 || PlayerLocation == 4 || PlayerLocation == 0)
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
    else if (CurrentFloor == 2)
    {
        PlayerLocation = 0;
        Maps2();
        while (PlayerLocation != 6)
        {
            std::cout << "목적지를 선택하세요. : ";
            std::cin >> RoomChoice;
            switch (RoomChoice)
            {
            case 1:
                if (PlayerLocation == 4)
                {
                    PlayerLocation = 1;
                    Maps2_1();
                    break;
                }
                else
                {
                    std::cout << "잘못된 입력입니다.";
                    system("pause");
                    break;
                }
            case 2:
                if (PlayerLocation == 0 || PlayerLocation == 3)
                {
                    PlayerLocation = 2;
                    Maps2_2();
                    break;
                }
                else
                {
                    std::cout << "잘못된 입력입니다.";
                    system("pause");
                    break;
                }
            case 3:
                if (PlayerLocation == 2 || PlayerLocation == 4 || PlayerLocation == 5)
                {
                    PlayerLocation = 3;
                    Maps2_3();
                    break;
                }
                else
                {
                    std::cout << "잘못된 입력입니다.";
                    system("pause");
                    break;
                }
            case 4:
                if (PlayerLocation == 1 || PlayerLocation == 3)
                {
                    PlayerLocation = 4;
                    Maps2_4();
                    break;
                }
                else
                {
                    std::cout << "잘못된 입력입니다.";
                    system("pause");
                    break;
                }
            case 5:
                if (PlayerLocation == 3)
                {
                    PlayerLocation = 5;
                    Maps2_5();
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
                else
                {
                    std::cout << "잘못된 입력입니다.";
                    system("pause");
                    break;
                }
            }
        }
    }

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
    std::cout << "test -- 수정예정(경욱님)" << std::endl;
    //std::cout << MonsterName << "(이)가 나타났다!" << std::endl;
    system("pause");
    //while (!IsWin)
    //{
    //    //몬스터 아스키아트
    //    //PrintStatus();
    //    //BattleSelection();
    //}

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


void UI::Maps1()
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
}

void UI::Maps1_1()
{
    MiniTitle();
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

void UI::Maps1_2()
{
    MiniTitle();
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

void UI::Maps1_3()
{
    MiniTitle();
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

void UI::Maps1_4()
{
    MiniTitle();
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

void UI::Maps1_5()
{
    MiniTitle();
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

void UI::Maps2()
{
    MiniTitle();
    std::cout << std::endl;
    std::cout << "========================================================  \n";
    std::cout << "                   [ Zep Tower 1F ]                       \n";
    std::cout << "========================================================  \n";
    std::cout << "                                                          \n";
    std::cout << "                                         [ 1 ]            \n";
    std::cout << "                                           │              \n";
    std::cout << "        [ @] ─────  [ 2 ] ──── [ 3 ]──── [ 4 ]            \n";
    std::cout << "                                │                         \n";
    std::cout << "                               [ 5 ] ───── [B6]           \n";
    std::cout << "                                                          \n";
    std::cout << "========================================================  \n";
    std::cout << "  [@ ] 플레이어         [B ] 보스         [  ] 일반 방      \n";
    std::cout << "========================================================  \n";
}

void UI::Maps2_1()
{
    MiniTitle();
    std::cout << std::endl;
    std::cout << "========================================================  \n";
    std::cout << "                   [ Zep Tower 1F ]                       \n";
    std::cout << "========================================================  \n";
    std::cout << "                                                          \n";
    std::cout << "                                         [ @ ]            \n";
    std::cout << "                                           │              \n";
    std::cout << "        [  ] ─────  [ 2 ] ──── [ 3 ]──── [ 4 ]            \n";
    std::cout << "                                │                         \n";
    std::cout << "                               [ 5 ] ───── [B6]           \n";
    std::cout << "                                                          \n";
    std::cout << "========================================================  \n";
    std::cout << "  [@ ] 플레이어         [B ] 보스         [  ] 일반 방      \n";
    std::cout << "========================================================  \n";
}

void UI::Maps2_2()
{
    MiniTitle();
    std::cout << std::endl;
    std::cout << "========================================================  \n";
    std::cout << "                   [ Zep Tower 1F ]                       \n";
    std::cout << "========================================================  \n";
    std::cout << "                                                          \n";
    std::cout << "                                         [ 1 ]            \n";
    std::cout << "                                           │              \n";
    std::cout << "        [  ] ─────  [ @ ] ──── [ 3 ]──── [ 4 ]            \n";
    std::cout << "                                │                         \n";
    std::cout << "                               [ 5 ] ───── [B6]           \n";
    std::cout << "                                                          \n";
    std::cout << "========================================================  \n";
    std::cout << "  [@ ] 플레이어         [B ] 보스         [  ] 일반 방      \n";
    std::cout << "========================================================  \n";
}

void UI::Maps2_3()
{
    MiniTitle();
    std::cout << std::endl;
    std::cout << "========================================================  \n";
    std::cout << "                   [ Zep Tower 1F ]                       \n";
    std::cout << "========================================================  \n";
    std::cout << "                                                          \n";
    std::cout << "                                         [ 1 ]            \n";
    std::cout << "                                           │              \n";
    std::cout << "        [  ] ─────  [ 2 ] ──── [ @ ]──── [ 4 ]            \n";
    std::cout << "                                │                         \n";
    std::cout << "                               [ 5 ] ───── [B6]           \n";
    std::cout << "                                                          \n";
    std::cout << "========================================================  \n";
    std::cout << "  [@ ] 플레이어         [B ] 보스         [  ] 일반 방      \n";
    std::cout << "========================================================  \n";
}

void UI::Maps2_4()
{
    MiniTitle();
    std::cout << std::endl;
    std::cout << "========================================================  \n";
    std::cout << "                   [ Zep Tower 1F ]                       \n";
    std::cout << "========================================================  \n";
    std::cout << "                                                          \n";
    std::cout << "                                         [ 1 ]            \n";
    std::cout << "                                           │              \n";
    std::cout << "        [  ] ─────  [ 2 ] ──── [ 3 ]──── [ @ ]            \n";
    std::cout << "                                │                         \n";
    std::cout << "                               [ 5 ] ───── [B6]           \n";
    std::cout << "                                                          \n";
    std::cout << "========================================================  \n";
    std::cout << "  [@ ] 플레이어         [B ] 보스         [  ] 일반 방      \n";
    std::cout << "========================================================  \n";
}

void UI::Maps2_5()
{
    MiniTitle();
    std::cout << std::endl;
    std::cout << "========================================================  \n";
    std::cout << "                   [ Zep Tower 1F ]                       \n";
    std::cout << "========================================================  \n";
    std::cout << "                                                          \n";
    std::cout << "                                         [ 1 ]            \n";
    std::cout << "                                           │              \n";
    std::cout << "        [  ] ─────  [ 2 ] ──── [ 3 ]──── [ 4 ]            \n";
    std::cout << "                                │                         \n";
    std::cout << "                               [ @ ] ───── [B6]           \n";
    std::cout << "                                                          \n";
    std::cout << "========================================================  \n";
    std::cout << "  [@ ] 플레이어         [B ] 보스         [  ] 일반 방      \n";
    std::cout << "========================================================  \n";
}

