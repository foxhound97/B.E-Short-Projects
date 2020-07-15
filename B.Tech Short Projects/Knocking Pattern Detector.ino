const int outputPin = 3;    // led indicator connected to digital pin
const int knockSensor = A0; // the piezo is connected to an analog pin
const int thresholdHIGH = 600;  // threshold value to decide when the detected knock is hard (HIGH)
const int thresholdLOW = 500;  // threshold value to decide when the detected knock is gentle (LOW)
 
 
const int secretKnockLength = 4; //How many knocks are in your secret knock
 
/* This is the secret knock sequence
 * 0 represents a LOW or quiet knock
 * 1 represents a HIGH or loud knock
 * The sequence can be as long as you like, but longer codes increase the difficulty of matching */
const int secretKnock[secretKnockLength] = {1, 0, 1, 1};
 #include<Servo.h>
 Servo myservo;
 #include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

 
int secretCounter = 0; //this tracks the correct knocks and allows you to move through the sequence
int sensorReading = 0; // variable to store the value read from the sensor pin
 
void setup() {

 lcd.begin(16, 2);
  //Set the output pin as an OUTPUT
  myservo.attach(8);
  pinMode(outputPin, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4,0);
 
  //Begin Serial Communication.
  Serial.begin(9600);
 
}
 
void loop() {
 
  // read the piezo sensor and store the value in the variable sensorReading:
 int  sensorReading = analogRead(knockSensor);
 
  // First determine is knock if Hard (HIGH) or Gentle (LOW)
 
  //Hard knock (HIGH) is detected
  if (sensorReading >= thresholdHIGH) {
 
    //Check to see if a Hard Knock matches the Secret Knock in the correct sequence.
    if (secretKnock[secretCounter] == 1) {
 
      //The Knock was correct, iterate the counter.
      secretCounter++;
      lcd.print("Correct");
 
    } else {
 
      //The Knock was incorrect, reset the counter
      secretCounter = 0;
     lcd.print("Fail - You are a spy!");
 
    }//close if
 
    //Allow some time to pass before sampling again to ensure a clear signal.
    delay(100);
 
    //Gentle knock (LOW) is detected
  } else if (sensorReading >= thresholdLOW) {
 
    //Check to see if a Gentle Knock matches the Secret Knock in the correct sequence.
    if (secretKnock[secretCounter] == 0) {
 
      //The Knock was correct, iterate the counter.
      secretCounter++;
      lcd.print("Correct");
 
    } else {
 
      //The Knock was incorrect, reset the counter.
      secretCounter = 0;
     
       lcd.print("Fail - You are a spy!");
 
    }//close if
 
    //Allow some time to pass before sampling again to ensure a clear signal.
    delay(100);
 
  }//close if else
 
  //Check for successful entry of the code, by seeing if the entire array has been walked through.
  if (secretCounter == (secretKnockLength) ) {
 
    for(int i=0;i<=180;i++)
    {
      myservo.write(i);
    }
    secretCounter = 0;
 
  }//close success check
 
}//close loop
