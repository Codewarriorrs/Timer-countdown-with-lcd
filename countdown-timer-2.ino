const unsigned long interval = 1000;  // Interval of 1 second
unsigned long previousMillis = 0;
unsigned long countdown = 0;  // Countdown duration in seconds (1 hour)
unsigned long inputjam, inputmenit, inputdetik;
int button = 5;
int buttonState ;
int button2 = 26;
int button2State;
int led = 18;
int touch;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int LCD_ADDRESS = 0x27;
const int LCD_COLUMNS = 16;
const int LCD_ROWS = 2;
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
unsigned long hours = countdown / 3600;
unsigned long minutes = (countdown % 3600) / 60;
unsigned long seconds = (countdown % 3600) % 60;

void setup() {
  pinMode(button, INPUT);
  pinMode(button2, INPUT);
  pinMode(led, OUTPUT);
  Wire.begin();
  lcd.begin();
  lcd.setCursor(0, 0);
  Serial.begin(9600);  // Initialize serial communication for debugging
  lcd.clear();
  Serial.println("Masukkan timer untuk jam: ");
  lcd.print("Masukkan jam: ");
  while (Serial.available() == 0) {};
  inputjam = strtoul(Serial.readStringUntil('\n').c_str(), NULL, 10);
  Serial.print("Timer telah diatur menjadi: ");
  lcd.clear();
  lcd.print("Timer : ");
  Serial.print(inputjam);
  lcd.print(inputjam);
  Serial.println(" jam");
  lcd.print(" jam");
  countdown = inputjam * 3600;
  delay(1000);
  lcd.clear();
  Serial.println("Masukkan timer untuk menit: ");

  lcd.print("Masukkan menit: ");
  while (Serial.available() == 0) {};
  inputmenit = strtoul(Serial.readStringUntil('\n').c_str(), NULL, 10);
  Serial.print("Timer telah diatur menjadi: ");
  lcd.clear();
  lcd.print("Timer : ");
  Serial.print(inputmenit);
  lcd.print(inputmenit);
  Serial.println(" menit");
  lcd.print("menit");
  countdown += inputmenit * 60;
  delay(1000);
  lcd.clear();
  Serial.println("Masukkan timer untuk detik: ");
  lcd.print("Masukkan detik: ");
  while (Serial.available() == 0) {};
  inputdetik = strtoul(Serial.readStringUntil('\n').c_str(), NULL, 10);
  Serial.print("Timer telah diatur menjadi: ");
  lcd.clear();
  lcd.print("Timer : ");
  Serial.print(inputdetik);
  lcd.print(inputdetik);
  Serial.println(" detik");
  lcd.print(" detik");
  countdown += inputdetik;
  // Serial.print("TIMER = ");
  // Serial.print(inputjam);
  // Serial.print(" : ");
  // Serial.print(inputmenit);
  // Serial.print(" : ");
  // Serial.println(inputdetik);
  Serial.println("START TIMER");
  //  lcd.print("Hello, World!");
  delay(2000);
  lcd.clear();
  hours = countdown / 3600;
  minutes = (countdown % 3600) / 60;
  seconds = (countdown % 3600) % 60;

}

