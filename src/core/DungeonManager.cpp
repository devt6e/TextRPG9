癤#include "core/DungeonManager.h"
#include "core/UIManager.h"
#include "character/Player.h"
#include "character/M_Slime.h"
#include "character/M_Goblin.h"
#include "character/M_Orc.h"
#include "item/Item.h"
#include "item/Inventory.h"

#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
//
/*// 1.  깃린 以鍮
std::random_device rd;
std::mt19937 gen(rd());

// 2. 踰 ㅼ: 1遺 10源吏
std::uniform_int_distribution<int> dist(0, 4);

// 3.  レ 戮湲
int number = dist(gen);

std::cout << number << '\n';*/


DungeonManager::DungeonManager()
	: currentFloor(1),
	currentRoom(0),
	dungeonMap{},
	playerLoc{},
	bossLoc{},
	hasCheckpoint(false),
	checkpointLoc{},
	visitedMap{},
	hasNpcAppeared(false),
	clearedMap{},
	shouldExitDungeon(false)
{
	GenerateDungeonMap();
}
//ui留ㅻ�


int DungeonManager::GetMapWidth() const
{
	return MapWidth;
}

int DungeonManager::GetMapHeight() const
{
	return MapHeight;
}
/*
留 諛 醫  諛 
dungeonMap 媛 0  諛 
1  2  諛 
*/

