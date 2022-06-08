#include <IRremote.h>

int RECV_PIN = 9;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  
  irrecv.enableIRIn(); // Start the receiver
  
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop()
{
  
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    
    if(results.value == 0x805FD827 || results.value==4294967295){
      //forward
      move(1,0,1,0);
      delay(500);
      move(0,0,0,0);
    }
    else if (results.value == 0x805F58A7 || results.value==4294967295){
      //right
      move(1,0,0,1);
      delay(500);
      move(0,0,0,0);
    }
    else if (results.value == 0x805FF807){
      //back
      move(0,1,0,1);
      delay(500);
      move(0,0,0,0);
    }
    else if (results.value == 0x805F7887){
     //left
      move(0,1,1,0);
      delay(500);
      move(0,0,0,0);
    }
    else{
      //stop
      move(0,0,0,0);
      delay(500);
      move(0,0,0,0);
    }
  }
  delay(100);
  
}

void move(int m1a, int m1b, int m2a, int m2b){
  digitalWrite(7,m1a);
  digitalWrite(6,m1b);
  digitalWrite(5,m2a);
  digitalWrite(4,m2b);
  
}
