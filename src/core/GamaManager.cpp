#include "core/GamaManager.h"


//임시 메뉴 출력 함수. todo: UIManager::PrintMenu() 수정
void PrintMenu(std::vector<std::string> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == "게임종료" || v[i] == "뒤로가기")
			std::cout << "0. " << v[i] << std::endl;
		else
			std::cout << i + 1 << ". " << v[i] << std::endl;
	}
}

//임시 아이템 출력 함수. todo: UIManager로 이식
void PrintItems(std::vector<Item> items)
{
	for (int i = 0; i < items.size(); i++)
	{
		printf("%d. %s(%d zem)\n", i + 1, items[i].Name.c_str(), items[i].Price);
	}
}

void CreateCharacter(GameManager* gm, UI& um, Player*& p)
{
	//���� //UIManager::PrintMessage(const std::string& str) 
	//���� //um.PrintMessage("�̸��� �Է��ϼ���: ");

	//string UIManager::InputString(const std::string& str) �ʿ�
	std::string name = "";
	name = um.InputSelection("당신은 누구십니까? ");
	//um.PrintMessage("직업을 선택하세요: ");
	//um.PrintMenu({"힘이 센 훈련생", "머리가 좋은 훈련생", "팔이 긴 훈련생", "민첩한 훈련생", "게임종료"});
	PrintMenu({ "전사", "마법사", "궁수", "도적", "게임종료" }); //임시
	//p->SetJob(um.InputSelection());
	std::string selection = um.InputSelection("������ �����ϼ���: ");
	switch (stoi(selection))
	{
	case 1:
		p = new Warrior(name);
		p->SetJob("����"); //todo: ���� ��Ī ���� �� ���� ����
		break;
	case 2:
		p = new Magician(name);
		p->SetJob("������");
		break;
	case 3:
		p = new Archer(name);
		p->SetJob("�ü�");
		break;
	case 4:
		p = new Thief(name);
		p->SetJob("����");
		break;
	case 5:
		gm->SetCurrentState(GameManager::GameState::Exit);
		//um.PrintMessage("������ �����մϴ�!\n");
		break;
	default:
		//um.PrintMessage("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���\n");
		break;
	}
	//����� �α� 
	//std::cout << p->GetName() << std::endl;
	//std::cout << p->GetJob() << std::endl; 
	//system("pause");
}

void GameManager::HandleDungeon()
{
	//dm.StartDungeon();
	dm.StartDungeon(*player, um, im);
}

void GameManager::HandleStore()
{
	//sm.EnterShop(player, im);
	while (1)
	{
		std::cout << "(Debug)[store]" << std::endl;	//임시

		PrintMenu({ "상품구매", "상품판매", "뒤로가기" });	//임시
		std::string selection = um.InputSelection("입력: ");
		int s = stoi(selection);
		switch (s)
		{
		case 1:
		{
			std::cout << "(Debug)아이템 구매 루틴" << std::endl; //디버그용

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
			std::cout << "(Debug)아이템 판매 루틴" << std::endl; //디버그용
			//인벤토리 목록 출력
			//void UIManager::PrintItem(vector<Item> itmes) 함수 추가 요청
			std::vector<Item> items = iven.GetAllItems();
			if (items.size() < 1)
			{
				std::cout << "판매할 아이템이 없습니다" << std::endl;
				break;
			}

			PrintItems(items);
			std::cout << "===============" << std::endl;
			std::string s = um.InputSelection("몇번? ");
			int idx = stoi(s);

			if (idx > items.size())
			{
				std::cout << "입력이 잘못 되었습니다" << std::endl;
				break;
			}

			std::string n = um.InputSelection("몇개? ");
			int quantity = stoi(n);
			if (quantity > items[idx - 1].ItemCount)
			{
				std::cout << "수량이 부족합니다" << std::endl;
				break;
			}
			//Inventory::ReduceItem(int idx, int quantity) -- vector<Item>의 idx-1 번째 원소의 itemcount를 quantity 만큼 감소
			int gold = items[idx].Price * quantity;
			std::cout << "판매 완료 !" << gold << "zem을 획득했습니다" << std::endl;
			player->SetGold(player->GetGold() + gold);
			break;
		}
		case 0:
			std::cout << "메인 메뉴로 돌아갑니다" << std::endl;
			system("pause");//임시
			system("cls"); //임시
			return;

		default:
			std::cout << "입력이 잘못되었습니다" << std::endl;
			break;
		}
		system("cls");
	}
	system("pause");//임시
	system("cls"); //임시

}      

void GameManager::HandleInventory()	//todo: 인벤토리 형태에 대한 고민
{
	//um.PrintMenu({ "인벤토리 확인", "", "인벤토리 닫기"});
	//std::string selection = um.InputSelection("번호를 입력하세요: "); 
	//switch (stoi(selection))
	//{
	//case 1:
	//	im.PrintAllSummary();
	//	break;
	//case 2:
	//	im.PrintAllSummary();
	//	break;
	//}
	um.PrintStatus(player);
	std::cout << std::endl;
	im.PrintAllSummary();
	system("pause");//임시
	system("cls"); //임시
}

void GameManager::Run()
{
	system("mode con:cols=150 lines=40 | title LOSTZEP");

	//um.MainTitle();	//todo: ���ο� ��� �Լ��� ���濹��
	um.PrintMain();
	//um.PrintTitle();
	//um.PrintIntro();

	system("pause");//임시
	system("cls"); //임시
	CreateCharacter(this, um, player);

	system("pause");//임시
	system("cls"); //임시
	
	player->SetGold(10000);

	//UI::PrintStory();
	

	while (currentState != GameState::Exit)
	{
		currentState = GameState::MainMenu;
		//um.PrintMenu({"ZEP타워 입장","상점이용","인벤토리","종료"});
		PrintMenu({ "ZEP타워 입장","상점이용","인벤토리","게임종료" });
		std::string selection = um.InputSelection("번호를 입력하세요: ");
		switch (stoi(selection))
		{
		case 1:
			//std::cout << "던전 루틴 실행" << std::endl;	//디버그 로그
			currentState = GameState::Dungeon;
			HandleDungeon();
			break;

		case 2:
			std::cout << "(Debug)상점 이용 루틴" << std::endl;		//디버그 로그
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