/*

*/

#include <IRremote.h>  //including infrared remote header file  
#include <Servo.h>     //including servo motor header file

int RECV_PIN  = 6; // the pin where you connect the output pin of IR sensor  
int RED_PIN   = 3;
int GREEN_PIN = 2;
int SERVO_PIN = 12;
int ready = 0;


Servo myservo;
IRrecv irrecv(RECV_PIN);     
decode_results results;     

void setup()     
{     
  Serial.begin(9600);
  Serial.println("Setup Test JK");
  irrecv.enableIRIn();
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  
  // Set in setup mode
  digitalWrite(RED_PIN,HIGH);
  digitalWrite(GREEN_PIN,LOW);
  
  // Initialise Servo
  myservo.attach(SERVO_PIN);
} 

void loop()     
{     
  if (irrecv.decode(&results))// Returns 0 if no data ready, 1 if data ready.     
  {     
   int readResults = results.value;// Results of decoding are stored in result.value               
   Serial.println(readResults); //prints the value a a button press
   switch(readResults) {
      case 12495:
        // green
        //RGB_color(0,255,0);
        break;
      case 6375:
        // red
        //RGB_color(255,0,0);
        break;
      case 31365:
        // blue
        //RGB_color(0,0,255);
        break;
      case -23971:
        // Setup Complete
        digitalWrite(RED_PIN,LOW);
        digitalWrite(GREEN_PIN,LOW);
        ready = 1;
        break;
      case 25245:
        // volume up
        // run servo clockwise 5 seconds
        if (ready) {
          digitalWrite(GREEN_PIN,HIGH);
          motor(80,5000);
          digitalWrite(GREEN_PIN,LOW);
        } else {
          blink_red();
        }
        break;
      case -22441:
        // volume down
        // run servo anti-clockwise 5 seconds
        if (ready) {
          digitalWrite(GREEN_PIN,HIGH);
          motor(100,5000);
          digitalWrite(GREEN_PIN,LOW);
        } else {
          blink_red();
        }
        break;
      case -28561:
        // Up buttom
        // move clockwise for 0.5 seconds
        digitalWrite(RED_PIN,HIGH);
        motor(80,500);
        digitalWrite(RED_PIN,LOW);
        break;
      case -8161:
        // Down button
        // move anti clockwise for 0.5 seconds
        digitalWrite(RED_PIN,HIGH);
        motor(100,500);
        digitalWrite(RED_PIN,LOW);
        break;
      default:
        // Do nothing
        break;
   }
   irrecv.resume(); // Restart the ISR state machine and Receive the next value     
  }
}

void blink_red () {
  for (int i=0;i<5;i++) {
    digitalWrite(RED_PIN,HIGH);
    delay(500);
    digitalWrite(RED_PIN,LOW);
    delay(500);
    digitalWrite(RED_PIN,HIGH);
  }
}

void motor (int val,int ms) {
  // turn
  myservo.write(val);
  // for how long
  delay(ms);
  // stop
  myservo.write(90);
}

