#include "core/DungeonManager.h"
#include "core/UIManager.h"

#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
//
/*// 1. 랜덤 생성기 준비
std::random_device rd;
std::mt19937 gen(rd());

// 2. 범위 설정: 1부터 10까지
std::uniform_int_distribution<int> dist(0, 4);

// 3. 랜덤 숫자 뽑기
int number = dist(gen);

std::cout << number << '\n';*/
//-----------------------게임매니저용 임시--------------------------------------
/* cpp용
			case 1:
			std::cout << "던전 루틴 실행" << std::endl;
			dm.StartDungeon(player, um);
			currentState = GameState::MainMenu;
			//currentState = GameState::Dungeon;
			//system("pause");
			break;
}
*/
/* 헤더용

private:
	BattleManager bm;
	DungeonManager dm;

	UI um;
	//Player player;
	Player player;*/

	//-----------------------게임매니저용 임시--------------------------------------


DungeonManager::DungeonManager()
	: currentFloor(1),
	currentRoom(0),
	dungeonMap{},
	playerLoc{},
	bossLoc{},
	hasCheckpoint(false),
	checkpointLoc{},
	visitedMap{},
	hasNpcAppeared(false)
{
	GenerateDungeonMap();
}
//ui매니저용


int DungeonManager::GetMapSize() const
{
	return MapSize;
}

/*
맵 밖 좌표 → 방 없음
dungeonMap 값이 0 → 방 없음
1 또는 2 → 방 있음
*/