bool DungeonManager::HasRoom(int x, int y) const
{
	if (x < 0 || x >= MapWidth ||
		y < 0 || y >= MapHeight)
	{
		return false;
	}

	return dungeonMap[x][y] != 0;
}
bool DungeonManager::IsRoomVisited(int x, int y) const
{
	if (!HasRoom(x, y))
	{
		return false;
	}

	return visitedMap[x][y];
}
bool DungeonManager::IsPlayerAt(int x, int y) const
{
	return x == playerLoc[0] &&
		y == playerLoc[1];
}
bool DungeonManager::IsBossAt(int x, int y) const
{
	return x == bossLoc[0] &&
		y == bossLoc[1];
}
bool DungeonManager::IsRoomVisible(int x, int y) const
{
	if (!HasRoom(x, y))
	{
		return false;
	}

	if (IsPlayerAt(x, y) ||
		IsBossAt(x, y) ||
		IsRoomVisited(x, y))
	{
		return true;
	}

	int distance =
		std::abs(x - playerLoc[0]) +
		std::abs(y - playerLoc[1]);

	return distance == 1;
}
void DungeonManager::GenerateDungeonMap()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> edgeDist(0, 3);
	std::uniform_int_distribution<int> xPositionDist(0, MapWidth - 1);
	std::uniform_int_distribution<int> yPositionDist(0, MapHeight - 1);

	int edge = edgeDist(gen);

	int playerXPosition = xPositionDist(gen);
	int playerYPosition = yPositionDist(gen);

	int bossXPosition = xPositionDist(gen);
	int bossYPosition = yPositionDist(gen);



	//i= 媛濡, j=몃
	for (int x = 0; x < MapWidth; x++)
	{
		for (int y = 0; y < MapHeight; y++)
		{
			dungeonMap[x][y] = 0;
		}
	}

	/*
	edge 0  player : , 0
	edge 1  player : , 4
	edge 2  player : 0, 
	edge 3  player : 4, 
	 */
	 // �댁댁 蹂댁 醫 寃곗

	switch (edge)
	{
	case 0: // �댁 履, 蹂댁 履
		playerLoc[0] = playerXPosition;
		playerLoc[1] = 0;

		bossLoc[0] = bossXPosition;
		bossLoc[1] = MapHeight - 1;
		break;

	case 1: // �댁 履, 蹂댁 履
		playerLoc[0] = playerXPosition;
		playerLoc[1] = MapHeight - 1;

		bossLoc[0] = bossXPosition;
		bossLoc[1] = 0;
		break;

	case 2: // �댁 쇱そ, 蹂댁 ㅻⅨ履
		playerLoc[0] = 0;
		playerLoc[1] = playerYPosition;

		bossLoc[0] = MapWidth - 1;
		bossLoc[1] = bossYPosition;
		break;

	case 3: // �댁 ㅻⅨ履, 蹂댁 쇱そ
		playerLoc[0] = MapWidth - 1;
		playerLoc[1] = playerYPosition;

		bossLoc[0] = 0;
		bossLoc[1] = bossYPosition;
		break;
	}
	int pathX = playerLoc[0];
	int pathY = playerLoc[1];

	while (pathX != bossLoc[0])
	{
		dungeonMap[pathX][pathY] = 1;

		if (pathX < bossLoc[0])
		{
			pathX++;
		}
		else
		{
			pathX--;
		}
	}
	while (pathY != bossLoc[1])
	{
		dungeonMap[pathX][pathY] = 1;

		if (pathY < bossLoc[1])
		{
			pathY++;
		}
		else
		{
			pathY--;
		}
	}
	// 醫 紐⑤ 寃곗 留듭 
	dungeonMap[playerLoc[0]][playerLoc[1]] = 1;
	visitedMap[playerLoc[0]][playerLoc[1]] = true;
	clearedMap[playerLoc[0]][playerLoc[1]] = true;
	dungeonMap[bossLoc[0]][bossLoc[1]] = 2;


	// ===== 留ㅻⅨ 諛   =====
	int branchStartX = -1;
	int branchStartY = -1;
	bool branchCreated = false;
	int branchCreatedCount = 0;

	for (int attempt = 0; attempt < 300; attempt++)
	{
		int randomX = xPositionDist(gen);
		int randomY = yPositionDist(gen);

		if (dungeonMap[randomX][randomY] != 1)
		{
			continue;
		}

		branchStartX = randomX;
		branchStartY = randomY;

		int direction = edgeDist(gen);
		/*
		0 = 대 遺媛
		1 = 대 媛ν 湲
		2 = 蹂댁ㅻ갑
		*/
		if (branchStartX != -1)
		{

			int branchX = branchStartX;
			int branchY = branchStartY;

			switch (direction)
			{
			case 0: // 
				branchY--;
				break;

			case 1: // 
				branchY++;
				break;

			case 2: // 쇱そ
				branchX--;
				break;

			case 3: // ㅻⅨ履
				branchX++;
				break;
			}
			if (branchX >= 0 &&
				branchX < MapWidth &&
				branchY >= 0 &&
				branchY < MapHeight)
			{
				//std::cout << "留듭\n";
				if (dungeonMap[branchX][branchY] == 0)
				{
					//std::cout << "踰쎌뭏.\n";
					int connectedPathCount = 0;
					if (branchX > 0 && dungeonMap[branchX - 1][branchY] != 0)
					{
						connectedPathCount++;
					}

					// ㅻⅨ履
					if (branchX < MapWidth - 1 &&
						dungeonMap[branchX + 1][branchY] != 0)
					{
						connectedPathCount++;
					}
					// 
					if (branchY > 0 &&
						dungeonMap[branchX][branchY - 1] != 0)
					{
						connectedPathCount++;
					}

					// 
					if (branchY < MapHeight - 1 &&
						dungeonMap[branchX][branchY + 1] != 0)
					{
						connectedPathCount++;
					}
					if (connectedPathCount == 1)
					{
						dungeonMap[branchX][branchY] = 1;
						branchCreatedCount++;
						branchCreated = true;

						if (branchCreatedCount >= 6)
						{
							break;
						}
					}

				}

			}

		}
	}
	/*std::cout << "branch count: "
		<< branchCreatedCount << '\n';
	std::cout << "branch created: "
		<< branchCreated << '\n';*/

		// ===== 留ㅻⅨ 諛   =====
		/*for (int j = 0; j < MapSize; j++)
		{
			for (int i = 0; i < MapSize; i++)
			{
				std::cout << dungeonMap[i][j] << " ";
			}

			std::cout << '\n';
		}*/
		/*
		std::cout << "edge: " << edge << '\n';
		std::cout << "position: " << position << '\n';
		std::cout << "player: "
			<< playerLoc[0] << ", "
			<< playerLoc[1] << '\n';
		std::cout << "boss: "
			<< bossLoc[0] << ", "
			<< bossLoc[1] << '\n';
		std::cout << "branch start: "
			<< branchStartX << ", "
			<< branchStartY << '\n';
			*/

}

