#include "core/GamaManager.h"

//todo: 
//void GameManager::HandleMainMenu()
//{
//
//}

/*
* 
//선언
void PrintMessage(const std::string&);

//정의
void UI::PrintMessage(const std::string& str) { std::cout << str; }

*/

void CreateCharacter(GameManager* gm, UI& um, Player*& p)
{
	//보류 //UIManager::PrintMessage(const std::string& str) 
	//보류 //um.PrintMessage("이름을 입력하세요: ");

	//string UIManager::InputString(const std::string& str) 필요
	std::string name = "";
	name = um.InputSelection("이름을 입력하세요: ");
	//um.PrintMessage("직업을 선택하세요: ");
	um.PrintMenu({"전사", "마법사", "궁수", "도적", "종료"});
	//p->SetJob(um.InputSelection());
	std::string selection = um.InputSelection("직업을 선택하세요: ");
	switch (stoi(selection))
	{
	case 1:
		p = new Warrior(name);
		p->SetJob("전사"); //todo: 직업 명칭 변경 시 수정 예정
		break;
	case 2:
		p = new Magician(name);
		p->SetJob("마법사");
		break;
	case 3:
		p = new Archer(name);
		p->SetJob("궁수");
		break;
	case 4:
		p = new Thief(name);
		p->SetJob("도적");
		break;
	case 5:
		gm->SetCurrentState(GameManager::GameState::Exit);
		//um.PrintMessage("게임을 종료합니다!\n");
		break;
	default:
		//um.PrintMessage("잘못된 입력입니다. 다시 입력하세요\n");
		break;
	}
	//디버깅 로그 
	//std::cout << p->GetName() << std::endl;
	//std::cout << p->GetJob() << std::endl; 
	//system("pause");
}

void GameManager::HandleDungeon()
{
	//dm.StartDungeon();
	dm.StartDungeon(*player, um, im);
}

void GameManager::HandleCrafting()
{

}      

void GameManager::HandleStatus()
{

}

void GameManager::HandleInventory()
{
	um.PrintMenu({ "인벤토리 확인", });
}

void GameManager::Run()
{
	system("mode con:cols=150 lines=40 | title LOSTZEP");

	//um.MainTitle();	//todo: 새로운 출력 함수로 변경예정
	um.PrintMain();
	um.PrintTitle();

	CreateCharacter(this, um, player);
	//UI::PrintStory();


	while (currentState != GameState::Exit)
	{
		um.PrintMenu({"던전입장","인벤토리","스탯관리", "제작소","종료"});
		std::string selection = um.InputSelection("번호를 입력하세요: ");
		switch (stoi(selection))
		{
		case 1:
			std::cout << "던전 루틴 실행" << std::endl;
			dm.StartDungeon(*player, um, im);
			if (player->GetHp() <= 0)
			{
				std::cout << "게임을 종료합니다.\n";
				return;
			}
			currentState = GameState::Dungeon;
			system("pause");
			break;
		case 2:
			std::cout << "인벤토리 확인 루틴 실행" << std::endl;
			currentState = GameState::Inventory;
			system("pause");
			break;
		case 3:
			std::cout << "handle status 루틴 실행" << std::endl;
			currentState = GameState::Status;
			system("pause");
			break;
		case 4:
			std::cout << "handle crafting 루틴 실행" << std::endl;
			currentState = GameState::Crafting;
			system("pause");
			break;

		case 0:
			std::cout << "게임을 종료합니다!" << std::endl;
			system("pause");
			return;
		default:
			std::cout << "입력이 잘못되었습니다!" << std::endl;
			system("pause");
			break;
		}
		currentState = GameState::MainMenu;
	}
}