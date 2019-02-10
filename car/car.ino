#include "nRF24L01.h" // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"

#define A1 5
#define A2 3
#define B1 6
#define B2 4

int ReceivedMessage[1] = {000}; // Used to store value received by the NRF24L01
RF24 radio(9,10); // NRF24L01 used SPI pins + Pin 9 and 10 on the UNO
const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 

void move_motor(int num, int val){
  if (num == 1){
    if (val < 0){
      digitalWrite(A1,LOW);
      analogWrite(A2,abs(val));
    }
    else{
      digitalWrite(A2,LOW);
      analogWrite(A1,val);
    }
  }
  else{
    if (val < 0){
      digitalWrite(B1,LOW);
      analogWrite(B2,abs(val));
    }
    else{
      digitalWrite(B2,LOW);
      analogWrite(B1,val);
    }
  } 
}

void move_motors(int left_val, int right_val){
  move_motor(1,left_val);
  move_motor(2,right_val);
}

void parse_message(int num){
  if (num == 000){
    move_motors(0,0);
  } 
  else if (num = 010){
    move_motors(-200,200);
  }
  else if (num = 020){
    move_motors(200,-200);
  }
  else if (num = 100){
    move_motors(200,200);
  }
  else if (num = 200){
    move_motors(-200,-200);
  }
  else if (num = 220){
    move_motors(-200,-250);
  }
  else if (num = 210){
    move_motors(-250,-200);
  }
  else if (num = 120){
    move_motors(250,200);
  }
  else if (num = 110){
    move_motors(200,250);
  }
}

void setup(void){
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(B1,OUTPUT);
  pinMode(B2,OUTPUT);
  
  radio.begin(); // Start the NRF24L01
  radio.openReadingPipe(1,pipe); // Get NRF24L01 ready to receive
  radio.startListening(); // Listen to see if information received
}

void loop(void){
  while (radio.available())
  {
    radio.read(ReceivedMessage, 1); // Read information from the NRF24L01
    delay(10);
  }
}
