#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include "core/UIManager.h"
#include "core/DungeonManager.h"
#include"character/Player.h"
//╔ ╗ ╚ ╝ ╠ ╣ ╦ ╩ ╬ ═ ║

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
void UI::Gotoxy(int x, int y)
{
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void UI::PrintStatus(Player*& p)
{
    Gotoxy(71, 22);
    std::cout << "이름: " << p->GetName() << "  직업: " << p->GetJob() << "  Lv: " << p->GetLevel();

    Gotoxy(71, 23);
    std::cout << "HP: " << p->GetHp() << "/" << p->GetMaxHp() << "  MP: " << p->GetMp() << "/" << p->GetMaxMp() << "  공격력: " << p->GetPower() << "  방어력: " << p->GetDefence();
}
void UI::PrintMenu(std::vector<std::string> menu)
{
    for (int i = 0; i < menu.size(); ++i)
    {
        Gotoxy(71, 27 + i);
        if (i == menu.size() - 1)
        {
            std::cout << "0)." << menu[i] << std::endl;
            break;
        }
        std::cout << i + 1 << ")." << menu[i] << std::endl;
    }
}
void UI::PrintBuilding()
{
    Gotoxy(10, 2);  std::cout << "         +---------------+";
    Gotoxy(10, 3);  std::cout << "         | [Z E P TOWER] |";
    Gotoxy(10, 4);  std::cout << "         |===============|";
    Gotoxy(10, 5);  std::cout << "         | [#]  [#]  [#] |";
    Gotoxy(10, 6);  std::cout << "         |---------------|";
    Gotoxy(10, 7);  std::cout << "         | [#]  [#]  [#] |";
    Gotoxy(10, 8);  std::cout << "         |---------------|";
    Gotoxy(10, 9);  std::cout << "         | [#]  [#]  [#] |";
    Gotoxy(10, 10);  std::cout << "         |---------------|";
    Gotoxy(10, 11);  std::cout << "         | [#]  [#]  [#] |";
    Gotoxy(10, 12); std::cout << "         |---------------|";
    Gotoxy(10, 13); std::cout << "         | [#]  [#]  [#] |";
    Gotoxy(10, 14); std::cout << "         |---------------|";
    Gotoxy(10, 15); std::cout << "  o      |   _  ____  _  |";
    Gotoxy(10, 16); std::cout << " /|\\     |  | | |  | | | |";
    Gotoxy(10, 17); std::cout << " / \\     |==|_|=|==|_|=|=|";
}
void UI::PrintMain()
{
    system("mode con:cols=150 lines=40 | title LOSTZEP");
    Gotoxy(0, 0);
    std::cout << R"(
╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
║                                                                                                                                                   ║
║                                                                                                                                                   ║
║                                                                                                                                                   ║
║                                                                                                                                                   ║
║                                                                                                                                                   ║
║                                                                                                                                                   ║
║                                                                                                                                                   ║
║                                                                                                                                                   ║
║                                                                                                                                                   ║
║                                                                                                                                                   ║
║                                                                                                                                                   ║
║                                                                                                                                                   ║
║                                                                                                                                                   ║
║                                                                                                                                                   ║
║                                                                                                                                                   ║
║                                                                                                                                                   ║
║                                                                                                                                                   ║
║                                                                                                                                                   ║
║                                                                                                                                                   ║
╠═════════════════════════════════════════════════════════════════════╦═════════════════════════════════════════════════════════════════════════════╣
║                                                                     ║                                                                             ║
║                                                                     ║                                                                             ║
║                                                                     ║                                                                             ║
║                                                                     ║                                                                             ║
║                                                                     ╠═════════════════════════════════════════════════════════════════════════════╣
║                                                                     ║                                                                             ║
║                                                                     ║                                                                             ║
║                                                                     ║                                                                             ║
║                                                                     ║                                                                             ║
║                                                                     ║                                                                             ║
║                                                                     ║                                                                             ║
╚═════════════════════════════════════════════════════════════════════╩═════════════════════════════════════════════════════════════════════════════╝                                                                                                                                                                               
 )";
}
void UI::PrintTitle()
{
    int y = 3;

    Gotoxy(2, y++); std::cout << "   ::                                                                                                                                         ";
    Gotoxy(2, y++); std::cout << "    -.                                                                                                                                        ";
    Gotoxy(2, y++); std::cout << "    -.                                         .-       ..                      ..                                      .     .               ";
    Gotoxy(2, y++); std::cout << "    -.                  :.=:.  ..+..        .:-::.:-     ...=---=:     ..==:--=..-    ---.:....:--..-         :..::::::.+.      .. -.. ...    ";
    Gotoxy(2, y++); std::cout << "    +.                 ..:        -..      .:             -.      :.  ::       :-     =         ..:           ....              .. .     .:.. ";
    Gotoxy(2, y++); std::cout << "    #=-              -..:          +. .   -..              :      ..  ..       :              .. =             . .              .: :      ....";
    Gotoxy(2, y++); std::cout << "    #*=              +**.          +=-.    +=                     ..  ::                    ...:*              -:.     .        ....     .=+. ";
    Gotoxy(2, y++); std::cout << "    #+-.             #++.          =**=      ` =-:::.             -   :.                    =***               .**: ... -=       .*+:.*+**.    ";
    Gotoxy(2, y++); std::cout << "    %+-              -++:          ===:          :-==:            :-. =-                 :+=+:                .++-              :+=:          ";
    Gotoxy(2, y++); std::cout << "    %=:               +=.          ::-            ---            :=. +=               :-==-           .      .--:              :=-:          ";
    Gotoxy(2, y++); std::cout << "   .*:..              .#:..       ::*             .-:-            :-. =              .:===.         ..=       .:::       .-     .::-          ";
    Gotoxy(2, y++); std::cout << "  ::::............      .=*..  ..*-        .-*:...#::              :  =             ...:::::::::......:       ::-::----:::     :.:::.         ";
    Gotoxy(2, y++); std::cout << "                                                                   +  -                                                                       ";
    Gotoxy(2, y++); std::cout << "                                                                  =  =.                                                                       ";
    Gotoxy(2, y++); std::cout << "                                                                   =  :                                                                       ";

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




