#define PLAYER_COUNT 4

int btPins[PLAYER_COUNT] = {2, 3, 4, 5};
int lampPins[PLAYER_COUNT] = {6, 7, 8, 9};
bool isLampLocked[PLAYER_COUNT] = {false, false, false, false};

void setup() {
  for (int i = 0; i < PLAYER_COUNT; i++) {
    pinMode(btPins[i], INPUT);
    pinMode(lampPins[i], OUTPUT);
    digitalWrite(lampPins[i], LOW);
  }
}

void loop() {
  for (int i = 0; i < PLAYER_COUNT; i++) {
    if (digitalRead(btPins[i]) == HIGH) {
      if (!isLampLocked[i]) {
        digitalWrite(lampPins[i], HIGH);
        isLampLocked[i] = true;
        delay(10000);
        digitalWrite(lampPins[i], LOW);
        isLampLocked[i] = false;
      }
      delay(100); // Delay to debounce the button
    }
  }
}
