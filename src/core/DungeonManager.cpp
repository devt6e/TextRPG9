#include "core/DungeonManager.h"
#include "core/UIManager.h"
#include "character/Player.h"
#include "character/M_Slime.h"
#include "character/M_Goblin.h"
#include "character/M_Orc.h"
#include "character/M_Zep.h"
#include "character/M_Morning.h"
#include "character/M_JYJ.h"
#include "character/M_husband.h"
#include "character/N_Manager1.h"
#include "character/N_Manager2.h"
#include "character/N_Manager3.h"
#include "character/N_Manager4.h"
#include "item/Item.h"
#include "item/Inventory.h"

#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
#include <algorithm>
#include <vector>
//
/*// 1. 랜덤 생성기 준비
std::random_device rd;
std::mt19937 gen(rd());

// 2. 범위 설정: 1부터 10까지
std::uniform_int_distribution<int> dist(0, 4);

// 3. 랜덤 숫자 뽑기
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
	npcRoomMap{},
	npcEncountered{},
	encounteredNpcCount(0),
	correctNpcQuizCount(0),
	midBossPending(false),
	midBossDefeated(false),
	finalBossDefeated(false),
	clearedMap{},
	shouldExitDungeon(false)
{
	GenerateDungeonMap();
}
//ui매니저용


int DungeonManager::GetMapWidth() const
{
	return MapWidth;
}

int DungeonManager::GetMapHeight() const
{
	return MapHeight;
}

bool DungeonManager::HasDefeatedFinalBoss() const
{
	return finalBossDefeated;
}
/*
맵 밖 좌표 → 방 없음
dungeonMap 값이 0 → 방 없음
1 또는 2 → 방 있음
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



	//i= 가로, j=세로
	for (int x = 0; x < MapWidth; x++)
	{
		for (int y = 0; y < MapHeight; y++)
		{
			dungeonMap[x][y] = 0;
			npcRoomMap[x][y] = -1;
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
	case 0: // 플레이어 위쪽, 보스 아래쪽
		playerLoc[0] = playerXPosition;
		playerLoc[1] = 0;

		bossLoc[0] = bossXPosition;
		bossLoc[1] = MapHeight - 1;
		break;

	case 1: // 플레이어 아래쪽, 보스 위쪽
		playerLoc[0] = playerXPosition;
		playerLoc[1] = MapHeight - 1;

		bossLoc[0] = bossXPosition;
		bossLoc[1] = 0;
		break;

	case 2: // 플레이어 왼쪽, 보스 오른쪽
		playerLoc[0] = 0;
		playerLoc[1] = playerYPosition;

		bossLoc[0] = MapWidth - 1;
		bossLoc[1] = bossYPosition;
		break;

	case 3: // 플레이어 오른쪽, 보스 왼쪽
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
	// 좌표 모두 결정 맵에 표시
	dungeonMap[playerLoc[0]][playerLoc[1]] = 1;
	visitedMap[playerLoc[0]][playerLoc[1]] = true;
	clearedMap[playerLoc[0]][playerLoc[1]] = true;
	dungeonMap[bossLoc[0]][bossLoc[1]] = 2;


	// ===== 막다른 방 생성 시작 =====
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
				branchX < MapWidth &&
				branchY >= 0 &&
				branchY < MapHeight)
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
					if (branchX < MapWidth - 1 &&
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

	// 시작점과 보스방을 제외한 이동 가능한 방 중 세 곳에
	// Manager 1, 3, 4를 무작위로 하나씩 배치한다.
	std::vector<std::pair<int, int>> npcCandidates;
	for (int x = 0; x < MapWidth; ++x)
	{
		for (int y = 0; y < MapHeight; ++y)
		{
			if (dungeonMap[x][y] == 1 &&
				!(x == playerLoc[0] && y == playerLoc[1]))
			{
				npcCandidates.push_back({ x, y });
			}
		}
	}

	std::shuffle(npcCandidates.begin(), npcCandidates.end(), gen);
	for (int npcIndex = 0;
		npcIndex < 3 && npcIndex < static_cast<int>(npcCandidates.size());
		++npcIndex)
	{
		int npcX = npcCandidates[npcIndex].first;
		int npcY = npcCandidates[npcIndex].second;
		npcRoomMap[npcX][npcY] = npcIndex;
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

void DungeonManager::StartDungeon(Player& player, UI& ui, InventoryManager& inventoryManager)
{
	shouldExitDungeon = false;
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
		ui.PrintStatus(&player);
		/*std::cout << "\n이동 가능한 방향: ";

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
		std::cout << "입력: ";*/
		ui.PrintDungeonMoveOptions(
			CanMoveTo(0),
			CanMoveTo(1),
			CanMoveTo(2),
			CanMoveTo(3));

		std::string inputString =
			ui.InputString("");

		if (inputString.empty())
		{
			continue;
		}

		char input = inputString[0];

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

			ui.PrintLog(
				"체크포인트를 저장하고 마을로 돌아갑니다.");
			ui.EraseArt();
			ui.PrintTitle();
			return;

		default:
			ui.PrintLog("잘못된 입력입니다.");
			continue;
		}

		if (CanMoveTo(direction))
		{
			MoveRoom(direction);
			if (clearedMap[playerLoc[0]][playerLoc[1]] == false)
			{
				RoomType decideRoom = DecideRoomType();
				HandleRoom(player, decideRoom, ui, inventoryManager);
				if (shouldExitDungeon)
				{
					if (player.GetHp() <= 0)
					{
						ui.PrintLog("게임 오버입니다.");
					}

					return;
				}
			}

		}
		else
		{
			if (IsBossDirection(direction) && encounteredNpcCount < 3)
			{
				ui.PrintLog("매니저님 3명을 모두 만나야 보스방에 들어갈 수 있습니다.");
				ui.WaitForAnyKey("계속하려면 아무 키나 입력하세요: "); // ysg: 다음 맵 갱신 전에 잠금 안내를 확인할 수 있도록 대기
			}
			else if (IsBossDirection(direction) && !midBossDefeated)
			{
				ui.PrintLog("중간보스를 처치해야 보스방에 들어갈 수 있습니다.");
				ui.WaitForAnyKey("계속하려면 아무 키나 입력하세요: "); // ysg: 안내 문구가 즉시 지워지는 문제 방지
			}
			else
			{
				ui.PrintLog("이동할 수 없는 방향입니다.");
			}
		}
	}

	if (finalBossDefeated)
	{
		return; // ysg: 보스 처치 후 뒤늦게 '보스방에 도착했습니다'가 출력되는 것 방지
	}

	ui.DisplayDungeonMap(*this);
	ui.PrintLog("보스방에 도착했습니다.");
}

