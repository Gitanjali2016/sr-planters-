#include <LiquidCrystal.h>
#include <Process.h>
#include <Bridge.h>
#include <stdio.h>



//Adjust from here

//Increase message size if you add more messages
const int messageSize = 4;
//Put in your messages here. Also add 16 spaces after the message helps clear the screen Be mindful of the commas after each message
String messages[messageSize] = {"#donate refugees  Save the Children  Followers 132,979 Tweets 19,100  Total contributions 294 million GBP CEO salary 264,638 GBP                ",
                                "#donate refugees  UN High Commissioner for Refugees  Followers 1,860,232 Tweets 25,774  Total contributions 88.9 million GBP  US CEO salary 136,619 GBP                ",
                                "##Aylan Kurdi  Just Giving Aylan Kurdi Fundraising  Total contributions 80,958 GBP CEO salary N/A  Twitter Followers 2975  Tweets 4,189                 ",
                                "#donate refugees  The dead boy on the beach photo increased one charity’s daily fundraising from 7,214 GBP to 793,630 GBP                 "
                               };
//This adjust how long the solenoid will run for
const int sTiming = 15;
// scroll text
const int scrollText = 300;

//The high and low ranges of the random time between messages
int randomLowTime = 3;
int randomHighTime = 6;
// Adjusts the multiplier for in between messages
long waitTime = 1000;

//Python scripts
String pythonScriptStart = "python /root/playerR.py -play";                         
String pythonScriptStop = "python /root/playerR.py -stop";   

//Adjust to here

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//solenoid
#define solenoidPin 8


int randomMessage = 0;
int randomSound = 0;
String message = "";
int counter = 0;

Process playing;
long randomTime = 0;

unsigned long demoPreviousMillis = 0;        // will store last time LED was updated

boolean generateRandom = true;
boolean runText = false;
boolean runSound = false;

void setup() {
  // put your setup code here, to run once:
  Bridge.begin();
  Serial.begin(9600);
  lcd.begin(8, 2);
  //runText = true;
  //runSound == true;
  randomSeed(A0);
  pinMode(solenoidPin, OUTPUT);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:


  if (generateRandom == true) {
    randomTime = long(random(randomLowTime, randomHighTime)) * waitTime;
    Serial.println(randomTime);
    generateRandom = false;
// Uncomment to see time on LCD Screen    
//    lcd.setCursor(0, 0);
//    lcd.print("waiting");
//    lcd.setCursor(0, 1);
//    lcd.print(randomTime);
  }

  if (generateRandom == false) {
    unsigned long demoCurrentMillis = millis();

    if (demoCurrentMillis - demoPreviousMillis >= randomTime) {
      // save the last time you blinked the LED
      demoPreviousMillis = demoCurrentMillis;
      generateRandom = true;
      runText = true;
      Serial.println("triggered");
      lcd.clear();
    }

  }

  if (runText == true) {
    if (playing.running()) {
      Process p;
      p.runShellCommand(pythonScriptStop);
      p.close();
    }

    player();

    digitalWrite(solenoidPin, HIGH);
    delay(sTiming);
    digitalWrite(solenoidPin, LOW);
    delay(sTiming);
    
    randomMessage = random(0, messageSize);
    Serial.print("randomMessage: ");
    Serial.println(randomMessage);
    message = messages[randomMessage];
    Serial.println(message);

    for (int i = 0; i < message.length(); i++) {
      //Serial.println("get in here");
      String left = message.substring(i, 8 + i);
      lcd.setCursor(0, 0);
      lcd.print(left);
      lcd.setCursor(0, 1);
      String right = message.substring(8 + i, 17 + i);
      lcd.print(right);
      delay(scrollText);
    }

    runText = false;
    generateRandom = true;


    lcd.clear();
  }
}

void player() {
  playing.runShellCommandAsynchronously(pythonScriptStart);
  delay(500);

}


