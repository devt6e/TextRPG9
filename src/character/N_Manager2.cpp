 #include "character/N_Manager2.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>

struct QuizData {
    std::string question;
    int correctAnswer;
};

// 정적 데이터로 퀴즈 목록 정의
static const std::vector<QuizData> manager2Quizzes = {
    {"[QUIZ 1] 김동현 매니저님의 조카 이름은 무엇일까요?\n1. 아리\n2. 온유\n3. 채원\n4. 보빈", 2},
    {"[QUIZ 2] 김동현 매니저님은 동아리에서 '이것'을 했다고 합니다. 무엇일까요?\n1. 봉산탈춤\n2. 등산\n3. 현대무용\n4. 랩", 1}
};

Manager2::Manager2() : NPC("김동현 매니저님"), currentQuizIndex(-1) {}

void Manager2::SpeakEncounter() const {
    if (!isRescued) {
        std::cout << "\n 어딘가에 꽁꽁 묶여 곤란해하고 계신 " << name << "을(를) 발견했습니다!\n";
        std::cout << name << ": \"어휴, 빨리 여기서 탈출할 수 있게 제 퀴즈를 맞혀서 문을 열어주세요! (틀리면 기회는 끝이에요!)\"\n";
    }
    else {
        std::cout << "\n 이미 구출된 " << name << "이(가) 밝은 미소로 반겨줍니다.\n";
        std::cout << name << ": \"다시 한번 고마워요!\"\n";
    }
}

void Manager2::AskQuiz() {
    if (isRescued) {
        std::cout << name << ": \"이미 저를 구출해주셨잖아요!\"\n";
        return;
    }

    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> quizDist(0, static_cast<int>(manager2Quizzes.size()) - 1);
    currentQuizIndex = quizDist(gen);
    std::cout << "\n[김동현 매니저님의 퀴즈가 출제됩니다!]\n";
    std::cout << manager2Quizzes[currentQuizIndex].question << "\n";
}

// 플레이어가 입력한 정답을 받아 판별하는 함수
bool Manager2::CheckAnswer(int playerAnswer) {
    if (isRescued || currentQuizIndex == -1) return false;

    if (playerAnswer == manager2Quizzes[currentQuizIndex].correctAnswer) {
        OnCorrect();
        return true;
    }
    else {
        OnWrong();
        return false;
    }
}

void Manager2::OnCorrect() {
    isRescued = true;
    std::cout << name << ": \"정답이에요! 드디어 여기서 탈출할 수 있게 되었네요. 정말 고마워요!\"\n";
}

void Manager2::OnWrong() const {
    std::cout << name << ": \"아니에요, 그건 틀렸어요... 더 이상 기회는 없네요. 저는 여기에 갇혀있을게요...\"\n";
}

void Manager2::GiveReward() const {
    if (isRescued) {
        std::cout << "구출 성공 보상으로 [" << name << "의 보상]을(를) 획득했습니다!\n";
    }
    else {
        std::cout << "퀴즈를 틀려서 보상을 받지 못했습니다...\n";
    }
}
