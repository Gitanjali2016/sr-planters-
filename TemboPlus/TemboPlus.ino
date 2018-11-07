#include <Bridge.h>
#include <LiquidCrystal.h>
#include <Temboo.h>
#include <Process.h>
#include <stdio.h>

#include "TembooAccount.h"
#include "Quotes.h"

int numRuns = 1;   // Execution count, so this doesn't run forever
int maxRuns = 1000;   // Maximum number of times the Choreo should be executed

int scroll_ms = 300;
int pump_ms = 15;

String lastTweetID =   "775455908814000128";
String latestTweetID = "000000000000000000";

int chosenRandomTweetCycles = 3;
int randRepsLo = 3;
int randRepsHi = 9;

//solenoid
#define solenoidPin 8

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Process player;


//Python scripts
String pythonScriptStart = "python /root/player.py -play";


void setup() {
//  Serial.begin(9600);

  randomSeed(analogRead(A0));
  pinMode(solenoidPin, OUTPUT);
  
  // For debugging, wait until the serial console is connected
  delay(4000);
//  while(!Serial);
  Bridge.begin();

  lcd.begin(8, 2);
  delay(2000);
  lcd.setCursor(0,0);
  lcd.home();
  lcd.clear();
  lcd.print(F("01234567"));
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print(F("89abcdef"));
  delay(2000);
  lcd.clear();
  delay(4000);
  
  
}

void writeMessageToLCDandFireSolenoid() {
  int choice = random(0, 4);
  String msg = "";
  String spacer = "                 ";
  if (choice == 0) {
    msg = text1 + spacer;
    
  } else if (choice == 1) {
    msg = text2 + spacer;
    
  } else if (choice == 2) {
    msg = text3 + spacer;
    
  } else if (choice == 3) {
    msg = text4 + spacer;
  }
  
  lcd.clear();

  player.runShellCommandAsynchronously(pythonScriptStart);

  digitalWrite(solenoidPin, HIGH);
  delay(pump_ms);
  digitalWrite(solenoidPin, LOW);
  delay(pump_ms);

  String substringA = "";
  String substringB = "";
  for (int i=0; i<(msg.length() - 16); i++) {
    
    substringA = msg.substring(i,(i+8));
    substringB = msg.substring((i+8),(i+16));
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(substringA);
    lcd.setCursor(0,1);
    lcd.print(substringB);
    delay(scroll_ms);
  }

//  if (player.running()) {
//    Process stopper;
//    stopper.runShellCommandAsynchronously(pythonScriptStop);
//    stopper.close();
//  }
}

void loop() {
  if (numRuns <= maxRuns) {
//    Serial.println("Running LatestTweet - Run #" + String(numRuns++));
    
//
//    TembooChoreo LatestTweetChoreo;
//    // Invoke the Temboo client
//    LatestTweetChoreo.begin();
//
//    // Set Temboo account credentials
//    LatestTweetChoreo.setAccountName(TEMBOO_ACCOUNT);
//    LatestTweetChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
//    LatestTweetChoreo.setAppKey(TEMBOO_APP_KEY);
//    
//    // Set Choreo inputs
//    LatestTweetChoreo.setProfile("donatehunger");                   // the profile is always donate hunger (this is a temboo thing)
//    LatestTweetChoreo.addInput("Query", query);
//    LatestTweetChoreo.addInput("SinceId", lastTweetID);
//
//    LatestTweetChoreo.addOutputFilter("id_str", "/statuses[0]/id_str", "Response");
//
//    
//    // Identify the Choreo to run
//    LatestTweetChoreo.setChoreo(F("/Library/Twitter/Search/LatestTweet"));
//    
//    // Run the Choreo; when results are available, print them to serial
//    unsigned int rc = LatestTweetChoreo.run();
//
//    if (rc == 0) {
//      while(LatestTweetChoreo.available()) {
//        latestTweetID = LatestTweetChoreo.readString();                 // takes 5+ seconds
////        Serial.print("latest:");
////        Serial.print(latestTweetID);
//      }
//    
//    } else {
//    
////      Serial.println("error");
//    
//      while(LatestTweetChoreo.available()) {
//        String name = LatestTweetChoreo.readStringUntil('\x1F');
//        name.trim();
//        String value = LatestTweetChoreo.readStringUntil('\x1E');
//        value.trim();
//        if (name == "HTTP_CODE") {
////          Serial.print(F("HTTP CODE: "));
////          Serial.println(value);
//        }
//      }
//    }
//    LatestTweetChoreo.close();
//
//    if (latestTweetID != lastTweetID) {
//      
//      lastTweetID = latestTweetID;
//    
////      Serial.println("---> LCD immediate...");
//      writeMessageToLCDandFireSolenoid();                                 // takes 15 + 1 seconds
//      
//
////      Serial.println(F("Waiting..."));
//      delay(5000);                                                        // takes 5 seconds
//      
//      chosenRandomTweetCycles = random(randRepsLo, randRepsHi);
//                    
//    } else {
//      
////      Serial.println("No news is good news.");
      
      if (chosenRandomTweetCycles <= 0) {
      
        chosenRandomTweetCycles = random(randRepsLo, randRepsHi);
        writeMessageToLCDandFireSolenoid();                               // takes 15 + 1 seconds
        
//        Serial.println(F("Waiting..."));
        delay(5000);                                                      // takes 5 seconds
      
      } else {

        chosenRandomTweetCycles -= 1;

//        Serial.println(F("Waiting..."));
        delay(20000);                                                        // takes 20 seconds
        
      }
//    }
  }
}
