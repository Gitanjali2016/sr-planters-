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
String pythonScriptStart = "python /root/playerH.py -play";
String pythonScriptStop = "python /root/playerH.py -stop";
String twitterScript = "python /root/twittersearchSingle.py \"donate hunger\"";
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
        writingMessage();
      }
    } else {
      player();
      digitalWrite(solenoidPin, HIGH);
      delay(sTiming);
      digitalWrite(solenoidPin, LOW);
      delay(sTiming);
      writingMessage();
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

void writingMessage() {
  randomMessage = random(0, messageSize);
  Serial.print("randomMessage: ");
  Serial.println(randomMessage);

  if (randomMessage == 0) {
    message = "#donate hunger  Action Against Hunger  Followers 10,482  Tweets 13,722  Total contributions 189.8 million GBP  Executive US Director salary 140,896 GBP                 ";
  } else if (randomMessage == 1) {
    message = "#donate hunger  Heifer International   Followers 247,650  Tweets 20,490  Total contributions  72.1 million  CEO salary 203,323 GBP               ";
  } else if (randomMessage == 2) {
    message = "#donate hunger  Oxfam International  Followers 711, 288  Tweets 24,982  Total contributions  10.6 million  President salary 284,320 GBP                ";
  } else if (randomMessage == 3) {
    message = "#donate hunger  51% of social media users hear about new social good initiatives on social media first                 ";
  }

  Serial.println(message);

  for (int i = 0; i < message.length(); i++) {
    //Serial.println("get in here");
    String left = message.substring(i, 8 + i);
    lcd.setCursor(0, 0);
    lcd.print(left);
    lcd.setCursor(0, 1);
    String right = message.substring(8 + i, 17 + i);
    lcd.print(right);
    delay(scrollTime);
  }

}

boolean checkScript() {
  Serial.println("checking script");

  twitter.runShellCommand(twitterScript);

  while (twitter.available()) {
    char c = twitter.read();
    date += c;
    //Serial.print(c);  // Display the response
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