RoomType DungeonManager::DecideRoomType()
{
	if (midBossPending && !midBossDefeated)
	{
		return RoomType::MidBoss;
	}
	else if (playerLoc[0] == bossLoc[0] && playerLoc[1] == bossLoc[1])
	{
		return RoomType::Boss;
	}

	int npcIndex = npcRoomMap[playerLoc[0]][playerLoc[1]];
	if (npcIndex >= 0 && npcIndex < 3 && !npcEncountered[npcIndex])
	{
		return RoomType::NPC;
	}
	else
	{
		return RoomType::Monster;
	}

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
		nextX >= MapWidth ||
		nextY < 0 ||
		nextY >= MapHeight)
	{
		return false;
	}

	if (IsBossAt(nextX, nextY) &&
		(encounteredNpcCount < 3 || !midBossDefeated))
	{
		return false;
	}

	return dungeonMap[nextX][nextY] != 0;
}

bool DungeonManager::IsBossDirection(int destination) const
{
	int nextX = playerLoc[0];
	int nextY = playerLoc[1];

	switch (destination)
	{
	case 0:
		--nextY;
		break;
	case 1:
		++nextY;
		break;
	case 2:
		--nextX;
		break;
	case 3:
		++nextX;
		break;
	default:
		return false;
	}

	return IsBossAt(nextX, nextY);
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
	/*std::cout << "moved player: "
		<< playerLoc[0] << ", "
		<< playerLoc[1] << '\n';*/
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
void DungeonManager::HandleRoom(Player& player,
	RoomType roomType,
	UI& ui,
	InventoryManager& inventoryManager)    // 방에 들어갔을 때
{
	switch (roomType)
	{
	case(RoomType::Boss):
	{
		ui.PrintLog("보스방 입장!!");
		JYJ boss(player.GetLevel());
		ui.PrintMonsterArt(boss.GetName()); // ysg: 최종 보스 등장 시 해당 아스키 아트 출력

		BattleResult battleResult =
			battleManager.StartBattle(
				player,
				boss,
				ui,
				inventoryManager,
				false); // ysg: 최종 보스방 재진입 상태가 꼬이지 않도록 도망 금지

		HandleBattleResult(
			player,
			boss,
			battleResult,
			ui,
			inventoryManager);

		if (battleResult == BattleResult::Victory)
		{
			finalBossDefeated = true;
			ui.PrintLog("최종 보스를 처치했습니다!");

			if (correctNpcQuizCount == 4)
			{
				ui.PrintLog("[ENDING] 전원 구출");
				ui.PrintLog("매니저님 4명의 문제를 모두 맞히고 전원을 구출해 함께 ZEP 타워를 탈출했습니다.");
			}
			else if (correctNpcQuizCount > 0)
			{
				ui.PrintLog("[ENDING] 일부 구출");
				ui.PrintLog(
					std::to_string(correctNpcQuizCount) +
					"명의 매니저님을 구출하고 ZEP 타워를 탈출했습니다.");
			}
			else
			{
				ui.PrintLog("[ENDING] 구출 실패");
				ui.PrintLog("매니저님을 아무도 구출하지 못한 채 홀로 ZEP 타워를 탈출했습니다.");
			}

			ui.WaitForAnyKey("게임을 종료하려면 아무 키나 입력하세요: ");
		}

		break;
	}
	case(RoomType::Monster):
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> monsterDist(0, 4);
		int monsterType = monsterDist(gen);

		switch (monsterType)
		{
		case 0:
		{
			Slime slime(player.GetLevel());
			ui.PrintMonsterArt(slime.GetName()); // ysg: 몬스터 종류 결정 직후 아스키 아트 출력
			ui.PrintLog(slime.GetName() + " 등장!!");
			BattleResult battleResult = battleManager.StartBattle(player, slime, ui, inventoryManager);
			HandleBattleResult(player, slime, battleResult, ui, inventoryManager);
			break;
		}

		case 1:
		{
			Goblin goblin(player.GetLevel());
			ui.PrintMonsterArt(goblin.GetName());
			ui.PrintLog(goblin.GetName() + " 등장!!");
			BattleResult battleResult = battleManager.StartBattle(player, goblin, ui, inventoryManager);
			HandleBattleResult(player, goblin, battleResult, ui, inventoryManager);

			break;
		}

		case 2:
		{
			Orc orc(player.GetLevel());
			ui.PrintMonsterArt(orc.GetName());
			ui.PrintLog(orc.GetName() + " 등장!!");
			BattleResult battleResult = battleManager.StartBattle(player, orc, ui, inventoryManager);
			HandleBattleResult(player, orc, battleResult, ui, inventoryManager);

			break;
		}

		case 3:
		{
			Zep zep(player.GetLevel());
			ui.PrintMonsterArt(zep.GetName());
			ui.PrintLog(zep.GetName() + " 등장!!");
			BattleResult battleResult = battleManager.StartBattle(player, zep, ui, inventoryManager);
			HandleBattleResult(player, zep, battleResult, ui, inventoryManager);
			break;
		}

		case 4:
		{
			Morning morning(player.GetLevel());
			ui.PrintMonsterArt(morning.GetName());
			ui.PrintLog(morning.GetName() + " 등장!!");
			BattleResult battleResult = battleManager.StartBattle(player, morning, ui, inventoryManager);
			HandleBattleResult(player, morning, battleResult, ui, inventoryManager);
			break;
		}
		}
		break;
	}
	case(RoomType::MidBoss):
	{
		ui.PrintLog("중간보스 매니저님 남편 꿈나무가 등장했습니다!!");
		husband midBoss(player.GetLevel());
		ui.PrintMonsterArt(midBoss.GetName()); // ysg: 중간보스 등장 아트 출력

		BattleResult battleResult = battleManager.StartBattle(
			player,
			midBoss,
			ui,
			inventoryManager);

		HandleBattleResult(
			player,
			midBoss,
			battleResult,
			ui,
			inventoryManager);

		if (battleResult == BattleResult::Victory)
		{
			midBossPending = false;
			midBossDefeated = true;
			ui.PrintLog("중간보스를 처치했습니다.");

			ui.NPC_K(); // ysg: 문승호 매니저님 외 NPC는 NPC_K 아트 사용
			Manager2 manager2;
			ui.PrintLog(manager2.GetName() + "이(가) 뿱하고 등장했습니다!!");
			manager2.SpeakEncounter();
			manager2.AskQuiz();

			int answer = ui.InputSelection("정답: ");
			bool isCorrect = manager2.CheckAnswer(answer);
			ui.WaitForAnyKey("퀴즈 결과를 확인하려면 아무 키나 입력하세요: "); // ysg: 정답·오답 대사를 후속 보상 로그 전에 확인
			manager2.GiveReward();

			if (isCorrect)
			{
				++correctNpcQuizCount;
				DropRandomItem(ui, inventoryManager);
			}
			else
			{
				ui.PrintLog("오답이어서 아이템 보상을 받지 못했습니다.");
			}

			if (IsBossAt(playerLoc[0], playerLoc[1]))
			{
				HandleRoom(player, RoomType::Boss, ui, inventoryManager);
			}
		}
		break;
	}
	case(RoomType::NPC):
	{
		int npcIndex = npcRoomMap[playerLoc[0]][playerLoc[1]];
		if (npcIndex < 0 || npcIndex >= 3 || npcEncountered[npcIndex])
		{
			clearedMap[playerLoc[0]][playerLoc[1]] = true;
			break;
		}

		npcEncountered[npcIndex] = true;
		if (npcIndex == 1) // ysg: Manager3 문승호 매니저님만 NPC_M 아트 사용
		{
			ui.NPC_M();
		}
		else
		{
			ui.NPC_K();
		}

		auto runNpcQuiz = [&](auto& npc)
		{
			ui.PrintLog(npc.GetName() + " 등장!!");
			npc.SpeakEncounter();
			npc.AskQuiz();
			int answer = ui.InputSelection("정답: ");
			bool rescued = npc.CheckAnswer(answer);
			ui.WaitForAnyKey("퀴즈 결과를 확인하려면 아무 키나 입력하세요: "); // ysg: 구출 성공·실패 대사를 충분히 확인한 뒤 진행
			npc.GiveReward();
			return rescued;
		};

		bool rescued = false;
		switch (npcIndex)
		{
		case 0:
		{
			Manager1 manager;
			rescued = runNpcQuiz(manager);
			break;
		}
		case 1:
		{
			Manager3 manager;
			rescued = runNpcQuiz(manager);
			break;
		}
		case 2:
		{
			Manager4 manager;
			rescued = runNpcQuiz(manager);
			break;
		}
		}

		++encounteredNpcCount;
		ui.PrintLog(
			"만난 매니저님: " +
			std::to_string(encounteredNpcCount) + " / 3");

		if (rescued)
		{
			++correctNpcQuizCount;
			DropRandomItem(ui, inventoryManager);
		}
		else
		{
			ui.PrintLog("오답이어서 아이템 보상을 받지 못했습니다.");
		}

		ui.WaitForAnyKey("계속하려면 아무 키나 입력하세요: "); // ysg: Enter를 포함한 키 하나로 진행하고 이전 선택지는 제거
		clearedMap[playerLoc[0]][playerLoc[1]] = true;

		if (encounteredNpcCount == 3 && !midBossDefeated)
		{
			midBossPending = true;
			clearedMap[playerLoc[0]][playerLoc[1]] = false;
			HandleRoom(player, RoomType::MidBoss, ui, inventoryManager);
		}
		break;
	}
	}
}
void DungeonManager::HandleBattleResult(Player& player,
	Monster& monster,
	BattleResult result,
	UI& ui,
	InventoryManager& inventoryManager)
{
	switch (result)
	{
	case(BattleResult::Victory):
	{
		ui.WaitForAnyKey("계속하려면 아무 키나 입력하세요: "); // ysg: Enter를 포함한 키 하나로 진행하고 이전 선택지는 제거

		ui.PrintLog("전투에서 승리했습니다.");
		clearedMap[playerLoc[0]][playerLoc[1]] = true;
		player.AddExp(monster.GetDropExp());
		player.SetGold(player.GetGold() + monster.GetDropGold());

		ui.PrintLog(std::to_string(monster.GetDropGold()) +" ZEM을 획득했습니다.");
		ui.WaitForAnyKey("계속하려면 아무 키나 입력하세요: "); // ysg: Enter를 포함한 키 하나로 진행하고 이전 선택지는 제거

	}
	break;
	case(BattleResult::Defeat):
	{
		ui.PrintLog("전투에서 패배했습니다.");
		shouldExitDungeon = true;
	}
	break;
	case(BattleResult::Escaped):
	{
		ui.PrintLog("전투에서 도망쳤습니다.");
		shouldExitDungeon = true;
		ui.EraseArt(); // ysg: 도망 후 마을로 돌아갈 때 던전 미니맵 잔상 제거
		ui.PrintTitle(); // ysg: 마을 화면의 LOSTZEP 타이틀 아트 복원
	}
	break;

	}
}

