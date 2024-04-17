#define PIN_BUZZER      3
#define FREQ_LOW        500
#define FREQ_HIGH       1200
#define WHOOP_DURATION  3500
#define WHOOP_STEPS     350

void setup() {
    int freqchange = (FREQ_HIGH - FREQ_LOW) / WHOOP_STEPS;
    int toneDuration = WHOOP_DURATION / WHOOP_STEPS;

    for(int i = 0; i < 10; i++) {
        for(int freq = FREQ_LOW; freq <= FREQ_HIGH; freq += freqchange) {
            tone(PIN_BUZZER, freq, toneDuration);
            delay(toneDuration);
        }
        delay(500);
    }
}

void loop() {

}