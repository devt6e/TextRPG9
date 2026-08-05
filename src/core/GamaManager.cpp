#include "core/GamaManager.h"

void CreateCharacter(GameManager* gm, UI& um, Player*& p)
{
	//보류 //UIManager::PrintMessage(const std::string& str) 
	//보류 //um.PrintMessage("이름을 입력하세요: ");

	std::string name = "";
	name = um.InputString("당신은 누구십니까? ");

	um.PrintSelection({"열정 가득 수강생", "TIL 우수 작성 수강생", "슬랙 이모지 잘 누르는 수강생", "게임종료"});
	int selection = um.InputSelection("직업을 선택하세요: ");
	switch (selection)	   
	{
	case 1:
		p = new Warrior(name);
		p->SetJob("열정 가득 수강생");
		break;
	case 2:
		p = new Magician(name);
		p->SetJob("TIL 우수 작성 수강생");
		break;
	case 3:
		p = new Thief(name);
		p->SetJob("슬랙 이모지 잘 누르는 수강생");
		break;
	case 0:
		gm->SetCurrentState(GameManager::GameState::Exit);
		break;
	default:
		um.PrintLog("잘못된 입력입니다. 다시 입력하세요\n");
		break;
	}
}

void GameManager::HandleDungeon()
{
	dm.StartDungeon(*player, um, im);
}

void GameManager::HandleStore()
{
	sm.EnterShop(player,im);
}      

void GameManager::HandleInventory()
{
	um.EraseStat();
	im.PrintAllSummary();

	um.PrintSelection({ "소비아이템", "재료 아이템", "뒤로가기" });
	int sel = um.InputSelection("확인할 가방을 선택하세요: ");
	while (sel < 0 || sel > 2)
	{
		sel = um.InputSelection("입력이 잘못되었습니다 다시 입력하세요: ");
	}
	if (sel == 0)
	{
		um.PrintLog("돌아갑니다");
		return;
	}

	Inventory<Item>& items = sel == 1
		? im.GetConsumableBag()
		: im.GetMaterialBag();
	if (items.GetAllItems().empty())
	{
		um.PrintLog("가방이 텅 비었습니다");
		return;
	}
	um.PrintSelection(items.GetAllItems());
	while (true)
	{
		int n = um.InputSelection("확인할 아이템 번호 (0: 돌아가기): ");
		if (n == 0)
		{
			um.EraseStat();
			return;
		}

		Item* selectedItem = items.GetItem(n);
		if (selectedItem == nullptr)
		{
			um.PrintLog("존재하지 않는 아이템 번호입니다."); // ysg: 없는 슬롯 선택 시 nullptr 역참조 방지
			continue;
		}

		um.EraseLog();
		//um.PrintLog(selectedItem->ItemDescription);
		items.PrintItemDetail(n);
		break;
	}

	//um.PrintSelection({"아이템 사용", "아이템 확인", "뒤로가기"});

	um.WaitForAnyKey("확인을 마치려면 아무 키나 입력하세요: ");
	um.EraseStat();
}

void GameManager::Run()
{
	system("mode con:cols=150 lines=40 | title LOSTZEP");

	um.PrintMain();
	um.PrintTitle();
	um.Pause();
	um.PrintIntro();

	CreateCharacter(this, um, player);
	if (player == nullptr)
	{
		return;
	}

	//player->SetGold(10000);

	while (currentState != GameState::Exit)
	{
		currentState = GameState::MainMenu; 
		um.PrintStatus(player);
		um.PrintSelection({"ZEP타워 입장","상점이용","인벤토리","게임종료"});
		int selection = um.InputSelection("번호를 입력하세요: ");
		switch (selection)
		{
		case 1:
			std::cout << "던전 루틴 실행" << std::endl;
			currentState = GameState::Dungeon;
			HandleDungeon();
			if (dm.HasDefeatedFinalBoss())
			{
				currentState = GameState::Exit;
				break;
			}
			if (player->GetHp() <= 0)
			{
				std::cout << "게임을 종료합니다.\n";
				return;
			}
			break;

		case 2:
			currentState = GameState::Store;
			HandleStore();
			break;

		case 3:
			currentState = GameState::Inventory;
			HandleInventory();
			um.EraseStat();
			break;

		case 0:
			currentState = GameState::Exit;
			break;

		default:
			//std::cout << "입력이 잘못되었습니다!" << std::endl;
			um.PrintLog("입력이 잘못되었습니다!");
			break;
		}
	}

	if (currentState == GameState::Exit)
	{
		delete player;
		if (!dm.HasDefeatedFinalBoss())
		{
			um.PrintLog("게임을 종료합니다!"); // ysg: 엔딩 출력 뒤 일반 종료 문구가 붙어서 중복 출력되지 않도록 처리
		}
		return;
	}
}
