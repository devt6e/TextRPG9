#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include "core/UIManager.h"
#include "core/DungeonManager.h"
#include"character/Player.h"
//? ? ? ? ? ? ? ? ? ? ?

void UI::DisplayDungeonMap(const DungeonManager& dungeon)
{
    system("cls");
    UI::PrintMain();
    int mapWidth = dungeon.GetMapWidth();
    int mapHeight = dungeon.GetMapHeight();
    int displayWidth = mapWidth * 6 - 3;
    int startX = 2;  // X축 시작 위치 (필요에 따라 조절)
    int startY = 2;  // Y축 시작 위치 (필요에 따라 조절)
    int currentY = startY;
    Gotoxy(startX, currentY++);
    std::cout << std::string(displayWidth, '=');
    Gotoxy(startX, currentY++);
    std::cout << "ZEP TOWER - 1F";
    Gotoxy(startX, currentY++);
    std::cout << std::string(displayWidth, '=');
    for (int y = 0; y < mapHeight; y++)
    {
        Gotoxy(startX, currentY++);
        for (int x = 0; x < mapWidth; x++)
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
            if (x < mapWidth - 1)
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
        if (y < mapHeight - 1)
        {
            Gotoxy(startX, currentY++);
            for (int x = 0; x < mapWidth; x++)
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

                if (x < mapWidth - 1)
                {
                    std::cout << "   ";
                }
            }
            std::cout << '\n';
        }
    }
    Gotoxy(startX, currentY++);
    std::cout << std::string(displayWidth, '=');
    Gotoxy(startX, currentY++);
    std::cout << "[P] 현재 위치  [B] 보스";
    Gotoxy(startX, currentY++);
    std::cout << "[.] 탐색 완료  [?] 미확인 방";
    Gotoxy(startX, currentY++);
    std::cout << std::string(displayWidth, '=') << '\n';
    Gotoxy(startX, currentY++);
}

void UI::PrintDungeonMoveOptions(
    bool canMoveUp,
    bool canMoveDown,
    bool canMoveLeft,
    bool canMoveRight)
{
    std::cout << "\n이동 가능한 방향: ";

    if (canMoveUp)
    {
        std::cout << "W(위) ";
    }

    if (canMoveDown)
    {
        std::cout << "S(아래) ";
    }

    if (canMoveLeft)
    {
        std::cout << "A(왼쪽) ";
    }

    if (canMoveRight)
    {
        std::cout << "D(오른쪽) ";
    }

    std::cout << "\nQ(마을로 복귀)\n";
    std::cout << "입력: ";
}


void UI::Gotoxy(int x, int y)
{
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void UI::PrintStatus(Player* p)
{
    Gotoxy(81, 22);
    std::cout << u8"이름: " << p->GetName() << u8"  직업: " << p->GetJob() << "  Lv: " << p->GetLevel();

    Gotoxy(81, 23);
    std::cout << "HP: " << p->GetHp() << "/" << p->GetMaxHp() << "  MP: " << p->GetMp() << "/" << p->GetMaxMp() << u8"  공격력: " << p->GetPower() << u8"  방어력: " << p->GetDefence() << std::endl;
    Gotoxy(1, 24);
}
void UI::PrintMenu(std::vector<std::string> menu)
{
    for (int i = 0; i < menu.size(); ++i)
    {
        Gotoxy(81, 27 + i);
        if (i == menu.size() - 1)
        {
            std::cout << "0)." << menu[i] << std::endl;
            break;
        }
        std::cout << i + 1 << ")." << menu[i] << std::endl;
    }
}
void UI::PrintMessage(const std::string& str) 
{ 
    std::cout << str; 
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
void UI::PrintTown()
{
    Gotoxy(1, 2);  std::cout << "                                                                 ";
    Gotoxy(1, 3);  std::cout << "           o                       o                       o     ";
    Gotoxy(1, 4);  std::cout << "          /|\\                     /|\\                     /|\\    ";
    Gotoxy(1, 5);  std::cout << "          / \\                     / \\                     / \\    ";
    Gotoxy(1, 6);  std::cout << "     +---------------------------------------------------------+  ";
    Gotoxy(1, 7);  std::cout << "     |  [====]                   [====]                  [====]|  ";
    Gotoxy(1, 8);  std::cout << "     |   |__|                     |__|                    |__| |  ";
    Gotoxy(1, 9); std::cout << "     |-------------------------------------------------------- |  ";
    Gotoxy(1, 10); std::cout << "     |   |__|                     |__|                    |__| |  ";
    Gotoxy(1, 11); std::cout << "     |  [====]                   [====]                  [====]|  ";
    Gotoxy(1, 12); std::cout << "     +---------------------------------------------------------+  ";
    Gotoxy(1, 13); std::cout << "          \\ /                     \\ /                     \\ /    ";
    Gotoxy(1, 14); std::cout << "          \\|/                     \\|/                     \\|/    ";
    Gotoxy(1, 15); std::cout << "           o                       o                       o     ";
    Gotoxy(1, 16); std::cout << "                                                                 ";
}
void UI::PrintMain()
{
    system("mode con:cols=150 lines=40 | title LOSTZEP");
    Gotoxy(0, 0);
    std::cout << u8R"(
?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?                                                                                                                                                   ?
?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
?                                                                               ?                                                                   ?
?                                                                               ?                                                                   ?
?                                                                               ?                                                                   ?
?                                                                               ?                                                                   ?
?                                                                               ?????????????????????????????????????????????????????????????????????
?                                                                               ?                                                                   ?
?                                                                               ?                                                                   ?
?                                                                               ?                                                                   ?
?                                                                               ?                                                                   ?
?                                                                               ?                                                                   ?
?                                                                               ?                                                                   ?
?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????                                                                                                                                                                               
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
void UI::PrintIntro()
{
    UI::PrintMain();
    UI::PrintTown();
    UI::Gotoxy(2, 22);
    std::cout << u8"평화로운 내일배움캠프 마을..." << std::endl;
    UI::Gotoxy(2, 23);
    std::cout << u8"어느 날 ZEP 본사에서 포인트 제도를 폐지하고..." << std::endl;
    UI::Gotoxy(2, 24);
    std:cout << u8"그에 반발하던 매니저님들, 튜터님들을 납치했다!!" << std::endl;
    UI::Gotoxy(2, 25);
    system("pause");
    system("cls");
    UI::PrintMain();
    UI::PrintBuilding();
    UI::Gotoxy(2, 22);
    std::cout << u8"당신은 납치당한 사람들과 포인트를 되찾기 위해 ZEP 빌딩을 오르기로 한다..." << std::endl;
    UI::Gotoxy(2, 23);
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




