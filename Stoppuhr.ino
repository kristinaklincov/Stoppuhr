//HINWEIS: die Methoden printDigits() und anzeigeDerZeit() wurden von der folgenden Seite entnommen: https://playground.arduino.cc/Code/SimpleTimer/
//Die Codeabschnitte finden Sie etwas weiter unten, oder Sie suchen nach DigitalClockDisplay() und gelangen dann zum Codeabschnitt

const int buttonPinWeiss = 4;
const int buttonPinRot = 5;
int lightOne = 8;
int lightTwo = 9;
int lightThree = 10;

int buttonStateWeiss = 0;
int buttonStateRot = 0;

boolean read = false;

int h, m, s;

int printFirst = 0; //Sorgt dafür, dass nur beim ersten Aufruf der anzeigeDerZeitMethode ein print durchgeführt wird

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPinWeiss, INPUT);
  pinMode(buttonPinRot, INPUT);
  pinMode(lightOne, INPUT);
  pinMode(lightTwo, INPUT);
  pinMode(lightThree, INPUT);
  Serial.begin(9600);
}
void anzeigeDerZeit() {
  //Ausgabe der Zeit, aber nur jede Sekunde
  //Diesen Teil habe ich aus dem Internet und so angepasst, dass es für mich gut ist
  //Der kopierte Codeausschnitt finden Sie im Link etwa in der Mitte der Seite: http://forum.arduino.cc/index.php?topic=247117.0
  static const unsigned long REFRESH_INTERVAL = 1000; // ms
  static unsigned long lastRefreshTime = 0;
   if(printFirst == 0){
    Serial.println("0:00:00");
    printFirst = 1;
    }
  if (millis() - lastRefreshTime >= REFRESH_INTERVAL)
  {
    lastRefreshTime += REFRESH_INTERVAL;
    s = millis() / 1000;
    m = s / 60;
    h = s / 3600;
    s = s - m * 60;
    m = m - h * 60;
    Serial.print(h);
    printDigits(m);
    printDigits(s);
    Serial.println();
  }
  //Wenn der rote Button gedrückt wird, wird stopProgramm() aufgerufen
  if (digitalRead(buttonPinRot) == HIGH) {
    digitalWrite(lightOne, OUTPUT);
    digitalWrite(lightTwo, OUTPUT);
    digitalWrite(lightThree, OUTPUT);
    stopProgramm();
  }
}
void printDigits(int digits) {
  Serial.print(":");
  if (digits < 10) {
    Serial.print('0');
  }
  Serial.print(digits);
}

//zeigt die Zeit beim Stoppen an
void stopProgramm() {
  Serial.print("Your time: ");
  Serial.print(h);
  printDigits(m);
  printDigits(s);
  //Setzt das Programm in ein loop damit es nicht mehr den Timer anzeigt
  while (1) {}
}

void loop() {
  buttonStateRot = digitalRead(buttonPinRot);
  //Loop, dass der Time ausgegeben wird, wenn der weisse Button einmal gedrückt wird
  while (1) {
    //Diese Schleife sorgt dafür, dass zu jedem Zeitpunkt, wenn das Programm lauft, die Stoppuhr mit dem weissen Button gestartet werden kann
    if(!read){ 
      buttonStateWeiss = digitalRead(buttonPinWeiss);
    }
    if (buttonStateWeiss == HIGH) {
      read = true;
      anzeigeDerZeit();
    }
  }
}
