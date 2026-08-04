#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <sstream> // ysg: 숫자 입력 문자열이 올바른 정수인지 검사하기 위해 추가
#include "core/UIManager.h"
#include "core/DungeonManager.h"
#include "character/Player.h"
#define ART_POS {2,2}
#define LOG_POS {2,22}
#define STAT_POS {81,22}
#define SELECT_POS {81,27}
#define ART_MAX_Y 19
#define LOG_MAX_Y 32
#define STAT_MAX_Y 25
#define SELECTION_MAX_Y 32
//art x: 1~146, y: 2~19 u.Erase({ 1, 2 }, 147, 19);
//log x: 1~78, y: 22~32 u.Erase({ 1, 22 }, 79, 11);
//stat x: 81~146, y: 22~25 u.Erase({ 81, 22 }, 67, 4);
//selection x: 81~146, y: 27~32 u.Erase({ 81, 27 }, 67, 6);
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
    Offsets = SELECT_POS;
    Gotoxy(Offsets[0], Offsets[1]);
    std::cout << "이동 가능한 방향: ";

    std::vector<std::string> moveOptions; // ysg: 실제 이동 가능한 방향만 모아서 출력하기 위해 추가
    if (canMoveUp) moveOptions.push_back("W(위)");
    if (canMoveDown) moveOptions.push_back("S(아래)");
    if (canMoveLeft) moveOptions.push_back("A(왼쪽)");
    if (canMoveRight) moveOptions.push_back("D(오른쪽)");

    if (moveOptions.size() == 4) // ysg: 4방향을 한 줄씩 출력하면 선택창을 벗어나므로 두 개씩 배치
    {
        Gotoxy(Offsets[0], ++Offsets[1]);
        std::cout << moveOptions[0] << "  " << moveOptions[1];
        Gotoxy(Offsets[0], ++Offsets[1]);
        std::cout << moveOptions[2] << "  " << moveOptions[3];
    }
    else
    {
        for (const std::string& option : moveOptions)
        {
            Gotoxy(Offsets[0], ++Offsets[1]);
            std::cout << option;
        }
    }

    Gotoxy(Offsets[0], ++Offsets[1]); // ysg: 마을 복귀 선택지와 실제 입력 칸을 서로 다른 줄에 표시
    std::cout << "Q(마을로 복귀)";
    Gotoxy(Offsets[0], ++Offsets[1]);
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
void UI::Erase(std::vector<int> coord, int rangeX, int rangeY)
{
    for (int h = 0; h < rangeY; h++)
    {
        Gotoxy(coord[0], coord[1] + h);
        for (int w = 0; w < rangeX; w++)
            std::cout << " ";
    }
}

void UI::EraseArt() {Erase({ 1, 2 }, 147, 19);}
void UI::EraseLog() { Erase({ 1, 22 }, 79, 11); }
void UI::EraseSelection() { Erase({ 81, 27 }, 67, 6); }
void UI::EraseStat() { Erase({ 81, 22 }, 67, 4); } 

void UI::PrintStatus(Player* p)
{
    Offsets = STAT_POS;
    UI::Gotoxy(Offsets[0], Offsets[1]);
    std::cout << u8"이름: " << p->GetName() << u8"  직업: " << p->GetJob() << "  Lv: " << p->GetLevel();
    UI::Gotoxy(Offsets[0], ++Offsets[1]);
    std::cout << "HP: " << p->GetHp() << "/" << p->GetMaxHp() << "  MP: " << p->GetMp() << "/" << p->GetMaxMp() << u8"  공격력: " << p->GetPower() << u8"  방어력: " << p->GetDefence() << std::endl;
    UI::Gotoxy(1, 24);
}
void UI::PrintInventory(std::vector<std::string> Inv)
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
void UI::PrintInventory(std::vector<Item> Inv, std::string str, int offset)
{
    Offsets = STAT_POS;
    Offsets[1] += offset;
    UI::Gotoxy(Offsets[0], Offsets[1]++);
    std::cout << str;
    UI::Gotoxy(Offsets[0], Offsets[1]++);
    for (int i = 0; i < Inv.size(); ++i)
    {
        std::cout << i + 1 << "). " << Inv[i].Name << "(" << Inv[i].Price <<")";
        if ((i + 1) % 3 == 0)
        {
            Gotoxy(Offsets[0], ++Offsets[1]);
        }
    }
}

