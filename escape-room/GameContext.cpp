#include "GameContext.hpp"
#include "EscapeRoomState.hpp"

bool firstRender = true;

GameContext::GameContext(
    State *currentState,
    TM1638plus *tm,
    PS2Keyboard *keyboard,
    LiquidCrystal_I2C *lcd,
    uint32_t button,
    uint32_t potentiometer,
    uint32_t buzzer)
    : CurrentState(currentState),
      Tm(tm),
      Keyboard(keyboard),
      Lcd(lcd),
      Button(button),
      Potentiometer(potentiometer),
      Buzzer(buzzer),
      numTasks(0){};

void GameContext::Update()
{
    this->PreviousTimeStamp = millis();
    this->CurrentTimeStamp = millis();

    if (true == firstRender)
    {
        this->CurrentState->startGame(this);
        firstRender = false;
    }
    else
    {
        this->CurrentState->update(this);
    }

    for (int i = 0; i < this->numTasks; i++)
    {
        this->tasks[i].execute();
    }
}

void GameContext::StopGame()
{
    this->Lcd->clear();
}

void GameContext::NextGame(State *next)
{
    this->CurrentState = next;
    firstRender = true;
    this->CurrentGameStartedAt = CurrentTimeStamp;
}

void GameContext::GameOver()
{
    this->Lcd->clear();
    firstRender = true;
    this->CurrentState = new EscapeRoomState();
}

void GameContext::AddTask(Task t)
{
    if (this->numTasks < MAX_TASKS)
    {
        this->tasks[this->numTasks++] = t;
    }
}

void GameContext::clearTasks()
{
    this->numTasks = 0;
}

uint8_t GameContext::getDebouncedTmReading()
{
    static uint32_t lastDebounceTime = 0;
    static uint8_t lastButtonState = HIGH;
    static uint8_t buttonState = HIGH;

    // Read the current button state
    uint8_t reading = this->Tm->readButtons();

    // If the button state has changed, reset the debounce timer
    if (reading != lastButtonState)
    {
        lastDebounceTime = millis();
    }

    // Check if the debounce time has elapsed
    if ((millis() - lastDebounceTime) > 50)
    {
        // Update the button state only if it has been stable for the debounce time
        if (reading != buttonState)
        {
            buttonState = reading;
        }
    }

    lastButtonState = reading;
    return reading;
}