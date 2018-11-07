#include <LiquidCrystal.h>
#include <Process.h>
#include <Bridge.h>
#include <stdio.h>



//Adjust from here

//Increase message size if you add more messages
const int messageSize = 4;
//Put in your messages here. Also add 16 spaces after the message helps clear the screen Be mindful of the commas after each message


//This adjust how long the solenoid will run for
const int sTiming = 15;
// scroll Time
const int scrollTime = 300;

//The high and low ranges of the random time between messages
long randomLowTime = 30000;
long randomHighTime = 60000;
// Adjusts the multiplier for in between messages


//Python scripts
String pythonScriptStart = "python /www/sd/playerH.py -play";
String pythonScriptStop = "python /www/sd/playerH.py -stop";
String twitterScript = "python /www/sd/twittersearchSingle.py \"donate hunger\"";
//Adjust to here

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//solenoid
#define solenoidPin 8


int randomMessage = 0;
int randomSound = 0;
String message = "";
int counter = 0;

Process playing;
Process twitter;
Process networkConnect;
long randomTime = 0;

unsigned long demoPreviousMillis = 0;        // will store last time LED was updated

boolean generateRandom = true;
boolean runText = false;
boolean runSound = false;

String messages;
String date;
String prevDate;
String connecting;

void setup() {
  // put your setup code here, to run once:
  Bridge.begin();
  Serial.begin(9600);
  message.reserve(200);
  date.reserve(20);
  prevDate.reserve(20);
  connecting.reserve(20);

  lcd.begin(8, 2);
  //runText = true;
  //runSound == true;
  randomSeed(analogRead(A0));
  pinMode(solenoidPin, OUTPUT);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:


  if (generateRandom == true) {
    randomTime = long(random(randomLowTime, randomHighTime));
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

    if (twitter.running()) {
      twitter.close();
    }

    if (checkConnection() == true) {
      if (checkScript() == true) {
        Serial.println("New message");
        player();
        digitalWrite(solenoidPin, HIGH);
        delay(sTiming);
        digitalWrite(solenoidPin, LOW);
        delay(sTiming);
        writingMessage("Test");
      }
    } else {
      player();
      digitalWrite(solenoidPin, HIGH);
      delay(sTiming);
      digitalWrite(solenoidPin, LOW);
      delay(sTiming);
      writingMessage("Test");
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

void writingMessage(String LCDprint) {
  Serial.print("Twitter: ");
  Serial.println(LCDprint);

  for (int i = 0; i < LCDprint.length(); i++) {
    //Serial.println("get in here");
    String left = LCDprint.substring(i, 8 + i);
    lcd.setCursor(0, 0);
    lcd.print(left);
    lcd.setCursor(0, 1);
    String right = LCDprint.substring(8 + i, 17 + i);
    lcd.print(right);
    delay(scrollTime);
  }

}

boolean checkScript() {
  Serial.println("checking for twitter messages...");

  twitter.runShellCommand(twitterScript);
  while (twitter.available()) {
    char c = twitter.read();
    date += c;
    LCDprint = c;
    Serial.print(c);  // Display the response
    writingMessage(); // Pass message to 
  }
  date.trim();
  Serial.println(date);

  if (date.equals(prevDate)) {
    date = "";
    return false;
  } else {
    prevDate = date;
    date = "";
    return true;
  }

}

boolean checkConnection() {
  networkConnect.runShellCommand("cat /sys/class/net/eth1/operstate");

  while (networkConnect.available()) {
    char c = networkConnect.read();
    connecting += c;
    //Serial.print(c);  // Display the response
  }
  connecting.trim();
  Serial.println(connecting);
  networkConnect.close();

  if (connecting.equals("up")) {
    Serial.println("Connection Up");
    connecting = "";
    return true;
  } else{
    Serial.println("Connection down");
    connecting = "";
    return false;
  }

}



