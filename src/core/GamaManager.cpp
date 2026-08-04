#include "core/GamaManager.h"


////임시 메뉴 출력 함수. todo: UIManager::PrintMenu() 수정
//void PrintMenu(std::vector<std::string> v)
//{
//	for (int i = 0; i < v.size(); i++)
//	{
//		if (v[i] == "게임종료" || v[i] == "뒤로가기")
//			std::cout << "0. " << v[i] << std::endl;
//		else
//			std::cout << i + 1 << ". " << v[i] << std::endl;
//	}
//}

////임시 아이템 출력 함수. todo: UIManager로 이식
//void PrintItems(std::vector<Item> items)
//{
//	for (int i = 0; i < items.size(); i++)
//	{
//		printf("%d. %s(%d zem)\n", i + 1, items[i].Name.c_str(), items[i].Price);
//	}
//}

void CreateCharacter(GameManager* gm, UI& um, Player*& p)
{
	//보류 //UIManager::PrintMessage(const std::string& str) 
	//보류 //um.PrintMessage("이름을 입력하세요: ");

	std::string name = "";
	name = um.InputString("당신은 누구십니까? ");
	um.PrintSelection({"열정 가득 수강생", "TIL 우수 작성 수강생", "슬랙 이모지 잘 누르는 수강생", "게임종료"});
	int selection = um.InputSelection("직업을 선택하세요: ");
	switch (selection)	//todo: P_Job 수정 중. 수정 하면 반영 예정
	{
	case 1:
		p = new Warrior(name);
		p->SetJob("열정 가득 수강생"); //todo: 직업 명칭 변경 시 수정 예정
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
		//um.PrintMessage("게임을 종료합니다!\n");
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
	while (1)
	{
		um.PrintSelection({ "상품구매", "상품판매", "뒤로가기" });
		int selection = um.InputSelection("입력: ");
		switch (selection)
		{
		case 1:
		{
			//std::cout << "(Debug)아이템 구매 루틴" << std::endl; //디버그용
			um.PrintLog("(Debug)아이템 구매 루틴 실행");

			//vector<Item> ShopManager::GetItems() 함수 추가 요청
			//아이템 목록 출력
			//void UIManager::PrintItem(vector<Item> itmes) 함수 추가 요청

			/*
			for(int i = 0; i < items.size(); i++)
			{
				printf("%d. %s(%d zem)\n",i+1, items[i].Name.c_str(), items[i].Price);
			}
			*/
			sm.PrintShopItems();	//임시
			sm.BuyItem(player, im);
			//std::cout << "===============" << std::endl;
			//std::string idx = um.InputSelection("몇번? ");
			//std::string nBuy = um.InputSelection("몇개? ");
			//if(player->GetGold() > items[idx-1].Price*nBuy)
			//	im.AddItem(items[idx-1], nBuy);	//InventoryManager::AddItem(Item _item, int cnt) 함수 추가 요청
			//else
			//	std::cout << "젬이 부족합니다" << std::endl;
			system("pause");
			break;
		}
		case 2:
		{
			//std::cout << "(Debug)아이템 판매 루틴" << std::endl; //디버그용
			 um.PrintLog("(Debug)아이템 판매 루틴 실행");
			//인벤토리 목록 출력
			//void UIManager::PrintItem(vector<Item> itmes) 함수 추가 요청
			std::vector<Item> items = iven.GetAllItems();
			if (items.size() < 1)
			{
				//std::cout << "판매할 아이템이 없습니다" << std::endl;
				um.PrintLog("판매할 아이템이 없습니다");
				break;
			}

			//PrintItems(items);
			//std::cout << "===============" << std::endl;
			um.PrintSelection(items);
			int numberSelection = um.InputSelection("몇번? ");

			if (numberSelection > items.size())
			{
				//std::cout << "입력이 잘못 되었습니다" << std::endl;
				um.PrintLog("입력이 잘못 되었습니다");
				break;
			}

			int quantitySelection = um.InputSelection("몇개? ");
			if (quantitySelection > items[numberSelection - 1].ItemCount)
			{
				//std::cout << "수량이 부족합니다" << std::endl;
				um.PrintLog("수량이 부족합니다");
				break;
			}
			//Inventory::ReduceItem(int idx, int quantity) -- vector<Item>의 idx-1 번째 원소의 itemcount를 quantity 만큼 감소
			int gold = items[numberSelection - 1].Price * quantitySelection;
			//std::cout << "판매 완료 !" << gold << "zem을 획득했습니다" << std::endl;
			std::string s = "판매 완료 !" + std::to_string(gold) + "zem을 획득했습니다!";
			um.PrintLog(s);
			player->SetGold(player->GetGold() + gold);
			break;
		}
		case 0:
			//std::cout << "메인 메뉴로 돌아갑니다" << std::endl;
			um.PrintLog("메인 메뉴로 돌아갑니다");
			//system("pause");//임시
			//system("cls"); //임시
			return;

		default:
			//std::cout << "입력이 잘못되었습니다" << std::endl;
			um.PrintLog("입력이 잘못되었습니다");
			break;
		}
		//system("cls");
	}
	//system("pause");//임시
	//system("cls"); //임시

}      

void GameManager::HandleInventory()	//todo: 인벤토리 형태에 대한 고민
{
	um.PrintStatus(player);
	//std::cout << std::endl;
	im.PrintAllSummary();
}

void GameManager::Run()
{
	system("mode con:cols=150 lines=40 | title LOSTZEP");

	um.PrintMain();
	um.PrintTitle();
	system("pause");
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
		um.PrintSelection({"ZEP타워 입장","상점이용","인벤토리","종료하기"});
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
			//std::cout << "(Debug)상점 이용 루틴" << std::endl;		//디버그 로그
			currentState = GameState::Store;
			HandleStore();
			break;

		case 3:
			std::cout << "(Debug)인벤토리 루틴" << std::endl;		//디버그 로그
			currentState = GameState::Inventory;
			HandleInventory();
			break;

		case 0:
			currentState = GameState::Exit;
			break;

		default:
			std::cout << "입력이 잘못되었습니다!" << std::endl;
			break;
		}
	}

	if (currentState == GameState::Exit)
	{
		delete player;
		std::cout << "게임을 종료합니다!" << std::endl;
		return;
	}
}