void DungeonManager::DropRandomItem(
	UI& ui,
	InventoryManager& inventoryManager)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// 랜덤 확률로 아이템 획득 
	// 100퍼 나오게 할꺼면 밑에 테두리안에 내용 없애거나 if (dropChance > 30) 30을 100으로
	//-------------------------------------------
	std::uniform_int_distribution<int> dropChanceDist(1, 100);
	int dropChance = dropChanceDist(gen);

	if (dropChance > 100)// 이거 30 -> 60으로하면 60퍼 확률로 드랍임
	{
		return;
	}
	//----------------------------------------------
	std::uniform_int_distribution<int> itemDist(0, 3);
	int itemType = itemDist(gen);

	switch (itemType)
	{
	case 0:
		ui.PrintItemArt("에너지 드링크");
		inventoryManager.AddConsumable(HpPotion());
		ui.PrintLog("HP 회복 포션을 획득했습니다.");

		break;

	case 1:
		ui.PrintItemArt("아이스 아메리카노");
		inventoryManager.AddConsumable(MpPotion());
		ui.PrintLog("MP 회복 포션을 획득했습니다.");

		break;

	case 2:
		ui.PrintItemArt("쿠키의 장난감");
		inventoryManager.AddConsumable(TempABPotion());
		ui.PrintLog("공격력 임시 버프 포션을 획득했습니다.");

		break;

	case 3:
		ui.PrintItemArt("온열안대");
		inventoryManager.AddConsumable(TempDEFPotion());
		ui.PrintLog("방어력 임시 버프 포션을 획득했습니다.");

		break;
	}
}
