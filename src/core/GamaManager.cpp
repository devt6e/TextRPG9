#include "../include/core/GamaManager.h"

void GameManager::HandleMainMenu()
{

}

void GameManager::HandleBattle()
{

}

void GameManager::HandleCrafting()
{

}      

void GameManager::HandleStatus()
{

}

void GameManager::Run()
{
	um.MainTitle();
	while (currentState != GameState::Exit)
	{
		um.PrintMenu({"던전 입장","스탯관리","제작소","종료"});
		//system("pause");
		std::string selection = um.InputSelection("번호를 입력하세요: ");
		switch (stoi(selection))
		{
		case 1:
			std::cout << "던전 루틴 실행" << std::endl;
			currentState = GameState::Dungeon;
			system("pause");
			break;
		case 2:
			std::cout << "스탯관리 루틴 실행" << std::endl;
			currentState = GameState::Dungeon;
			system("pause");
			break;
		case 3:
			std::cout << "제작소 루틴 실행" << std::endl;
			system("pause");
			break;
		case 0:
			std::cout << "게임 종료!" << std::endl;
			system("pause");
			return;
		default:
			std::cout << "입력 잘못됨!" << std::endl;
			system("pause");
			break;
		}
	}
}