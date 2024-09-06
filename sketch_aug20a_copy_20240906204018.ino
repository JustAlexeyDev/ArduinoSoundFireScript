const int tempPin = A0;    
const int buzzerPin = 8;   

const float thresholdTemp = 40.0; 

int melody[] = {400, 360, 400, 360, 400, 360, 400}; 
int noteDurations[] = {4, 4, 4, 4, 4, 4, 4}; 

bool alarmActive = false;
unsigned long alarmStartTime = 0;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  deactivateAlarm(); // Сброс сигнала при старте программы
}

void loop() {
  float temperature = readTemperature();

  if (temperature >= thresholdTemp) {
    activateAlarm();
  }

  if (alarmActive) {
    playMelody();
  }
}

float readTemperature() {
  int sensorValue = analogRead(tempPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100;
  return temperature;
}

void activateAlarm() {
  if (!alarmActive) {
    alarmActive = true;
    alarmStartTime = millis();
    Serial.println("ALARM"); // Отправка сигнала на компьютер
  }
}

void bizzerSet() {
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, 1000, 100);  
    delay(200);             
  }
}

void deactivateAlarm() {
  alarmActive = false;
  noTone(buzzerPin); 
  Serial.println("RESET"); // Отправка сигнала на компьютер
  bizzerSet();
}

void playMelody() {
  for (int thisNote = 0; thisNote < 7; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzerPin);
  }
  
  delay(2000);
}