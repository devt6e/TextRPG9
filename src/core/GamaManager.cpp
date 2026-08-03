#include "core/GamaManager.h"

//추후 필요 시 구현 예정
//void GameManager::HandleMainMenu()
//{
//
//}

void GameManager::CreateCharacter()
{

}

void GameManager::HandleDungeon()
{
	//dm.StartDungeon();
}

void GameManager::HandleCrafting()
{

}      

void GameManager::HandleStatus()
{

}

void GameManager::Run()
{
	system("mode con:cols=150 lines=40 | title LOSTZEP");
	um.MainTitle();

	while (currentState != GameState::Exit)
	{
		um.PrintMenu({"던전입장","인벤토리","제작소","종료"});
		std::string selection = um.InputSelection("번호를 입력하세요: ");
		switch (stoi(selection))
		{
		case 1:
			std::cout << "던전 루틴 실행" << std::endl;
			currentState = GameState::Dungeon;
			//bm.StartBattle();
			HandleDungeon();
			system("pause");
			break;
		case 2:
			std::cout << "인벤토리 확인" << std::endl;
			currentState = GameState::Inventory;
			system("pause");
			break;
		case 3:
			std::cout << "제작소 루틴 실행" << std::endl;
			currentState = GameState::Crafting;
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
		currentState = GameState::MainMenu;
	}
}