bool DungeonManager::HasRoom(int x, int y) const
{
	if (x < 0 || x >= MapSize ||
		y < 0 || y >= MapSize)
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
	std::uniform_int_distribution<int> positionDist(0, MapSize - 1);
	int edge = edgeDist(gen);
	int position = positionDist(gen);
	int bossPosition = positionDist(gen);
	// 랜덤최신 버전?이라고함 ran()은 구버전이라고함 무튼 이게 더 좋은거같음



	//i= 가로, j=세로
	for (int i = 0; i < MapSize; i++)
	{
		for (int j = 0;j < MapSize; j++)
		{
			dungeonMap[i][j] = 0;
		}
	}

	/*
	edge 0 → player : 랜덤, 0
	edge 1 → player : 랜덤, 4
	edge 2 → player : 0, 랜덤
	edge 3 → player : 4, 랜덤
	 */
	 // 플레이어와 보스 좌표 결정

	switch (edge)
	{
	case 0:
		playerLoc[0] = position;
		playerLoc[1] = 0;

		bossLoc[0] = bossPosition;
		bossLoc[1] = MapSize - 1;

		break;

	case 1:
		playerLoc[0] = position;
		playerLoc[1] = MapSize - 1;

		bossLoc[0] = bossPosition;
		bossLoc[1] = 0;
		break;

	case 2:
		playerLoc[0] = 0;
		playerLoc[1] = position;

		bossLoc[0] = MapSize - 1;
		bossLoc[1] = bossPosition;
		break;

	case 3:
		playerLoc[0] = MapSize - 1;
		playerLoc[1] = position;

		bossLoc[0] = 0;
		bossLoc[1] = bossPosition;
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
	// 좌표 모두 결정 맵에 표시
	dungeonMap[playerLoc[0]][playerLoc[1]] = 1;
	visitedMap[playerLoc[0]][playerLoc[1]] = true;
	dungeonMap[bossLoc[0]][bossLoc[1]] = 2;


	// ===== 막다른 방 생성 시작 =====
	int branchStartX = -1;
	int branchStartY = -1;
	bool branchCreated = false;
	int branchCreatedCount = 0;

	for (int attempt = 0; attempt < 100; attempt++)
	{
		int randomX = positionDist(gen);
		int randomY = positionDist(gen);

		if (dungeonMap[randomX][randomY] != 1)
		{
			continue;
		}

		branchStartX = randomX;
		branchStartY = randomY;

		int direction = edgeDist(gen);
		/*
		0 = 이동 불가
		1 = 이동 가능한 길
		2 = 보스방
		*/
		if (branchStartX != -1)
		{

			int branchX = branchStartX;
			int branchY = branchStartY;

			switch (direction)
			{
			case 0: // 위
				branchY--;
				break;

			case 1: // 아래
				branchY++;
				break;

			case 2: // 왼쪽
				branchX--;
				break;

			case 3: // 오른쪽
				branchX++;
				break;
			}
			if (branchX >= 0 &&
				branchX < MapSize &&
				branchY >= 0 &&
				branchY < MapSize)
			{
				//std::cout << "맵안\n";
				if (dungeonMap[branchX][branchY] == 0)
				{
					//std::cout << "벽칸.\n";
					int connectedPathCount = 0;
					if (branchX > 0 && dungeonMap[branchX - 1][branchY] != 0)
					{
						connectedPathCount++;
					}

					// 오른쪽
					if (branchX < MapSize - 1 &&
						dungeonMap[branchX + 1][branchY] != 0)
					{
						connectedPathCount++;
					}

					// 위
					if (branchY > 0 &&
						dungeonMap[branchX][branchY - 1] != 0)
					{
						connectedPathCount++;
					}

					// 아래
					if (branchY < MapSize - 1 &&
						dungeonMap[branchX][branchY + 1] != 0)
					{
						connectedPathCount++;
					}
					if (connectedPathCount == 1)
					{
						dungeonMap[branchX][branchY] = 1;
						branchCreatedCount++;
						branchCreated = true;
						if (branchCreatedCount >= 2)
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

		// ===== 막다른 방 생성 끝 =====
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

void DungeonManager::StartDungeon(Player& player, UI& ui)
{
	// 체크포인트가 있으면 저장된 위치에서 다시 시작
	if (hasCheckpoint)
	{
		playerLoc[0] = checkpointLoc[0];
		playerLoc[1] = checkpointLoc[1];
	}

	// 현재 위치가 보스방이 아닐 동안 반복
	while (dungeonMap[playerLoc[0]][playerLoc[1]] != 2)
	{
		ui.DisplayDungeonMap(*this);

		std::cout << "\n이동 가능한 방향: ";

		if (CanMoveTo(0))
		{
			std::cout << "W(위) ";
		}

		if (CanMoveTo(1))
		{
			std::cout << "S(아래) ";
		}

		if (CanMoveTo(2))
		{
			std::cout << "A(왼쪽) ";
		}

		if (CanMoveTo(3))
		{
			std::cout << "D(오른쪽) ";
		}

		std::cout << "\nQ(마을로 복귀)\n";
		std::cout << "입력: ";

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
				<< "체크포인트를 저장하고 마을로 돌아갑니다.\n";
			return;

		default:
			std::cout << "잘못된 입력입니다.\n";
			continue;
		}

		if (CanMoveTo(direction))
		{
			MoveRoom(direction);
		}
		else
		{
			std::cout << "이동할 수 없는 방향입니다.\n";
		}
	}

	ui.DisplayDungeonMap(*this);
	std::cout << "보스방에 도착했습니다.\n";
}

bool DungeonManager::CanMoveTo(int destination) const    // 목적지로 이동 가능?
{
	int nextX = playerLoc[0];
	int nextY = playerLoc[1];
	switch (destination)
	{
	case 0: //위
		nextY--;
		break;

	case 1: //아래
		nextY++;
		break;

	case 2: //왼쪽
		nextX--;
		break;

	case 3: //오른
		nextX++;
		break;

	default:
		return false;
	}
	if (nextX < 0 ||
		nextX >= MapSize ||
		nextY < 0 ||
		nextY >= MapSize)
	{
		return false;
	}
	return dungeonMap[nextX][nextY] != 0;
}
void DungeonManager::MoveRoom(int destination)    // 현재 위치 변경
{
	if (!CanMoveTo(destination))
	{
		return;
	}
	switch (destination)
	{
	case 0: // 위
		playerLoc[1]--;
		break;

	case 1: // 아래
		playerLoc[1]++;
		break;

	case 2: // 왼쪽
		playerLoc[0]--;
		break;

	case 3: // 오른쪽
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
			if (x < 0 || x >= MapSize ||
				y < 0 || y >= MapSize)
			{
				return false;
			}

			// 방 자체가 존재하지 않음
			if (dungeonMap[x][y] == 0)
			{
				return false;
			}

			// 플레이어 위치
			if (x == playerLoc[0] &&
				y == playerLoc[1])
			{
				return true;
			}

			// 보스 위치는 항상 표시
			if (x == bossLoc[0] &&
				y == bossLoc[1])
			{
				return true;
			}

			// 이미 방문한 방
			if (visitedMap[x][y])
			{
				return true;
			}

			// 플레이어와 인접한 방
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

		// 방 출력
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

			// 오른쪽 방과 연결되어 있으면 가로 통로 출력
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

		// 아래쪽 방과 연결되는 세로 통로 출력
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
	std::cout << "| [P] 현재 위치   [B] 보스        |\n";
	std::cout << "| [.] 탐색 완료   [?] 미확인 방   |\n";
	std::cout << "+---------------------------------+\n";
}*/
void DungeonManager::HandleRoom(Player& player, RoomType roomType)    // 방에 들어갔을 때
{

}
void DungeonManager::HandleBattleResult(BattleResult result)    // 전투 결과
{

}

