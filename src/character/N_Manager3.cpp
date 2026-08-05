#include "character/N_Manager3.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>

struct QuizData {
    std::string question;
    int correctAnswer;
};

// 정적 데이터로 퀴즈 목록 정의
static const std::vector<QuizData> manager3Quizzes = {
    {"[QUIZ 1] 문승호 매니저님의 태권도 경력은 어떻게 될까요?\n1. 14년\n2. 3년\n3. 9년\n4. 50년", 1},
    {"[QUIZ 2] 문승호 매니저님의 멤버 카드에서 좋아한다고 언급되지 않은 것은 무엇일까요?\n1. 맥주\n2. 와인\n3. 콜라\n4. 위스키", 3}
};

Manager3::Manager3() : NPC("문승호 매니저님"), currentQuizIndex(-1) {}

void Manager3::SpeakEncounter() const {
    if (!isRescued) {
        std::string s1 = "\n 어딘가에 꽁꽁 묶여 곤란해하고 계신 ";
        s1.append(name);
        s1.append("을(를) 발견했습니다!");
        um.PrintLog(s1);

        std::string s2 = name;
        s2.append(": \"어휴, 빨리 여기서 탈출할 수 있게 제 퀴즈를 맞혀서 문을 열어주세요! (틀리면 기회는 끝이에요!)\"");
        um.PrintLog(s2);
    }
    else {
        std::string s1 = "\n 이미 구출된 ";
        s1.append(name);
        s1.append("이(가) 밝은 미소로 반겨줍니다.");
        um.PrintLog(s1);

        std::string s2 = name;
        s2.append(": \"다시 한번 고마워요!\"");
        um.PrintLog(s2);
    }
}

void Manager3::AskQuiz() {
    if (isRescued) {
        std::string s = name;
        s.append(": \"이미 저를 구출해주셨잖아요!\"");
        um.PrintLog(s);
        return;
    }

    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> quizDist(0, static_cast<int>(manager3Quizzes.size()) - 1);
    currentQuizIndex = quizDist(gen);

    // 단일 문자열 및 퀴즈 데이터 출력
    um.PrintLog("\n[문승호 매니저님의 퀴즈가 출제됩니다!]");
    um.PrintQuiz(manager3Quizzes[currentQuizIndex].question);
}

// 플레이어가 입력한 정답을 받아 판별하는 함수
bool Manager3::CheckAnswer(int playerAnswer) {
    if (isRescued || currentQuizIndex == -1) return false;

    if (playerAnswer == manager3Quizzes[currentQuizIndex].correctAnswer) {
        OnCorrect();
        return true;
    }
    else {
        OnWrong();
        return false;
    }
}

void Manager3::OnCorrect() {
    isRescued = true;
    std::string s = name;
    s.append(": \"정답이에요! 드디어 여기서 탈출할 수 있게 되었네요. 정말 고마워요!\"");
    um.PrintLog(s);
}

void Manager3::OnWrong() const {
    std::string s = name;
    s.append(": \"아니에요, 그건 틀렸어요... 더 이상 기회는 없네요. 저는 여기에 갇혀있을게요...\"");
    um.PrintLog(s);
}

void Manager3::GiveReward() const {
    if (isRescued) {
        std::string s = "구출 성공 보상으로 [";
        s.append(name);
        s.append("의 보상]을(를) 획득했습니다!");
        um.PrintLog(s);
    }
    else {
        um.PrintLog("퀴즈를 틀려서 보상을 받지 못했습니다...");
    }
}
