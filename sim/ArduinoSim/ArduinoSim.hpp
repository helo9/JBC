#define OUTPUT 1

enum AnalogPins {
    A0 = 50,
    A1,
    A2,
    A3,
    A4,
    A5
};

unsigned long millis();

void pinMode(int pin, int mode);

int analogRead(int pin);
void analogWrite(int pin, int value);

int digitalRead(int pin);
void digitalWrite(int pin, int value);
