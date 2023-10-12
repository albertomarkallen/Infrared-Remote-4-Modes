#include <IRremote.h> // Use Case Version 2
#include <NewTone.h>  // Can Use Together with IRremote but not Simultaneously
#include "musicConfig.h" // Contain Note Pitches, Song Melody and Duration
#include "command.h" // Contain Remote Specific Commands
#include "pinSetup.h"

int previousCommand = 0; // Used for Selecting Menu
int currentCommand = 0; // The Command When Remote is Pressed
int mode = 0; // 0 - No Mode ; 1 - Piano ; 2 - Garage Opener ; 3 - Volume ; 4 - Music and Light Show
int gateStatus = 1; //0 - Door Closed [All Lights On] ; 1 - Door Open [All Lights Off]
int gateProgress = 0; // 0 - Door is Steady ; 1 - Door is in Progress
int flag = 0; // 0 - Open Door ; 1 - Close Door ; 2 - Pause the Opening/Closing
int press = 1; // 0 - Pause ; 1- Continue

IRrecv receiver(irPin);

void setup() {

  pinMode(irPin,INPUT); // Setup LED and Buzzer as Output
  for(int i = 11 ; i >=4 ; i--){
    pinMode(i,OUTPUT);
  }
  Serial.begin(9600);
  receiver.enableIRIn(); // Start the receiver
}

void loop() {
  static int count = 5; //Used For Mode 2 in Tracking which LED is On or Off

  if (receiver.decode()) { // Decode when a button is pressed
    currentCommand = receiver.decodedIRData.command; 
    Serial.println(currentCommand);
    if(currentCommand == one && previousCommand == channel) // Check "Menu" Then "One" is clicked consecutively
      mode = 1;
    else if(currentCommand == two && previousCommand == channel) // Check "Menu" Then "One" is clicked consecutively
      mode = 2; 
    else if(currentCommand == three && previousCommand == channel)// Check "Menu" Then "One" is clicked consecutively
      mode = 3;
    else if(currentCommand == four && previousCommand == channel)// Check "Menu" Then "One" is clicked consecutively
      mode = 4;
    else if(currentCommand == backward)
      mode = 0;
   
    if(mode == 1) // Execute while in Mode 1
      modeOne(currentCommand);
    else if(currentCommand == play && mode == 2) // Check if Play is Pressed and in Mode Two [This only runs every button clicked, to make use of the Play Functionality]
      modeTwo(count);
    else if(mode == 3) // Execute while in Mode 3
      modeThree(currentCommand);
    else if(mode == 4){ // Execute while in Mode 4
      if(currentCommand == play){
        modeFour();
      }
    }
    previousCommand = currentCommand;
    receiver.resume();  // Receive the next value
  }

  if(mode == 2){
      if(gateProgress == 1 && flag == 2 && gateStatus == 1 && press == 1){
        gateProgress = 1;
        Serial.println(count);
        count--;
        if(count == 5){
          gateStatus = 1;
          gateProgress = 0;
          flag = 1;
        }
        digitalWrite(count,LOW);
        delay(500);
      }

      else if(gateProgress == 1 && flag == 2 && gateStatus == 0 && press == 1){
        gateProgress = 1;
        Serial.println(count);
        digitalWrite(count,HIGH);
        delay(500);
        count++;
        if(count == 12){
          gateStatus = 0;
          gateProgress = 0;
          flag = 0;
        }
      }
    
      else if(currentCommand == play && gateStatus == 1 && count < 13 && flag == 0){
        gateProgress = 1;
        Serial.println(count);
        digitalWrite(count,HIGH);
        delay(500);
        count++;
        if(count == 12){
          gateStatus = 0;
          gateProgress = 0;
        }
      }

      else if(currentCommand == play && gateStatus == 0 && count > 5 && flag == 1){
        gateProgress = 1;
        Serial.println(count);
        count--;
        if(count == 5){
          gateStatus = 1;
          gateProgress = 0;
        }
        digitalWrite(count,LOW);
        delay(500);
      }
    }
    delay(250);
}

