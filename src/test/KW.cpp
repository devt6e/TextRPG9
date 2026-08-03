////경욱님 개발 테스트용 메인
////=======테스트절차=======
//// 1. src/core/main.cpp 전체주석처리(ctrl+a 하고 ctrl+/ 하기)
//// 2. 본인이름.cpp 에서 테스트 하기
//// 3. 오류없으면
//// 4. 본인이름.cpp 전체주석처리
//// 5. src/core/main.cpp 전체주석처리 해제(ctrl+a 하고 ctrl+/ 하기)
//// 6. 커밋하고 pr하기
//#include <iostream>
//#include <windows.h>
//#include <string>
//#include <cstdlib>
//#include <vector>
//#include "core/UIManager.h"
//#include"character/Player.h"
//#include"character/P_Warrior.h"
//#include "core/DungeonManager.h"
//
//int main()
//{
//	Player* p = new Warrior("test");
//	DungeonManager dungeon;
//	SetConsoleOutputCP(CP_UTF8);
//	SetConsoleCP(CP_UTF8);
//	system("mode con:cols=150 lines=40 | title LOSTZEP");
//	UI ui;
//	ui.PrintIntro();
//	ui.PrintStatus(p);
//	
//	system("pause");
//	ui.DisplayDungeonMap(dungeon);
//	system("pause");
//	return 0;
//
//}