void DungeonManager::StartDungeon(Player& player, UI& ui, InventoryManager& inventoryManager)
{
	shouldExitDungeon = false;
	// 泥댄ыъ명멸 쇰㈃ �λ 移 ㅼ 
	if (hasCheckpoint)
	{
		playerLoc[0] = checkpointLoc[0];
		playerLoc[1] = checkpointLoc[1];
	}

	//  移媛 蹂댁ㅻ갑   諛蹂
	while (dungeonMap[playerLoc[0]][playerLoc[1]] != 2)
	{
		ui.DisplayDungeonMap(*this);

		/*std::cout << "\n이동 가능한 방향: ";

		if (CanMoveTo(0))
		{
			std::cout << "W() ";
		}

		if (CanMoveTo(1))
		{
			std::cout << "S() ";
		}

		if (CanMoveTo(2))
		{
			std::cout << "A(쇱そ) ";
		}

		if (CanMoveTo(3))
		{
			std::cout << "D(ㅻⅨ履) ";
		}

		std::cout << "\nQ(마을로 복귀)\n";
		std::cout << "입력: ";*/
		ui.PrintDungeonMoveOptions(
			CanMoveTo(0),
			CanMoveTo(1),
			CanMoveTo(2),
			CanMoveTo(3));

		char input;
		std::cin >> input;

		int direction = -1;

		switch (input)
		{
		case 'w':
		case 'W':
			direction = 0;
			break;

		case 's':
		case 'S':
			direction = 1;
			break;

		case 'a':
		case 'A':
			direction = 2;
			break;

		case 'd':
		case 'D':
			direction = 3;
			break;

		case 'q':
		case 'Q':
			checkpointLoc[0] = playerLoc[0];
			checkpointLoc[1] = playerLoc[1];
			hasCheckpoint = true;

			std::cout
				<< "泥댄ыъ명몃� �ν怨 留濡 媛.\n";
			return;

		default:
			std::cout << "紐삳 �μ.\n";
			continue;
		}

		if (CanMoveTo(direction))
		{
			MoveRoom(direction);
			if (clearedMap[playerLoc[0]][playerLoc[1]] == false)
			{
				RoomType decideRoom = DecideRoomType();
				HandleRoom(player, decideRoom, inventoryManager);
				if (shouldExitDungeon)
				{
					std::cout << "寃 ㅻ.\n";
					return;
				}
			}

		}
		else
		{
			std::cout << "대   諛⑺μ.\n";
		}
	}

	ui.DisplayDungeonMap(*this);
	std::cout << "蹂댁ㅻ갑 李⑺듬.\n";
}

RoomType DungeonManager::DecideRoomType()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> ranNPC(0, 99);
	int npcAppeare = ranNPC(gen);

	int distanceToBoss =
		std::abs(playerLoc[0] - bossLoc[0]) +
		std::abs(playerLoc[1] - bossLoc[1]);

	if (playerLoc[0] == bossLoc[0] && playerLoc[1] == bossLoc[1])
	{
		return RoomType::Boss;
	}
	else if (hasNpcAppeared == false && (npcAppeare < 20 || distanceToBoss == 1))
	{
		hasNpcAppeared = true;
		return RoomType::NPC;
	}
	else
	{
		return RoomType::Monster;
	}

}

