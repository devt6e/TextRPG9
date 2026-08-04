//#include "core/UITemp.h"
//
//int main()
//{
//	system("mode con:cols=150 lines=40 | title LOSTZEP");
//	SetConsoleOutputCP(CP_UTF8);
//	SetConsoleCP(CP_UTF8);
//
//	UITemp u;
//	
//	
//	
//	u.PrintArt();
//	u.PrintLog();
//	u.PrintSelection();
//	u.PrintStat();
//	u.PrintAscii();
//	system("pause");
//	
//	u.PrintMain();
//
//	//art x: 1~146, y: 2~19
//	u.Erase({ 1, 2 }, 147, 19);
//	//log x: 1~79, y: 22~32
//	u.Erase({ 1, 22 }, 79, 11);
//	//stat x: 81~146, y: 22~25
//	u.Erase({ 81, 22 }, 67, 4);
//	//selection x: 81~146, y: 27~32 
//	u.Erase({ 81, 27 }, 67, 6);
//
//	u.GotoEnd();
//}