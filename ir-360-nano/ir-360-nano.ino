/*

*/

#include <IRremote.h>  //including infrared remote header file  
#include <Servo.h>     //including servo motor header file

int RECV_PIN  = 6; // the pin where you connect the output pin of IR sensor  
int RED_PIN   = 3;
int GREEN_PIN = 2;
int SERVO_PIN = 12;
// Setup mode
int setup_ready = 0;
// Blinds should be set to closed position in setup stage
int b_status = 0; // 0 - Closed , 1 - Open

// Set open/close speed
int blind_speed = 30;
// Set open/close duration
int duration = 10000;
// Continious motion control
int motion = 0;
// Continious motion value
int mot_val = 90;


Servo myservo;
IRrecv irrecv(RECV_PIN);     
decode_results results;     

void setup()     
{     
  Serial.begin(9600);
  Serial.println("Setup Test JK");
  Serial.println(b_status);
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
  if (setup_ready) {
    digitalWrite(RED_PIN,LOW); 
  } else {
    digitalWrite(RED_PIN,HIGH);
  }
    
  if (irrecv.decode(&results))// Returns 0 if no data ready, 1 if data ready.     
  {     
   int readResults = results.value;// Results of decoding are stored in result.value               
   Serial.println(readResults); //prints the value a a button press
   switch(readResults) {
      case -23971:
        // Setup Mode
        // Coming in or out of status mode, blinds should be set to closed position
        b_status = 0;
        if (setup_ready) {
          setup_ready = 0;
        } else {
          setup_ready = 1;
        }
        break;
      case 25245:
        // volume up
        // open
        // run servo clockwise 5 seconds
        if (setup_ready) {
          open_blinds();
        } else {
          blink_red();
        }
        break;
      case -22441:
        // volume down
        // close
        // run servo anti-clockwise 5 seconds
        if (setup_ready) {
          close_blinds();
        } else {
          blink_red();
        }
        break;
      case -28561:
        // Up buttom
        // move clockwise for 0.5 seconds
        // motor(80,500);
        digitalWrite(GREEN_PIN,HIGH);
        motion = 1;
        mot_val = 90 - blind_speed;
        cont_run();
        break;
      case -8161:
        // Down button
        // move anti clockwise for 0.5 seconds
        // motor(100,500);
        digitalWrite(GREEN_PIN,HIGH);
        motion = 1;
        mot_val = 90 + blind_speed;
        cont_run();
        break;
      case -7651:
        // Func/Stop button
        motion = 0;
        mot_val = 90;
        myservo.write(90);
        blink_red();
        break;
      default:
        // If motion is on , keep it running
        break;
   }
   irrecv.resume(); // Restart the ISR state machine and Receive the next value     
  }
}

void blink_red () {
  digitalWrite(GREEN_PIN,LOW);
  for (int i=0;i<5;i++) {
    digitalWrite(RED_PIN,HIGH);
    delay(100);
    digitalWrite(RED_PIN,LOW);
    delay(100);
  }
}

void open_blinds() {
  Serial.println("Open");
  Serial.println(b_status);
  if (b_status == 0) {
    digitalWrite(GREEN_PIN,HIGH);
    int open_speed = 90 - blind_speed;
    myservo.write(open_speed);
    delay(duration);
    myservo.write(90);
    b_status = 1;
    digitalWrite(GREEN_PIN,LOW);
  } else {
    blink_red();
  }
}

void close_blinds() {
  Serial.println("Open");
  Serial.println(b_status);
  if (b_status == 1) {
    digitalWrite(GREEN_PIN,HIGH);
    int close_speed = 90 + blind_speed;
    myservo.write(close_speed);
    delay(duration);
    myservo.write(90);
    b_status = 0;
    digitalWrite(GREEN_PIN,LOW);
  } else {
    blink_red();
  }
}

void cont_run () {
  // continious run
  if (motion) {
    myservo.write(mot_val);
  } else {
    myservo.write(90);
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
