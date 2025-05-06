#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

char auth[] = "IEpfmdGBJ6uHKyXUXTFaZMwiIvMi4jeX";
char ssid[] = "ShaikAbdulRasheed";
char pass[] = "tony6281";

DHT dht(D3, DHT11);
BlynkTimer timer;
bool pirbutton = 0;

#define Buzzer D0
#define MQ2 A0
#define trig D4
#define echo D5
#define PIR D6
#define relay1 D7
#define relay2 D8

BLYNK_WRITE(V0) {
  pirbutton = param.asInt();
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(Buzzer, OUTPUT);
  pinMode(PIR, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("Home Automation");
  lcd.setCursor(4, 1);
  lcd.print("System");
  delay(4000);
  lcd.clear();

  timer.setInterval(100L, gassensor);
  timer.setInterval(100L, DHT11sensor);
  timer.setInterval(100L, pirsensor);
  timer.setInterval(100L, ultrasonic);
}

void gassensor() {
  int value = analogRead(MQ2);
  value = map(value, 0, 1024, 0, 100);
  if (value <= 50) {
    digitalWrite(Buzzer, LOW);
  } else if (value > 50) {
    digitalWrite(Buzzer, HIGH);
  }
  Blynk.virtualWrite(V1, value);
  lcd.setCursor(0, 0);
  lcd.print("G: ");
  lcd.print(value);
}

void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    return;
  }
  Blynk.virtualWrite(V2, t);
  Blynk.virtualWrite(V3, h);
  lcd.setCursor(8, 0);
  lcd.print("T:");
  lcd.print(t);
  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(h);
}

void pirsensor() {
  bool value = digitalRead(PIR);
  if (pirbutton == 1) {
    if (value == 0) {
      digitalWrite(Buzzer, LOW);
    } else if (value == 1) {
      digitalWrite(Buzzer, LOW);
    }
  }
}

void ultrasonic() {
  digitalWrite(trig, LOW);
  delayMicroseconds(4);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;
  Blynk.virtualWrite(V4, cm);
  if (cm <= 30)
    digitalWrite(Buzzer, HIGH);
  delay(1000);
  digitalWrite(Buzzer, LOW);
  lcd.setCursor(8, 1);
  lcd.print("W:");
  lcd.print(cm);
  lcd.print("  ");
}

BLYNK_WRITE(V5) {
  bool RelayOne = param.asInt();
  digitalWrite(relay1, RelayOne ? LOW : HIGH);
}

BLYNK_WRITE(V6) {
  bool RelayTwo = param.asInt();
  digitalWrite(relay2, RelayTwo ? LOW : HIGH);
}

void loop() {
  Blynk.run();
  timer.run();
}

