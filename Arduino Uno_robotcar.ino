 //motor driver
#define in1 4                                                           //defining const. variable named "in1" with value 0, which refers to the PICO D0.                  
#define in2 5                                                           //defining const. variable named "in2" with value 1, which refers to the PICO D1.                  
#define in3 6                                                           //defining const. variable named "in3" with value 2, which refers to the PICO D2.                  
#define in4 7                                                           //defining const. variable named "in4" with value 3, which refers to the PICO D3.                  
#define motorASpeedPin 3                  
#define motorBSpeedPin 9  
​
#define Echo 10 // attach pin D10 Arduino to pin Echo of HC-SR04
#define Trigger 11 // attach pin D9 Arduino to pin Echo of HC-SR04
int buzzer = 2;
int led_1 = 13;
int led_2 = 12;
long duration; // variable for the duration measurement
float distance; // variable for the distance measurement in cm unit. 
​
char val;              
                
/*                  
  forward function takes four arguments x, y, motorSpeed, speedPin.                  
  this function returns nothing.                  
  responsible for running motor A forward by a specific speed.                  
*/               
               
void forward(int x, int y, int motorSpeed, int speedPin) {                  
 digitalWrite(x, HIGH);                  
 digitalWrite(y, LOW);                  
 analogWrite(speedPin, motorSpeed);                  
}             
                 
/*                  
  backward function takes four arguments x, y, motorSpeed, speedPin.                  
  this function returns nothing.                  
  responsible for running motor B backward with a specific speed.                  
*/               
               
void backward(int x, int y, int motorSpeed, int speedPin) {                  
 digitalWrite(x, LOW);                  
 digitalWrite(y, HIGH);                  
 analogWrite(speedPin, motorSpeed);                  
}                  
            
void right(int motorSpeed) {                  
 forward(in1, in2, motorSpeed, motorASpeedPin);                  
 backward(in3, in4, motorSpeed, motorBSpeedPin);                  
}               
               
void left(int motorSpeed) {                  
 forward(in3, in4, motorSpeed, motorBSpeedPin);                  
 backward(in1, in2, motorSpeed, motorASpeedPin);                  
}               
               
void stopAll() {                  
 digitalWrite(in1, LOW);                  
 digitalWrite(in2, LOW);                  
 digitalWrite(in3, LOW);                  
 digitalWrite(in4, LOW);                  
}                 
             
void setup() {
    
  // Buzzer
  pinMode(buzzer, OUTPUT);
  
  // LED
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
​
  // Ultrasonic Sensor
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
​
  
  pinMode(Trigger, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(Echo, INPUT); // Sets the EchoPin as an input
  Serial.begin(9600); //Start the Serial Port at 9600 baud (default)
  
                  
 for (int i = 3 ; i <= 5 ; i++) {                  
   pinMode(i, OUTPUT);                  
 }                  
 for (int i = 7 ; i <= 9 ; i++) {                  
   pinMode(i, OUTPUT);                  
 }                               
               
}                 
             
void loop() {
  
 // LED, Ultrasonic, Buzzer
 // Ultrasonic Sensor Part
  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(Echo, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
​
  // LED Part
  if (distance < 15)//activate only when distance is less than 15cm
    {
      digitalWrite(led_1, HIGH);
      digitalWrite(led_2, HIGH);  
      tone(buzzer,1200,500);
      stopAll();
  
    }
  else
    {
      digitalWrite(led_1, LOW);
      digitalWrite(led_2, LOW);
      
    }
   if (Serial.available() > 0) {                  
     val = Serial.read(); 
     Serial.println(val);                 
   }                  
   if (val == 'f') {                  
     forward(in1, in2, 255, motorASpeedPin);                  
     forward(in3, in4, 255, motorBSpeedPin);                  
     Serial.println("forward");                  
   }                  
   if (val == 'b') {                  
     backward(in1, in2, 255, motorASpeedPin);                  
     backward(in3, in4, 255, motorBSpeedPin);                  
     Serial.println("backward");                  
   }                  
   if (val == 'r') {                  
     right(255);                  
     Serial.println("right");                  
   }                  
   if (val == 'l') {                  
     left(255);                  
     Serial.println("left");                  
   }                  
   if (val == 's') {                  
     stopAll();                  
     Serial.println("stopAll");                  
   }                  
}    