bool DungeonManager::CanMoveTo(int destination) const    // 紐⑹吏濡 대 媛?
{
	int nextX = playerLoc[0];
	int nextY = playerLoc[1];
	switch (destination)
	{
	case 0: //
		nextY--;
		break;

	case 1: //
		nextY++;
		break;

	case 2: //쇱そ
		nextX--;
		break;

	case 3: //ㅻⅨ
		nextX++;
		break;

	default:
		return false;
	}
	if (nextX < 0 ||
		nextX >= MapWidth ||
		nextY < 0 ||
		nextY >= MapHeight)
	{
		return false;
	}
	return dungeonMap[nextX][nextY] != 0;
}
void DungeonManager::MoveRoom(int destination)    //  移 蹂寃
{
	if (!CanMoveTo(destination))
	{
		return;
	}
	switch (destination)
	{
	case 0: // 
		playerLoc[1]--;
		break;

	case 1: // 
		playerLoc[1]++;
		break;

	case 2: // 쇱そ
		playerLoc[0]--;
		break;

	case 3: // ㅻⅨ履
		playerLoc[0]++;
		break;
	}
	visitedMap[playerLoc[0]][playerLoc[1]] = true;
	std::cout << "moved player: "
		<< playerLoc[0] << ", "
		<< playerLoc[1] << '\n';
}
/*void DungeonManager::DisplayDungeonMap() const
{
	system("cls");
	auto IsVisible = [&](int x, int y)
		{
			if (x < 0 || x >= MapWidth ||
				 y < 0 || y >= MapHeight)
			{
				return false;
			}

			// 諛 泥닿 議댁ы吏 
			if (dungeonMap[x][y] == 0)
			{
				return false;
			}

			// �댁 移
			if (x == playerLoc[0] &&
				y == playerLoc[1])
			{
				return true;
			}

			// 蹂댁 移 � 
			if (x == bossLoc[0] &&
				y == bossLoc[1])
			{
				return true;
			}

			// 대� 諛⑸Ц 諛
			if (visitedMap[x][y])
			{
				return true;
			}

			// �댁댁 몄 諛
			int distance =
				std::abs(x - playerLoc[0]) +
				std::abs(y - playerLoc[1]);

			return distance == 1;
		};

	std::cout << "+---------------------------------+\n";
	std::cout << "|          ZEP TOWER - 1F         |\n";
	std::cout << "+---------------------------------+\n";
	std::cout << "|\n";

	for (int y = 0; y < MapSize; y++)
	{
		std::cout << "|  ";

		// 諛 異�
		for (int x = 0; x < MapSize; x++)
		{
			std::string symbol = "   ";

			if (x == playerLoc[0] &&
				y == playerLoc[1])
			{
				symbol = "[P]";
			}
			else if (x == bossLoc[0] &&
				y == bossLoc[1])
			{
				symbol = "[B]";
			}
			else if (visitedMap[x][y])
			{
				symbol = "[.]";
			}
			else if (IsVisible(x, y))
			{
				symbol = "[?]";
			}

			std::cout << symbol;

			// ㅻⅨ履 諛⑷낵 곌껐 쇰㈃ 媛濡 듬 異�
			if (x < MapSize - 1)
			{
				bool connected =
					dungeonMap[x][y] != 0 &&
					dungeonMap[x + 1][y] != 0 &&
					IsVisible(x, y) &&
					IsVisible(x + 1, y);

				if (connected)
				{
					std::cout << "---";
				}
				else
				{
					std::cout << "   ";
				}
			}
		}

		std::cout << "  |\n";

		// 履 諛⑷낵 곌껐 몃 듬 異�
		if (y < MapSize - 1)
		{
			std::cout << "|  ";

			for (int x = 0; x < MapSize; x++)
			{
				bool connected =
					dungeonMap[x][y] != 0 &&
					dungeonMap[x][y + 1] != 0 &&
					IsVisible(x, y) &&
					IsVisible(x, y + 1);

				if (connected)
				{
					std::cout << " | ";
				}
				else
				{
					std::cout << "   ";
				}

				if (x < MapSize - 1)
				{
					std::cout << "   ";
				}
			}

			std::cout << "  |\n";
		}
	}

	std::cout << "|\n";
	std::cout << "+---------------------------------+\n";
	std::cout << "| [P]  移   [B] 蹂댁        |\n";
	std::cout << "| [.]  猷   [?] 誘명 諛   |\n";
	std::cout << "+---------------------------------+\n";
}*/
void DungeonManager::HandleRoom(Player& player,
	RoomType roomType,
	InventoryManager& inventoryManager)    // 諛⑹ ㅼ닿 
{
	switch (roomType)
	{
	case(RoomType::Boss):
	{
		std::cout << "蹂댁ㅻ갑 !!\n";
		break;
	}
	case(RoomType::Monster):
	{
		std::cout << "紐ъㅽ 깆!!\n";
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> monsterDist(0, 2);
		int monsterType = monsterDist(gen);

		switch (monsterType)
		{
		case 0:
		{
			Slime slime(player.GetLevel());
			BattleResult battleResult = battleManager.StartBattle(player, slime, inventoryManager);
			HandleBattleResult(player, slime, battleResult, inventoryManager);
			break;
		}

		case 1:
		{
			Goblin goblin(player.GetLevel());
			BattleResult battleResult = battleManager.StartBattle(player, goblin, inventoryManager);
			HandleBattleResult(player, goblin, battleResult, inventoryManager);

			break;
		}

		case 2:
		{
			Orc orc(player.GetLevel());
			BattleResult battleResult = battleManager.StartBattle(player, orc, inventoryManager);
			HandleBattleResult(player, orc, battleResult, inventoryManager);

			break;
		}
		}
		break;
	}
	case(RoomType::NPC):
	{
		std::cout << "NPC 등장!!\n";
		DropRandomItem(inventoryManager);
		system("pause");
		clearedMap[playerLoc[0]][playerLoc[1]] = true;
		break;
	}
	}
}
void DungeonManager::HandleBattleResult(Player& player,
	Monster& monster,
	BattleResult result,
	InventoryManager& inventoryManager)
{
	switch (result)
	{
	case(BattleResult::Victory):
	{
		system("pause");

		std::cout << "�ъ 밸━듬.\n";
		clearedMap[playerLoc[0]][playerLoc[1]] = true;
		player.AddExp(monster.GetDropExp());
		player.SetGold(player.GetGold() + monster.GetDropGold());
		DropRandomItem(inventoryManager);

		std::cout << monster.GetDropGold() << " 怨⑤瑜 듬.\n";
		system("pause");

	}
	break;
	case(BattleResult::Defeat):
	{
		std::cout << "�ъ ⑤같듬.\n";
		shouldExitDungeon = true;
	}
	break;
	case(BattleResult::Escaped):
	{
		std::cout << "�ъ 留爾ㅼ듬.\n";

	}
	break;

	}
}

void DungeonManager::DropRandomItem(
	InventoryManager& inventoryManager)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	//  瑜濡 댄  
	// 100 ㅺ 爰쇰㈃ 諛 由ъ 댁 嫄곕 if (dropChance > 30) 30 100쇰
	//-------------------------------------------
	std::uniform_int_distribution<int> dropChanceDist(1, 100);
	int dropChance = dropChanceDist(gen);

	if (dropChance > 30)// 닿굅 30 -> 60쇰硫 60 瑜濡 
	{
		return;
	}
	//----------------------------------------------
	std::uniform_int_distribution<int> itemDist(0, 3);
	int itemType = itemDist(gen);

	switch (itemType)
	{
	case 0:
		inventoryManager.AddConsumable(HpPotion());
		break;

	case 1:
		inventoryManager.AddConsumable(MpPotion());
		break;

	case 2:
		inventoryManager.AddConsumable(TempABPotion());
		break;

	case 3:
		inventoryManager.AddConsumable(TempDEFPotion());
		break;
	}
}