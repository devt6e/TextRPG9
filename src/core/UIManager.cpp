#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include "core/UIManager.h"
#include "core/DungeonManager.h"
#include"character/Player.h"
#define ART_POS {2,2}
#define LOG_POS {2,22}
#define STAT_POS {81,22}
#define SELECT_POS {81,27}
//╔ ╗ ╚ ╝ ╠ ╣ ╦ ╩ ╬ ═ ║

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
    UI::Gotoxy(startX, currentY++);
    //std::cout << std::string(displayWidth, '═');
    UI::Gotoxy(startX, currentY++);
    std::cout << "ZEP TOWER - 1F";
    UI::Gotoxy(startX, currentY++);
    //std::cout << std::string(displayWidth, '═');
    for (int y = 0; y < mapHeight; y++)
    {
        UI::Gotoxy(startX, currentY++);
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
            UI::Gotoxy(startX, currentY++);
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
    UI::Gotoxy(startX, currentY++);
    //std::cout << std::string(displayWidth, '═');
    UI::Gotoxy(startX, currentY++);
    std::cout << "[P] 현재 위치  [B] 보스";
    UI::Gotoxy(startX, currentY++);
    std::cout << "[.] 탐색 완료  [?] 미확인 방";
    UI::Gotoxy(startX, currentY++);
    //std::cout << std::string(displayWidth, '═') << '\n';
    UI::Gotoxy(startX, currentY++);
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
void UI::Gotoxy(std::vector<int> coor)
{
    COORD pos = { (SHORT)(coor[0]), (SHORT)(coor[1]) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void UI::PrintStatus(Player* p)
{
    Offsets = STAT_POS;
    UI::Gotoxy(Offsets[0], Offsets[1]++);
    std::cout << u8"이름: " << p->GetName() << u8"  직업: " << p->GetJob() << "  Lv: " << p->GetLevel();
    std::cout << "HP: " << p->GetHp() << "/" << p->GetMaxHp() << "  MP: " << p->GetMp() << "/" << p->GetMaxMp() << u8"  공격력: " << p->GetPower() << u8"  방어력: " << p->GetDefence() << std::endl;
    UI::Gotoxy(1, 24);
}
void UI::PrintInventory(std::vector<string> Inv)
{
    Offsets = STAT_POS;
    UI::Gotoxy(Offsets[0],Offsets[1]);
    for (int i = 0; i < Inv.size(); ++i)
    {
        std::cout <<i+1<<"). " << Inv[i] << "  ";
        if ((i + 1) % 3 == 0)
        {
            Gotoxy(Offsets[0], ++Offsets[1]);
        }
    }
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
    Offsets = LOG_POS;
    static int n = 0;
    UI::Gotoxy(Offsets[0], Offsets[1] + n);
    n++;
    std::cout << str << "  ";
}
void UI::PrintBuilding()
{
    UI::Gotoxy(10, 2);  std::cout << "         +---------------+";
    UI::Gotoxy(10, 3);  std::cout << "         | [Z E P TOWER] |";
    UI::Gotoxy(10, 4);  std::cout << "         |===============|";
    UI::Gotoxy(10, 5);  std::cout << "         | [#]  [#]  [#] |";
    UI::Gotoxy(10, 6);  std::cout << "         |---------------|";
    UI::Gotoxy(10, 7);  std::cout << "         | [#]  [#]  [#] |";
    UI::Gotoxy(10, 8);  std::cout << "         |---------------|";
    UI::Gotoxy(10, 9);  std::cout << "         | [#]  [#]  [#] |";
    UI::Gotoxy(10, 10);  std::cout << "         |---------------|";
    UI::Gotoxy(10, 11);  std::cout << "         | [#]  [#]  [#] |";
    UI::Gotoxy(10, 12); std::cout << "         |---------------|";
    UI::Gotoxy(10, 13); std::cout << "         | [#]  [#]  [#] |";
    UI::Gotoxy(10, 14); std::cout << "         |---------------|";
    UI::Gotoxy(10, 15); std::cout << "  o      |   _  ____  _  |";
    UI::Gotoxy(10, 16); std::cout << " /|\\     |  | | |  | | | |";
    UI::Gotoxy(10, 17); std::cout << " / \\     |==|_|=|==|_|=|=|";
}
void UI::PrintTown()
{
    UI::Gotoxy(1, 2);  std::cout << "                                                                 ";
    UI::Gotoxy(1, 3);  std::cout << "           o                       o                       o     ";
    UI::Gotoxy(1, 4);  std::cout << "          /|\\                     /|\\                     /|\\    ";
    UI::Gotoxy(1, 5);  std::cout << "          / \\                     / \\                     / \\    ";
    UI::Gotoxy(1, 6);  std::cout << "     +---------------------------------------------------------+  ";
    UI::Gotoxy(1, 7);  std::cout << "     |  [====]                   [====]                  [====]|  ";
    UI::Gotoxy(1, 8);  std::cout << "     |   |__|                     |__|                    |__| |  ";
    UI::Gotoxy(1, 9); std::cout << "     |-------------------------------------------------------- |  ";
    UI::Gotoxy(1, 10); std::cout << "     |   |__|                     |__|                    |__| |  ";
    UI::Gotoxy(1, 11); std::cout << "     |  [====]                   [====]                  [====]|  ";
    UI::Gotoxy(1, 12); std::cout << "     +---------------------------------------------------------+  ";
    UI::Gotoxy(1, 13); std::cout << "          \\ /                     \\ /                     \\ /    ";
    UI::Gotoxy(1, 14); std::cout << "          \\|/                     \\|/                     \\|/    ";
    UI::Gotoxy(1, 15); std::cout << "           o                       o                       o     ";
    UI::Gotoxy(1, 16); std::cout << "                                                                 ";
}
void UI::PrintMain()
{
    const int WIDTH = 149;
    const int HEIGHT = 34;
    const int MIDDLE_Y = 21;
    const int SUB_DIVIDER_X = 80;
    const int SUB_DIVIDER_Y = 26;
    //DRAW TOP
    UI::Gotoxy(0, 0);
    std::cout << R"(
╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
)";
    //DRAW MIDDLE
    UI::Gotoxy(0, MIDDLE_Y);
    std::cout << R"(╠═══════════════════════════════════════════════════════════════════════════════╦═══════════════════════════════════════════════════════════════════╣
)";
    //DRAW BOTTOM
    UI::Gotoxy(0, HEIGHT - 1);
    std::cout << R"(╚═══════════════════════════════════════════════════════════════════════════════╩═══════════════════════════════════════════════════════════════════╝ 
)";
    for (int h = 1; h < HEIGHT - 1; h++)
    {
        if (h == 1 || h == MIDDLE_Y)
        {
            continue;
        }
        UI::Gotoxy(0, h);
        std::cout << R"(║)";
        UI::Gotoxy(WIDTH - 1, h);
        std::cout << R"(║)";
        if (h > MIDDLE_Y)
        {
            Gotoxy(SUB_DIVIDER_X, h);
            std::cout << R"(║)";
        }
    }
    UI::Gotoxy(SUB_DIVIDER_X, SUB_DIVIDER_Y);
    std::cout << R"(╠═══════════════════════════════════════════════════════════════════╣)";
    UI::Gotoxy(0, 39);
}
void UI::PrintTitle()
{
    int y = 3;

    UI::Gotoxy(2, y++); std::cout << "   ::                                                                                                                                         ";
    UI::Gotoxy(2, y++); std::cout << "    -.                                                                                                                                        ";
    UI::Gotoxy(2, y++); std::cout << "    -.                                         .-       ..                      ..                                      .     .               ";
    UI::Gotoxy(2, y++); std::cout << "    -.                  :.=:.  ..+..        .:-::.:-     ...=---=:     ..==:--=..-    ---.:....:--..-         :..::::::.+.      .. -.. ...    ";
    UI::Gotoxy(2, y++); std::cout << "    +.                 ..:        -..      .:             -.      :.  ::       :-     =         ..:           ....              .. .     .:.. ";
    UI::Gotoxy(2, y++); std::cout << "    #=-              -..:          +. .   -..              :      ..  ..       :              .. =             . .              .: :      ....";
    UI::Gotoxy(2, y++); std::cout << "    #*=              +**.          +=-.    +=                     ..  ::                    ...:*              -:.     .        ....     .=+. ";
    UI::Gotoxy(2, y++); std::cout << "    #+-.             #++.          =**=      ` =-:::.             -   :.                    =***               .**: ... -=       .*+:.*+**.    ";
    UI::Gotoxy(2, y++); std::cout << "    %+-              -++:          ===:          :-==:            :-. =-                 :+=+:                .++-              :+=:          ";
    UI::Gotoxy(2, y++); std::cout << "    %=:               +=.          ::-            ---            :=. +=               :-==-           .      .--:              :=-:          ";
    UI::Gotoxy(2, y++); std::cout << "   .*:..              .#:..       ::*             .-:-            :-. =              .:===.         ..=       .:::       .-     .::-          ";
    UI::Gotoxy(2, y++); std::cout << "  ::::............      .=*..  ..*-        .-*:...#::              :  =             ...:::::::::......:       ::-::----:::     :.:::.         ";
    UI::Gotoxy(2, y++); std::cout << "                                                                   +  -                                                                       ";
    UI::Gotoxy(2, y++); std::cout << "                                                                  =  =.                                                                       ";
    UI::Gotoxy(2, y++); std::cout << "                                                                   =  :                                                                       ";

}
void UI::PrintIntro()
{
    UI::PrintMain();
    UI::PrintTown();
    UI::Gotoxy(2, 22);
    std::cout << "평화로운 내일배움캠프 마을..." << std::endl;
    UI::Gotoxy(2, 23);
    std::cout << "어느 날 ZEP 회사에서 포인트 제도를 폐지하고..." << std::endl;
    UI::Gotoxy(2, 24);
    std:cout << "그에 항의하던 매니저님들, 튜터님들을 납치했다!!" << std::endl;
    UI::Gotoxy(2, 25);
    system("pause");
    system("cls");
    UI::PrintMain();
    UI::PrintBuilding();
    UI::Gotoxy(2, 22);
    std::cout << "당신은 납치당한 사람들과 포인트를 되찾기 위해 ZEP 빌딩을 오르기로 한다..." << std::endl;
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
    UI::Gotoxy(10, 2);  std::cout << "                  ---          " << std::endl;
    UI::Gotoxy(10, 3);  std::cout << "                /     \\        " << std::endl;
    UI::Gotoxy(10, 4);  std::cout << "                ((o_o))        " << std::endl;
    UI::Gotoxy(10, 5);  std::cout << "                \\     /        " << std::endl;
    UI::Gotoxy(10, 6);  std::cout << "              -(|    |)-       " << std::endl;
    UI::Gotoxy(10, 7);  std::cout << "             ( |      | )      " << std::endl;
    UI::Gotoxy(10, 8);  std::cout << "             | |      | |      " << std::endl;
    UI::Gotoxy(10, 9);  std::cout << "             (_|______|_)      " << std::endl;
    UI::Gotoxy(10, 10); std::cout << "                | ___ |        " << std::endl;
    UI::Gotoxy(10, 11); std::cout << "  /\\ =^._.^=    | | | |        " << std::endl;
    UI::Gotoxy(10, 12); std::cout << "    \\ |   |     | | | |        " << std::endl;
    UI::Gotoxy(10, 13); std::cout << "     \\|___|    (__| |__)       " << std::endl;

}
void UI::NPC_K()
{
    UI::Gotoxy(10, 2);  std::cout << "                    /\\" << std::endl;
    UI::Gotoxy(10, 3);  std::cout << "                   /  \\" << std::endl;
    UI::Gotoxy(10, 4);  std::cout << "                  /    \\" << std::endl;
    UI::Gotoxy(10, 5);  std::cout << "                 /      \\" << std::endl;
    UI::Gotoxy(10, 6);  std::cout << "         ____   /________\\    ____" << std::endl;
    UI::Gotoxy(10, 7);  std::cout << "        (    \\   (  o.o  )   /    )" << std::endl;
    UI::Gotoxy(10, 8);  std::cout << "         \\    \\   \\  =  /   /    /" << std::endl;
    UI::Gotoxy(10, 9);  std::cout << "          \\    \\  /`---'\\  /    /" << std::endl;
    UI::Gotoxy(10, 10); std::cout << "           \\    \\/   |   \\/    /" << std::endl;
    UI::Gotoxy(10, 11); std::cout << "            /   /|   |   |\\   \\" << std::endl;
    UI::Gotoxy(10, 12); std::cout << "           (   ( |   |   | )   )" << std::endl;
    UI::Gotoxy(10, 13); std::cout << "           /    \\|   |   |/    \\" << std::endl;
    UI::Gotoxy(10, 14); std::cout << "          /     /|___|___|\\     \\" << std::endl;
    UI::Gotoxy(10, 15); std::cout << "         (____ /  /     \\  \\_____)" << std::endl;
    UI::Gotoxy(10, 16); std::cout << "                 /       \\" << std::endl;
    UI::Gotoxy(10, 17); std::cout << "                |    |    |" << std::endl;
    UI::Gotoxy(10, 18); std::cout << "                |    |    |" << std::endl;
    UI::Gotoxy(10, 19); std::cout << "               (_____|_____)" << std::endl;
}




