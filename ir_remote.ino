/*

*/

#include <IRremote.h>  //including infrared remote header file  
#include <Servo.h>     //including servo motor header file

int RECV_PIN  = 7; // the pin where you connect the output pin of IR sensor  
int BLUE_PIN  = 12;
int RED_PIN   = 9;
int GREEN_PIN = 10;
int SERVO_PIN = 13;


Servo myservo;
IRrecv irrecv(RECV_PIN);     
decode_results results;     

void setup()     
{     
  Serial.begin(9600);
  Serial.println("Setup Test JK");
  irrecv.enableIRIn();
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  
  // Set Primary colour to white
  RGB_color(255, 255, 255);
  
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
        RGB_color(0,255,0);
        break;
      case 6375:
        // red
        RGB_color(255,0,0);
        break;
      case 31365:
        // blue
        RGB_color(0,0,255);
        break;
      case -23971:
        // off
        RGB_color(0,0,0);
        break;
      case 25245:
        // volume up
        // run servo clockwise 5 seconds
        RGB_color(255,0,0);
        motor(80,5000);
        RGB_color(0,0,0);
        break;
      case -22441:
        // volume down
        // run servo anti-clockwise 5 seconds
        RGB_color(255,0,0);
        motor(100,5000);
        RGB_color(0,0,0);
        break;
      case -28561:
        // Up buttom
        // move clockwise for 0.5 seconds
        RGB_color(0,255,0);
        motor(80,500);
        RGB_color(0,0,0);
        break;
      case -8161:
        // Down button
        // move anti clockwise for 0.5 seconds
        RGB_color(0,255,0);
        motor(100,500);
        RGB_color(0,0,0);
        break;
      default:
        // Do nothing
        break;
   }
   irrecv.resume(); // Restart the ISR state machine and Receive the next value     
  }
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(RED_PIN, red_light_value);
  analogWrite(GREEN_PIN, green_light_value);
  analogWrite(BLUE_PIN, blue_light_value);
}

void motor (int val,int ms) {
  // turn
  myservo.write(val);
  // for how long
  delay(ms);
  // stop
  myservo.write(90);
}

