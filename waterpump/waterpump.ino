/*************************************************************
Motor Shield 1-Channel DC Motor Demo
by Randy Sarafan

For more information see:
https://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/

*************************************************************/

int floatState = LOW;
int countdown = 0;

void setup() {


  //Setup Channel A
  pinMode(12, OUTPUT);     //Initiates Motor Channel A pin
  digitalWrite(12, HIGH);  //Establishes forward direction of Channel A
  pinMode(9, OUTPUT);      //Initiates Brake Channel A pin
  digitalWrite(9, LOW);    //Disengage the Brake for Channel A

  pinMode(3, OUTPUT);    //init "pwm"
  digitalWrite(3, LOW);  // turn motoro off

  // 2 is float sensor
  pinMode(2, INPUT_PULLUP);

  pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {

  floatState = digitalRead(2);
  if (floatState == HIGH) {
    Serial.println("WATER LEVEL - HIGH");
    if(!countdown) {
      countdown = 5 * 60; // run for 5 min
    }
  }
  else {
    Serial.println("WATER LEVEL - LOW");
  }

  if(countdown) {
    countdown--;
    digitalWrite(3, HIGH);
    Serial.println("MOTOR ON");
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    if(countdown == 0 && floatState == HIGH) {
      // last run didn't clear sensor, stop to prevent burning out motor
      digitalWrite(3, LOW);
      while(1) {
        Serial.println("locked");
        delay(1000);
      }
    }
  } else {
    digitalWrite(3, LOW);
    Serial.println("MOTOR OFF");
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  }
  delay(1000);
}