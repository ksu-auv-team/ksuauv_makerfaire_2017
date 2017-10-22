 #include<Servo.h>

const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance;
int to_ESC=0;

Servo esc; //creates servo class

void setup() {
  //set up Ultrasonic
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  //the trigPin and the echoPin are two of the four prongs that come from the sensor, look at the front of the sensor to see the small print corresponding to each prong.
   
  //set up ESC and motor output
esc.attach(8); //connect a wire to Digital output 8
esc.writeMicroseconds(0); //send a PWM singal to ESC
  //The ESC will read the output given by the Arduino and convert it to a signal that is recognizable to the motor.
Serial.begin(9600); // Starts the serial communication for all devices
}


// All the stuff below is what determines the speed the motor runs at. Look at how the signal given by the sensor is calculated to 'distance', and how the distance is used
// to calculate the speed output of the motor.
void loop() {
  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance 
distance= duration*0.034/2;
//Serial.print("Distance: ");
//Serial.println(distance);
//This code below sends a signal to the ESC to move the motor
if (distance < 10)
  to_ESC=1500;
 else if(distance > 50)             
  to_ESC=1000;                         
 else {                             
 to_ESC= 1500-(7.5*distance);}
 //This stuff above is the logic sequence for the motor. In summary, the motor will reach max speed at '10' distance and begin to run at '50' distance. 
 //Anything greater or less than those digits will flatline inorder to prevent the motor from overworking itself at max speed, and spin only when in desired range.
 

esc.writeMicroseconds(to_ESC);

// Prints the distance on the Serial Monitor
//Serial.print("Distance: ");
//distance = constrain(distance, 0, 82);
//Serial.println(distance);
//Serial.print("PWM Output: ");
//Serial.println(to_ESC);
delay(2);
}