void UI::PrintSelection(std::vector<std::string> menu)
{
    EraseSelection();
    for (int i = 0; i < menu.size(); ++i)
    {
        Gotoxy(81, 27 + i);
        if (menu[i] == "종료하기" || menu[i] == "뒤로가기")
        {
            std::cout << "0)." << menu[i] << std::endl;
            break;
        }
        std::cout << i + 1 << ")." << menu[i] << std::endl;
    }
}
void UI::PrintSelection(std::vector<Item> menu)
{
    EraseSelection();
    for (int i = 0; i < menu.size(); ++i)
    {
        Gotoxy(81, 27 + i);
        if (menu[i].Name == "종료하기" || menu[i].Name == "뒤로가기")
        {
            std::cout << "0)." << menu[i].Name << "(" << menu[i].Price << ")" << std::endl;
            break;
        }
        std::cout << i + 1 << ")." << menu[i].Name << "(" << menu[i].Price << ")" << std::endl;
    }
}
void UI::PrintLog(const std::string& str)
{
    static int n = 0;
    Offsets = LOG_POS;
    if (Offsets[1] + n >= LOG_MAX_Y)
    {
        n = 0;
        //UI::Erase(LOG_POS, 78, 11);
        EraseLog();
    }
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
    Gotoxy(0, 35);
}
void UI::PrintIntro()
{
    EraseArt();
    UI::PrintMain();
    UI::PrintTown();
    UI::Gotoxy(2, 22);
    std::cout << "평화로운 내일배움캠프 마을..." << std::endl;
    UI::Gotoxy(2, 23);
    std::cout << "어느 날 ZEP 회사에서 포인트 제도를 폐지하고..." << std::endl;
    UI::Gotoxy(2, 24);
    std::cout << "그에 항의하던 매니저님들, 튜터님들을 납치했다!!" << std::endl;
    UI::Gotoxy(2, 25);
    system("pause");
    system("cls");
    UI::PrintMain();
    UI::PrintBuilding();
    UI::Gotoxy(2, 22);
    std::cout << "당신은 납치당한 사람들과 포인트를 되찾기 위해 ZEP 빌딩을 오르기로 한다..." << std::endl;
    UI::Gotoxy(2, 23);
    system("pause");
    system("cls");
    UI::PrintMain();
    PrintTitle();
}
void UI::PrintArt(std::string_view s)
{
    Offsets = ART_POS;
    Gotoxy(Offsets[0], Offsets[1]);
    std::cout << s;
}

int UI::InputSelection(std::string text)
{
    while (true) // ysg: 문자를 입력해도 프로그램이 종료되지 않고 다시 입력받도록 반복
    {
        Offsets = SELECT_POS;   //LOG_POS -> SELECT_POS 변경
        UI::Gotoxy(Offsets[0], Offsets[1] + 5);
        std::cout << text;

        std::string input;
        if (!std::getline(std::cin >> std::ws, input)) // ysg: 입력 한 줄 전체를 받아 1abc 같은 입력도 차단
        {
            std::cin.clear();
            continue;
        }

        std::istringstream inputStream(input); // ysg: 입력값이 정수 하나로만 구성됐는지 검사
        int selection;
        char extraCharacter;

        if ((inputStream >> selection) && !(inputStream >> extraCharacter))
        {
            return selection;
        }

        PrintLog("숫자만 입력해주세요.");
    }
}
std::string UI::InputString(std::string text)
{
    std::string s;
    if (!text.empty()) // ysg: 빈 문자열이면 WASD 메뉴에서 지정한 현재 커서 위치를 유지
    {
        Offsets = SELECT_POS;   //LOG_POS->SELECT_POS 로 수정
        UI::Gotoxy(Offsets[0], Offsets[1]);
        std::cout << text;
    }
    //Offsets = SELECT_POS;                 //입력의 자연스러움을 위해 수정
    //UI::Gotoxy(Offsets[0], Offsets[1]);   //입력의 자연스러움을 위해 수정
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