int modeOne(int cmd){
  if(cmd == zero){
    digitalWrite(ledPin1,HIGH);
    NewTone(buzzerPin,1047,500);
    delay(125);
    digitalWrite(ledPin1,LOW);
  }

  else if(cmd == one){
    digitalWrite(ledPin2,HIGH);
    digitalWrite(ledPin3,HIGH);
    NewTone(buzzerPin,1245,500);
    delay(125);
    digitalWrite(ledPin2,LOW);
    digitalWrite(ledPin3,LOW);
  }

  else if(cmd == two){
    digitalWrite(ledPin3,HIGH);
    NewTone(buzzerPin,1319,500);
    delay(125);
    digitalWrite(ledPin3,LOW);
  }

  else if(cmd == three){
    digitalWrite(ledPin4,HIGH);
    NewTone(buzzerPin,1397,500);
    delay(125);
    digitalWrite(ledPin4,LOW);
  }

  else if(cmd == four){
    digitalWrite(ledPin4,HIGH);
    digitalWrite(ledPin5,HIGH);
    NewTone(buzzerPin,1480,500);
    delay(125);
    digitalWrite(ledPin4,LOW);
    digitalWrite(ledPin5,LOW);
  }
  
  else if(cmd == five){
    digitalWrite(ledPin5,HIGH);
    NewTone(buzzerPin,1568,500);
    delay(125);
    digitalWrite(ledPin5,LOW);
  }

  else if(cmd == six){
    digitalWrite(ledPin5,HIGH);
    digitalWrite(ledPin6,HIGH);
    NewTone(buzzerPin,1661,500);
    delay(125);
    digitalWrite(ledPin5,LOW);
    digitalWrite(ledPin6,LOW);
  }

  else if(cmd == seven){
    digitalWrite(ledPin6,HIGH);
    NewTone(buzzerPin,1760,500);
    delay(125);
    digitalWrite(ledPin6,LOW);
  }

  else if(cmd == eight){
    digitalWrite(ledPin6,HIGH);
    digitalWrite(ledPin7,HIGH);
    NewTone(buzzerPin,1865,500);
    delay(125);
    digitalWrite(ledPin6,LOW);
    digitalWrite(ledPin7,LOW);
  }

  else if(cmd == nine){
    digitalWrite(ledPin7,HIGH);
    NewTone(buzzerPin,1976,500);
    delay(125);
    digitalWrite(ledPin7,LOW);
  }

  else if(cmd == special2){
    digitalWrite(ledPin2,HIGH);
    NewTone(buzzerPin,1175,500);
    delay(125);
    digitalWrite(ledPin2,LOW);
  }

  else if(cmd == special1){
    digitalWrite(ledPin1,HIGH);
    digitalWrite(ledPin2,HIGH);
    NewTone(buzzerPin,1109,500);
    delay(125);
    digitalWrite(ledPin1,LOW);
    digitalWrite(ledPin2,LOW);
  }
}

int modeTwo(int count){
  if(count == 12)
    flag = 1;
  else if(count == 5)
    flag = 0;
  else if(count < 12 && count > 5){
    flag = 2;
    if(press == 1)
        press = 0;
    else if(press == 0)
        press = 1;
  }
      
}

int modeThree(int cmd){
  if(cmd == plus){
    for(int i = 11 ; i>=5 ; i--){
      digitalWrite(i,HIGH);
      delay(250);
    }
  }

  else if(cmd == minus){
    for(int i = 5 ; i <= 11 ; i++){
      digitalWrite(i,LOW);
      delay(250);
    }
  }
}

int modeFour(){
  for (int thisNote = 0; thisNote < 112; thisNote++) {
    int noteDuration = 750 / noteDurations[thisNote];
    digitalWrite(ledPin1,HIGH);
    digitalWrite(ledPin2,HIGH);
    digitalWrite(ledPin3,HIGH);
    digitalWrite(ledPin4,HIGH);
    digitalWrite(ledPin5,HIGH);
    digitalWrite(ledPin6,HIGH);
    digitalWrite(ledPin7,HIGH);
    NewTone(buzzerPin, melody[thisNote], noteDuration);
    delay(10);
    digitalWrite(ledPin1,LOW);
    digitalWrite(ledPin2,LOW);
    digitalWrite(ledPin3,LOW);
    digitalWrite(ledPin4,LOW);
    digitalWrite(ledPin5,LOW);
    digitalWrite(ledPin6,LOW);
    digitalWrite(ledPin7,LOW);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    noNewTone(buzzerPin);
  }
}




