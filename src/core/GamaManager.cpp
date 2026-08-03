#include "core/GamaManager.h"

//���� �ʿ� �� ���� ����
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
		um.PrintMenu({"��������","�κ��丮","���ۼ�","����"});
		std::string selection = um.InputSelection("��ȣ�� �Է��ϼ���: ");
		switch (stoi(selection))
		{
		case 1:
/*			std::cout << "���� ��ƾ ����" << std::endl;
			currentState = GameState::Dungeon;*/
			//����
			std::cout << "���� ��ƾ ����" << std::endl;
			dm.StartDungeon(*player, um);
			currentState = GameState::MainMenu;
			system("pause");
			break;
		case 2:
			std::cout << "�κ��丮 Ȯ��" << std::endl;
			currentState = GameState::Inventory;
			system("pause");
			break;
		case 3:
			std::cout << "���ۼ� ��ƾ ����" << std::endl;
			currentState = GameState::Crafting;
			system("pause");
			break;
		case 0:
			std::cout << "���� ����!" << std::endl;
			system("pause");
			return;
		default:
			std::cout << "�Է� �߸���!" << std::endl;
			system("pause");
			break;
		}
		currentState = GameState::MainMenu;
	}
}