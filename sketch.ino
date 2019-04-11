#include <Bridge.h>
#include <LiquidCrystal.h>
#include <Process.h>
#include <SPI.h>
#include <SD.h>
#include "Quotes.h"

String lastTweet  = "exPrevTweet";


//solenoid
#define solenoidPin 8

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Process player;
Process tweetSearch;

//Python scripts
String pythonScriptStart = "python /root/player.py -play";
String pythonTweetScript = "python /mnt/sda1/arduino/www/twitter_hashtag_path.py";

//test script vv
//String pythonTweetScript = "python /mnt/sda1/arduino/www/test_python_script.py";


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
  ////// needed?
  lcd.clear();
}

boolean newTweetCheck(){
  SD.begin();
  //python should create file right away then add as needed
  if (!SD.exists("//////filename"){
    Serial.println("error: file does not exist -- undefined behavior ensuing");
  } 
  //input filename
  File file = sd.open("//////filename", FILE_READ);

  String tweet = "";

  char curChar = '';
  //need to mark and test EOF
  while (curChar != -1){
    tweet += curChar;

    curChar = file.read();
    if (curChar == '\n'){
      tweet = "";
    }
  }

  //tweet is now most recent tweet
  boolean retVal = true;
  if (tweet == lastTweet){
    retVal = false;
  }
  
  lastTweet = tweet;
  return retVal;
  
}

  
void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(A0));
  pinMode(solenoidPin, OUTPUT);
  
  // For debugging, wait until the serial console is connected
  delay(4000);
  while(!Serial);
  Bridge.begin();

  //create file and start writing tweets
  tweetSearch.runShellCommandAsynchronously(pythonTweetScript);

//  lcd.begin(8, 2);
//  delay(2000);
//  lcd.setCursor(0,0);
//  lcd.home();
//  lcd.clear();
  writeMessageToLCDandFireSolenoid();
//  lcd.print(F("01234567"));
//  delay(2000);
//  lcd.setCursor(0,1);
//  lcd.print(F("89abcdef"));
//  delay(2000);
  lcd.clear();
//  delay(4000);
  Serial.println("setup finished, file should be created, most likely empty");
  

}


void loop(){
  if (newTweetCheck()){
    writeMessageToLCDandFireSolenoid();
  }
  //wait 2 seconds between
  delay(2000);
}
