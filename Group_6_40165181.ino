#include <Servo.h>
#define sensorPin PC3 //define US pin
int servoPin = PD2; //define servo pin
int servoPos = 85 ;
Servo servo;
int SensorLeft = PD3; //define IR1 pin
int SensorRight = PD4; //define IR2 pin
int distanceIRLeft;
int distanceIRRight;
int distanceUS;
int liftFan, thrustFan;

void setup() {
    Serial.begin(9600);
    //Setup servo
    servo.attach(servoPin);
    servo.write(servoPos);
    //setup IR
    Serial.println("IR sensor starts from now.");
    //setup US
    pinMode(sensorPin,INPUT);
    //setup fan
    liftFan = 9;
    thrustFan = 6;
    pinMode(thrustFan, OUTPUT);
    pinMode(liftFan, OUTPUT);
    analogWrite(thrustFan,200);
    analogWrite(liftFan,255);
    delay(0.5);
}
int returnDistanceIRLeft()
{
  return digitalRead(SensorLeft);
}

int returnDistanceIRRight()
{
  return digitalRead(SensorRight);
}

int returnDistanceUS()
{
  return analogRead(sensorPin) * 1.27;
}

void loop() {
  distanceUS = returnDistanceUS();
  distanceIRLeft = returnDistanceIRLeft();
  distanceIRRight = returnDistanceIRRight();
  Serial.println();
  Serial.println("==================================");
  Serial.print("Distance US sensor: ");
  Serial.print(distanceUS);
  Serial.println(" cm");
  Serial.print("Distance IR Left: ");
  Serial.println(distanceIRLeft);
  Serial.print("Disance US right: ");
  Serial.println(distanceIRRight);
  Serial.println("==================================");
  Serial.println();
  
  if (17 <= distanceUS && distanceUS < 40 && distanceIRLeft == 1&& distanceIRRight==0){
    servo.write(180); // competition turns.
    delay(1500); //in ms/
    servo.write(20);
    delay(900);
    servo.write(servoPos); //put the servo back in the zero position to allow forward thrust
    Serial.println("Turning Right.");
  }
  else if (17 <= distanceUS && distanceUS < 40 && distanceIRRight==1 && distanceIRLeft==0 )
  {
    servo.write(0);
    delay(2500); //wait 5 seconds before putting the fan back in the zero position/   
    servo.write(140);
    delay(800);
    servo.write(servoPos); //put the servo back in the zero position to allow forward thrust
    Serial.println("Turning Left.");
  }
  else if (distanceIRLeft == 1 && distanceIRRight ==0)
  {
      while(digitalRead(SensorLeft) == 1 && digitalRead(SensorRight) ==0) //in cm
      {
        servo.write(95); //turn fan 117 degrees to adjust position
        delay(200);
        Serial.println("Too close to the left side: Adujusting distance.");
        Serial.println();
        Serial.println("==================================");
        Serial.print("Distance US sensor: ");
        Serial.print(distanceUS);
        Serial.println(" cm");
        Serial.print("Distance IR Left: ");
        Serial.println(distanceIRLeft);
        Serial.print("Disance US right: ");
        Serial.println(distanceIRRight);
        Serial.println("==================================");
        Serial.println();
        distanceUS = returnDistanceUS();
        if (distanceUS <= 17)
          break;
      }
      servo.write(servoPos);
      delay(1000);
  }
  else if(distanceIRLeft ==0  && distanceIRRight == 1)
  {
    while(digitalRead(SensorLeft) ==0  && digitalRead(SensorRight) == 1)
    {
      servo.write(70); //67.5
      delay(300);
      Serial.println("Too close to the right side: Adujusting distance");
      Serial.println();
      Serial.println("==================================");
      Serial.print("Distance US sensor: ");
      Serial.print(distanceUS);
      Serial.println(" cm");
      Serial.print("Distance IR Left: ");
      Serial.println(distanceIRLeft);
      Serial.print("Disance US right: ");
      Serial.println(distanceIRRight);
      Serial.println("==================================");
      Serial.println();
      distanceUS = returnDistanceUS();
      
      if (distanceUS <= 17)
          break;
    }
    servo.write(servoPos);
    delay(1000);
  }
 /* else if (distanceUS < 20 && distanceIRLeft == 1 && distanceIRRight == 0)
  {
    servo.write(120);
    delay(2000);
    servo.write(servoPos);
  }
  else if (distanceUS < 20 && distanceIRLeft == 1 && distanceIRRight == 0)
  {
    servo.write(50);
    delay(2000);
    servo.write(servoPos);
  }*/
  else if (distanceIRRight == 1 && distanceIRLeft == 1 && distanceUS < 20)
  {

    servo.write(0);
    delay(800);
    servo.write(servoPos);
    delay(800); 
    
  }


}
