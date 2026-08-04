#include "character/N_Manager1.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

struct QuizData {
    std::string question;
    int correctAnswer;
};

// 정적 데이터로 퀴즈 목록 정의
static const std::vector<QuizData> manager1Quizzes = {
    {"[QUIZ 1] 변서원 매니저님의 MBTI는 무엇일까요?\n1. ENTP\n2. ISFJ\n3. INTJ\n4. ENTJ", 3},
    {"[QUIZ 2] 변서원 매니저님은 낙서를 좋아합니다. 매니저님이 한 낙서의 모티브가 아닌 것은 무엇일까요?\n1. 사막여우\n2. 인형\n3. 떡볶이\n4. 선인장", 2}
};

Manager1::Manager1() : NPC("변서원 매니저님"), currentQuizIndex(-1) {}

void Manager1::SpeakEncounter() const {
    if (!isRescued) {
        std::cout << "\n 어딘가에 꽁꽁 묶여 곤란해하고 계신 " << name << "을(를) 발견했습니다!\n";
        std::cout << name << ": \"어휴, 빨리 여기서 탈출할 수 있게 제 퀴즈를 맞혀서 문을 열어주세요! (틀리면 기회는 끝이에요!)\"\n";
    }
    else {
        std::cout << "\n 이미 구출된 " << name << "이(가) 밝은 미소로 반겨줍니다.\n";
        std::cout << name << ": \"다시 한번 고마워요! 오늘도 코딩 힘내세요!\"\n";
    }
}

void Manager1::AskQuiz() const {
    if (isRescued) {
        std::cout << name << ": \"이미 저를 구출해주셨잖아요!\"\n";
        return;
    }

    // 이번에 출제할 인덱스 결정 (출력할 때마다 랜덤으로 뽑히도록 전역/지역 처리)
    // 보통 게임 루프에서 AskQuiz를 부를 때 결정되므로, 여기서는 예시로 출력만 담당하게 합니다.
    std::cout << "\n[변서원 매니저님의 퀴즈가 출제됩니다!]\n";
}

// 플레이어가 입력한 정답을 받아 판별하는 함수
bool Manager1::CheckAnswer(int playerAnswer) {
    if (isRescued || currentQuizIndex == -1) {
        // 임시로 이번 호출에 맞춰 랜덤 인덱스를 고정하는 로직 추가
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        currentQuizIndex = std::rand() % manager1Quizzes.size();
    }

    std::cout << manager1Quizzes[currentQuizIndex].question << "\n";
    std::cout << "플레이어 입력 정답: " << playerAnswer << "\n";

    if (playerAnswer == manager1Quizzes[currentQuizIndex].correctAnswer) {
        OnCorrect();
        return true;
    }
    else {
        OnWrong();
        return false;
    }
}

void Manager1::OnCorrect() {
    isRescued = true;
    std::cout << name << ": \"정답이에요! 드디어 여기서 탈출할 수 있게 되었네요. 정말 고마워요!\"\n";
}

void Manager1::OnWrong() const {
    std::cout << name << ": \"아니에요, 그건 틀렸어요... 더 이상 기회는 없네요. 저는 여기에 갇혀있을게요...\"\n";
}

void Manager1::GiveReward() const {
    if (isRescued) {
        std::cout << "구출 성공 보상으로 [" << name << "]을(를) 획득했습니다!\n";
    }
    else {
        std::cout << "퀴즈를 틀려서 보상을 받지 못했습니다...\n";
    }
}