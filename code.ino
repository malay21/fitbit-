#include <Wire.h>                                       //library to connect 2 two wire interface
#include <MPU6050.h>                                    //for interfacing the mpu6050 sensor
#include <SoftwareSerial.h>                             //comunicate with arduino serial monitor and BT module
SoftwareSerial BTSerial(2, 3);                          //connecting HC-05 for transmission BTserial(TX , RX)
MPU6050 mpu;

/*connections

mpu6050 :
VCC -> 3.3V
GND -> gnd
SCL -> A5
SDA -> A4

HC-05 :
VCC -> 5V
GND -> GND
TXD -> D2
RXD -> D3
*/

unsigned long timer = 0;
float timeStep = 0.01;
float x= 0;
float y = 0;
float z = 0;
float a=0;
int step1;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)){
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    BTSerial.print("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  mpu.calibrateGyro();
  mpu.setThreshold(3);
}

void loop()
{
  float temp = mpu.readTemperature();
  a=(x+y)/2;
  timer = millis();
  Vector norm = mpu.readNormalizeGyro();

  x = x + norm.YAxis * timeStep;                                          //raw data of roll
  y = y + norm.XAxis * timeStep;                                          //raw data of pitch
  z = z + norm.ZAxis * timeStep;                                          //raw data of yaw

  delay((timeStep*1000) - (millis() - timer));
  if((x+y)/2!=a){
    step1++;
    float dist=step1*1.2;
    Serial.print("  steps : ");
    Serial.print(step1);
    Serial.print("  temp : ");
    Serial.print(temp);
    Serial.print("  dist : ");
    Serial.println(dist);
    BTSerial.print("\n");
    BTSerial.print(" steps : ");
    BTSerial.print(step1);
    BTSerial.print(" temp : ");
    BTSerial.print(temp);
    BTSerial.print(" dist : ");
    BTSerial.print(dist);
    BTSerial.print(" ft");
    delay(800);
  } 
}
