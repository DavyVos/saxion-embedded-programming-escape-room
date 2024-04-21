#include "MultipleChoice.hpp"
#include "WinEnd.hpp"

String questions[] = {
    "What is the answers to the universe and everything?",
    "What planet was originally named \"George\" when first discovered?",
    "What is the approximate age of the universe in billions of years?"};

String answers[] = {
    "A) 10, B 42, C)3",
    "A) Uranus, B Jupiter, C)Neptune",
    "A) 13.8, B 4.8, C)100",
};

char correctAnswer[] = {
    'b',
    'a',
    'a'};

int currentQuestion = 0;
int previousQuestion = 0;

int questionStart = 16;
int questionEnd = 0;

String scrollQuestion(String StrDisplay)
{
    String result;
    String StrProcess = "                " + StrDisplay + "                ";
    result = StrProcess.substring(questionStart, questionEnd);
    questionStart++;
    questionEnd++;
    if (questionStart > StrProcess.length())
    {
        questionStart = 16;
        questionEnd = 0;
    }
    return result;
}

int answerStart = 16;
int answerEnd = 0;

String scrollAnswer(String StrDisplay)
{
    String result;
    String StrProcess = "                " + StrDisplay + "                ";
    result = StrProcess.substring(answerStart, answerEnd);
    answerStart++;
    answerEnd++;
    if (answerStart > StrProcess.length())
    {
        answerStart = 16;
        answerEnd = 0;
    }
    return result;
}

void MultipleChoice::update(GameContext *context)
{
    if (true == context->Keyboard->available())
    {
        char nextKey = context->Keyboard->read();

        bool result = nextKey == correctAnswer[currentQuestion];
        if (false == result)
        {
            context->GameOver();
        }
        else if (2 == currentQuestion)
        {
            this->nextGame(context);
        }
        else
        {
            currentQuestion++;
        }
    }
        if (0 == context->CurrentTimeStamp % 500)
    {
        context->Lcd->setCursor(0, 0);
        context->Lcd->println(scrollQuestion(questions[currentQuestion]));
    }
    if (0 == context->CurrentTimeStamp % 500)
    {
        context->Lcd->setCursor(0, 1);
        context->Lcd->println(scrollAnswer(answers[currentQuestion]));
    }
}

void MultipleChoice::nextGame(GameContext *context)
{
    context->NextGame(new WinEnd());
}

void MultipleChoice::startGame(GameContext *context)
{
}

void MultipleChoice::stopGame(GameContext *context)
{
}