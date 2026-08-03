//성국님 개발 테스트용 메인
//=======테스트절차=======
// 1. src/core/main.cpp 전체주석처리(ctrl+a 하고 ctrl+/ 하기)
// 2. 본인이름.cpp 에서 테스트 하기
// 3. 오류없으면
// 4. 본인이름.cpp 전체주석처리
// 5. src/core/main.cpp 전체주석처리 해제(ctrl+a 하고 ctrl+/ 하기)
// 6. 커밋하고 pr하기
// *테스트 내용은 남겨주세요!

//--------------------------이거 몬스터 cpp 밑에 적당한 위치에 넣어야함--------------------------------
/*// 전투 테스트용 임시 구현 
void Monster::SetHp(int Value)
{
    if (Value < 0)
    {
        Hp = 0;
    }
    else if (Value > MaxHp)
    {
        Hp = MaxHp;
    }
    else
    {
        Hp = Value;
    }
}*/
//--------------------------이거 몬스터 cpp  밑에 적당한 위치에 넣어야함--------------------------------



/*#include "core/UIManager.h"
#include "core/DungeonManager.h"
#include "core/BattleManager.h"
#include "character/P_Warrior.h"
#include "character/M_Slime.h"
#include "character/M_Goblin.h"
#include "character/M_Orc.h"

int main()
{
	Warrior player("테스트 전사");
	//Slime slime(player.GetLevel());
	//BattleManager battleManager;
	//battleManager.StartBattle(player, slime);

	DungeonManager dungeonManager;
	UI ui;
	dungeonManager.StartDungeon(player, ui);
}*/