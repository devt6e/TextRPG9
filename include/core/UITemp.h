#include "core/UIManager.h"

#define ART_POS {2,2}
#define LOG_POS {2,22}
#define STAT_POS {81,22}
#define SELECT_POS {81,27}

#define OFFSET_L 2
#define OFFSET_R 81
#define OFFSET_T 3
#define OFFSET_M 22
#define OFFSET_B 27

class UITemp
{
public:
    UI um;
    void PrintMessage(std::string str)
    {
        cout << str;
    }

    void Gotoxy(int x, int y)
    {
        COORD pos = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }
    void Gotoxy(std::vector<int> coor)
    {
        COORD pos = { (SHORT)(coor[0]), (SHORT)(coor[1]) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }
    void PrintMain()
    {
        const int WIDTH = 149;
        const int HEIGHT = 34;
        const int MIDDLE_Y = 21;
        const int SUB_DIVIDER_X = 80;
        const int SUB_DIVIDER_Y = 26;
        //system("mode con:cols=150 lines=40 | title LOSTZEP");
        //DRAW TOP
        Gotoxy(0, 0);
        std::cout << R"(
╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
)";
        //DRAW MIDDLE
        Gotoxy(0, MIDDLE_Y);
        std::cout << R"(╠═══════════════════════════════════════════════════════════════════════════════╦═══════════════════════════════════════════════════════════════════╣
)";
        //DRAW BOTTOM
        Gotoxy(0, HEIGHT-1);
        std::cout << R"(╚═══════════════════════════════════════════════════════════════════════════════╩═══════════════════════════════════════════════════════════════════╝ 
)";
        for (int h = 1; h < HEIGHT -1; h++)
        {
            if (h == 1 || h == MIDDLE_Y)
            {
                continue;
            }
            Gotoxy(0, h);
            std::cout << R"(║)";
            Gotoxy(WIDTH-1, h);
            std::cout << R"(║)";
            if (h > MIDDLE_Y)
            {
                Gotoxy(SUB_DIVIDER_X, h);
                std::cout << R"(║)";
            }
        }
        Gotoxy(SUB_DIVIDER_X, SUB_DIVIDER_Y);
        std::cout << R"(╠═══════════════════════════════════════════════════════════════════╣)";
        Gotoxy(0, 39);
    }

    void PrintArt()
    {
        Gotoxy(ART_POS);
        PrintMessage("안녕하세요 저는 아스키아트 영역입니다\n");
        Gotoxy(10, 2);
        std::cout << R"(
     _   _      _ _        __        __         _     _ _ _
    | | | | ___| | | ___   \ \      / /__  _ __| | __| | | |
    | |_| |/ _ \ | |/ _ \   \ \ /\ / / _ \| '__| |/ _` | | |
    |  _  |  __/ | | (_) |   \ V  V / (_) | |  | | (_| |_|_|
    |_| |_|\___|_|_|\___/     \_/\_/ \___/|_|  |_|\__,_(_|_)      
        )" << std::endl;
    }

    void PrintLog()
    {
        Gotoxy(LOG_POS);
        PrintMessage("안녕하세요 저는 로그 영역입니다\n");
    }

    void PrintStat()
    {
        Gotoxy(STAT_POS);
        PrintMessage("안녕하세요 저는 스탯 영역입니다\n");
    }

    void PrintSelection()
    {
        Gotoxy(SELECT_POS);
        PrintMessage("안녕하세요 저는 선택 영역입니다\n");
    }

    void GotoEnd()
    {
        Gotoxy(0,35);
    }
};