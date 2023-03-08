

// Define pins for ultrasonic and buzzer
int const trigPin = 4; // Trigger pin for ultrasonic sensor
int const echoPin = 5; // Echo pin for ultrasonic sensor
int const buzzPin = 6; // Pin for the buzzer
int duration; // Variable to store the duration of the ultrasonic signal
int distance; // Variable to store the distance measured by the ultrasonic sensor

//PIR Sensor
int motorPin = 7; // Pin to control the motor
int sensor = 8; // Pin for the PIR sensor
int state = LOW; // Variable to store the current state of the PIR sensor (HIGH if motion is detected, LOW otherwise)
int value = 0; // Variable to store the value read from the PIR sensor
//int led = 13; //Led pin no 
//int buttonpin=12;

// Setup function - runs once when the Arduino is powered on or reset
void setup()
{   
    // Start serial communication with a baud rate of 9600
    Serial.begin(9600);
    
    // Set the trigger pin as an output and the echo pin as an input
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 
    
    // Set the buzzer pin as an output
    pinMode(buzzPin, OUTPUT); 
    
    // Set the motor pin as an output and the PIR sensor pin as an input
    pinMode(motorPin, OUTPUT);    
    pinMode(sensor, INPUT); 
}


void loop()
{
    // Send a pulse to the ultrasonic sensor
    digitalWrite(trigPin, HIGH);
    delay(1);
    digitalWrite(trigPin, LOW);
   
    // Measure the duration of the echo and calculate distance
    duration = pulseIn(echoPin, HIGH, 30000); // waits for the pin to go HIGH, measures duration, and returns the duration in microseconds
    distance = (duration / 2) / 29.1; // divide the duration by 2 to account for the time it takes for the sound wave to travel to the object and back, and then divide by 29.1 to convert microseconds to centimeters

    //Serial.print("Distance1: ");
    //Serial.println(distance);
    delay(100); // wait for 100ms before continuing
    
    // If the distance is within 70cm and greater than 0cm, turn on the buzzer and flash it three times
    if (distance <= 70 && distance > 0) {
        digitalWrite(buzzPin, HIGH);
        delay(1000);
        digitalWrite(buzzPin, LOW);
        digitalWrite(buzzPin, HIGH);
        delay(1000);
        digitalWrite(buzzPin, LOW);
        digitalWrite(buzzPin, HIGH);
        delay(1000);
        digitalWrite(buzzPin, LOW);
    } 
    // If the distance is greater than 70cm or less than or equal to 0cm, turn off the buzzer
    else {
        digitalWrite(buzzPin, LOW);
    }
    
    // Read the state of the PIR sensor
    value = digitalRead(sensor);
    
    // If motion is detected, turn on the motor and print a message to the serial monitor
    if (value == HIGH) { 
        digitalWrite(motorPin, HIGH);
        if (state == LOW) {
            Serial.println("Motion Detected ");
            state = HIGH;
        }    
    } 
    // If motion is not detected, turn off the motor and print a message to the serial monitor
    else {
        digitalWrite(motorPin, LOW);
        if(state == HIGH){
            Serial.println("Motion Ended ");
            state = LOW;
        }   
    }      
}
