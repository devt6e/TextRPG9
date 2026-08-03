#include <iostream>

#include "core/GamaManager.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);  // 콘솔 "출력" 해석 방식을 UTF-8로
	//SetConsoleCP(CP_UTF8);	      // 콘솔 "입력" 해석 방식도 UTF-8로
	GameManager().Run();
}