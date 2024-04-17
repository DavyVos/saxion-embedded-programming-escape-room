#define PIN_BUZZER 3
#define FREQ_LOW 500
#define FREQ_HIGH 1200
#define WHOOP_DURATION 3500
#define WHOOP_STEPS 350
#define BUTTON_PIN 2

int buttonState = 0;

void setup()
{
    // initialize the pushbutton pin as an input:
    pinMode(BUTTON_PIN, INPUT);

    int freqchange = (FREQ_HIGH - FREQ_LOW) / WHOOP_STEPS;
    int toneDuration = WHOOP_DURATION / WHOOP_STEPS;

    for (int i = 0; i < 10; i++)
    {
        for (int freq = FREQ_LOW; freq <= FREQ_HIGH; freq += freqchange)
        {
            // read the state of the pushbutton value:
            buttonState = digitalRead(BUTTON_PIN);
            // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
            if (buttonState == HIGH)
            {
                // turn LED on:
                tone(PIN_BUZZER, freq, toneDuration);
            }
            delay(toneDuration);
        }
        delay(500);
    }
}

void loop()
{
}