void loop() {
  //buttonState = digitalRead(button);
  touch = touchRead(4);
  //  Serial.println(touch);
  if (countdown != 0 && touch < 25) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
  if (digitalRead(button) == HIGH) {
    buttonState = !buttonState;
  }
  button2State = digitalRead(button2);
  delay(200);
  if (button2State == 1) {
    Serial.println(button2State);
    countdown = 0;
    setTimer();
    button2State = 0;
  }

  lcd.setCursor(0, 0);

  if (hours < 10) {
    lcd.print("0");
  }
  lcd.print(hours);
  lcd.print(":");
  if (minutes < 10) {
    lcd.print("0");
  }
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) {
    lcd.print("0");
  }
  lcd.print(seconds);


  //  delay(200);
  Serial.println(buttonState);
  if (buttonState == 1) {
    lcd.setCursor(0, 0);
    unsigned long currentMillis = millis();  // Get the current time

    // Check if the specified interval has elapsed
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;  // Update the previous time

      // Decrease the countdown value
      if (countdown > 0) {
        countdown--;
      }

      // Convert countdown to hours, minutes, and seconds
      hours = countdown / 3600;
      minutes = (countdown % 3600) / 60;
      seconds = (countdown % 3600) % 60;

      // Output the countdown value in HH:MM:SS format
      if (hours < 10) {
        Serial.print("0");
        lcd.print("0");
      }
      Serial.print(hours);
      lcd.print(hours);
      Serial.print(":");
      lcd.print(":");
      if (minutes < 10) {
        Serial.print("0");
        lcd.print("0");
      }
      Serial.print(minutes);
      lcd.print(minutes);
      Serial.print(":");
      lcd.print(":");
      if (seconds < 10) {
        Serial.print("0");
        lcd.print("0");
      }
      Serial.println(seconds);
      lcd.print(seconds);

      // Check if the countdown has reached 0
      if (countdown == 0) {
        // Countdown is finished, do something
        Serial.println("Countdown finished!");
        buttonState = 0;
        digitalWrite(led, HIGH);
        if (touch < 25) {
        digitalWrite(led, LOW);
      }
        setTimer();
      }
      else {
        digitalWrite(led, LOW);
      }

      lcd.setCursor(0, 1);
      lcd.print("                     ");
    }
  } else {
    lcd.setCursor(0, 1);
    lcd.print("click to start");
    //    if (button2State == 1) {
    //      Serial.println(button2State);
    //      countdown = 0;
    //      setTimer();
    //      button2State=0;
  }
}


void setTimer() {
  lcd.clear();
  Serial.println("Masukkan timer untuk jam: ");
  lcd.print("Masukkan Jam: ");
  while (Serial.available() == 0) {};
  inputjam = strtoul(Serial.readStringUntil('\n').c_str(), NULL, 10);
  Serial.print("Timer telah diatur menjadi: ");
  lcd.clear();
  lcd.print("Timer : ");
  Serial.print(inputjam);
  lcd.print(inputjam);
  Serial.println(" jam");
  lcd.print(" jam");
  countdown = inputjam * 3600;
  delay(1000);
  lcd.clear();
  Serial.println("Masukkan timer untuk menit: ");

  lcd.print("Masukkan Menit: ");
  while (Serial.available() == 0) {};
  inputmenit = strtoul(Serial.readStringUntil('\n').c_str(), NULL, 10);
  Serial.print("Timer telah diatur menjadi: ");
  lcd.clear();
  lcd.print("Timer : ");
  Serial.print(inputmenit);
  lcd.print(inputmenit);
  Serial.println(" menit");
  lcd.print(" menit");
  countdown += inputmenit * 60;
  delay(1000);
  lcd.clear();
  Serial.println("Masukkan timer untuk detik: ");
  lcd.print("Masukkan Detik: ");
  while (Serial.available() == 0) {};
  inputdetik = strtoul(Serial.readStringUntil('\n').c_str(), NULL, 10);
  Serial.print("Timer telah diatur menjadi: ");
  lcd.clear();
  lcd.print("Timer : ");
  Serial.print(inputdetik);
  lcd.print(inputdetik);
  Serial.println(" detik");
  lcd.print(" detik");
  countdown += inputdetik;
  // Serial.print("TIMER = ");
  // Serial.print(inputjam);
  // Serial.print(" : ");
  // Serial.print(inputmenit);
  // Serial.print(" : ");
  // Serial.println(inputdetik);
  Serial.println("START TIMER");
  //  lcd.print("Hello, World!");
  delay(2000);
  lcd.clear();
  hours = countdown / 3600;
  minutes = (countdown % 3600) / 60;
  seconds = (countdown % 3600) % 60;

}
