// Project 50 – Creating an IR Remote Control Arduino

#include <IRremote.h> 
int receiverpin = 2;
IRrecv irrecv(receiverpin); 
decode_results results;
void setup()
{
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT); 
delay(500);
digitalWrite(3, HIGH);
digitalWrite(4, HIGH);
digitalWrite(5, HIGH);
digitalWrite(6, HIGH);
digitalWrite(7, HIGH);
delay(500);
digitalWrite(3, LOW);
digitalWrite(4, LOW);
digitalWrite(5, LOW);
digitalWrite(6, LOW);
digitalWrite(7, LOW);
delay(500); 
                            // code above is just testing led functionality
  Serial.begin(9600);       // start serial monitor  
  irrecv.enableIRIn();      // start receiver
  for (int z = 3 ; z < 8 ; z++)  
  {
    pinMode(z, OUTPUT);
  }
}

void translateIR() 
// takes action based on IR code received
// uses Saumsung IR codes from https://github.com/lepiaf/IR-Remote-Code/blob/master/README.md
{
  switch(results.value)
  {
    case 0xE0E020DF:  Serial.println("1 received"); digitalWrite(3, HIGH); delay(100); digitalWrite(3, LOW); break;
    case 0xE0E0A05F:  Serial.println("2 received"); digitalWrite(4, HIGH); delay(100); digitalWrite(4, LOW); break;
    case 0xE0E0609F:  Serial.println("3 received"); digitalWrite(5, HIGH); delay(100); digitalWrite(5, LOW); break;
    case 0xE0E010EF:  Serial.println("4 received"); digitalWrite(6, HIGH); delay(100); digitalWrite(6, LOW); break;
    case 0xE0E0906F:  Serial.println("5 received"); digitalWrite(7, HIGH); delay(100); digitalWrite(7, LOW); break;
    default: Serial.println("received unknown button press!"); break;
  }
}

 void pinOn(int pin) // turns on digital pin "pin" for 1 second
{
  digitalWrite(pin, HIGH);
  delay(1000);
  digitalWrite(pin, LOW);
}

void loop() 
{
   if (irrecv.decode(&results))    // have we received an IR signal?
  {
    translateIR();
     for (int z = 0 ; z < 2 ; z++) // ignore the 2nd and 3rd repeated codes
    {
      irrecv.resume();            // receive the next value
    }
  }
}