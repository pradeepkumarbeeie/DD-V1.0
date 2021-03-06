#include <Wire.h>
#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads(0x49);
float Voltage = 0.0;
#include <Adafruit_Sensor.h> 
#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
const int selectPins[3] = {10, 9, 8}; // S0~8, S1~9, S2~10
const int zOutput = 5; 
int time = 1;
int Signal=0;
const int zInput = A0; // Connect common (Z) to A0 (analog input)
void setup() 
{
  Serial.begin(9600); // Initialize the serial port
  Serial.print("Time:"+String(time)+"\t"+"\t");
  //ads.setGain(GAIN_TWOTHIRDS);
  ads.begin();
  Serial.print("Time:"+String(time)+"\t"+"\t");
  if(!accel.begin())
   {
      Serial.println("No ADXL345 sensor detected.");
     while(1);
    //  Serial.print("Time:"+String(time)+"\t"+"\t");
   }
  for (int i=0; i<3; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);
    Serial.print("Time:"+String(time)+"\t"+"\t");
  }
  pinMode(zInput, INPUT); // Set up Z as an input
}

void loop() 
{ 
   sensors_event_t event; 
   accel.getEvent(&event);
  for (int n=0;n<8;n++)
  {
    if(time<=10){
      digitalWrite(selectPins[0], LOW);
      digitalWrite(selectPins[1], LOW);
      digitalWrite(selectPins[2], LOW);
      Signal=1;
      Serial.print("Time:"+String(time)+"\t"+"\t");
    }
    else if(time<=20&&time>10) {
      digitalWrite(selectPins[0], LOW);
      digitalWrite(selectPins[1], LOW);
      digitalWrite(selectPins[2], HIGH);
      Signal=2;
      }
    else if(time<=30&&time>20) {
      digitalWrite(selectPins[0], LOW);
      digitalWrite(selectPins[1], HIGH);
      digitalWrite(selectPins[2], LOW);
      Signal=3;
      }      
    else if(time<=40&&time>30) {
      digitalWrite(selectPins[0], LOW);
      digitalWrite(selectPins[1], HIGH);
      digitalWrite(selectPins[2], HIGH);
      Signal=4;
      }
      else if(time<=50&&time>40) {
      digitalWrite(selectPins[0], HIGH);
      digitalWrite(selectPins[1], LOW);
      digitalWrite(selectPins[2], LOW);
      Signal=5;
      }
      else if(time<=60&&time>50) {
      digitalWrite(selectPins[0], HIGH);
      digitalWrite(selectPins[1], LOW);
      digitalWrite(selectPins[2], HIGH);
      Signal=6;
      }
      else if(time<=70&&time>60) {
      digitalWrite(selectPins[0], HIGH);
      digitalWrite(selectPins[1], HIGH);
      digitalWrite(selectPins[2], LOW);
      Signal=7;
      }
      else {
      digitalWrite(selectPins[0], HIGH);
      digitalWrite(selectPins[1], HIGH);
      digitalWrite(selectPins[2], HIGH);
      Signal=8;
      }
      
  int inputValue = analogRead(A0); // and read Z
  int16_t adc0; // we read from the ADC, we have a sixteen bit integer as a result
  adc0 = ads.readADC_SingleEnded(0);
  Voltage = (adc0 * 0.1875)/1000;  
//  float f = ADS.toVoltage(1);  // voltage factor
  Serial.print("Time:"+String(time)+"\t"+"\t");
  Serial.print("Signal:"+String(Signal)+"\t");
  Serial.print("AIN0: "+String(adc0)+"\t");
  //Serial.print("Analog0: "+String(val_0)+String(val_0 * f, 3)+"\t");
  Serial.print("Analog"+String(inputValue)+"\t" );
  Serial.print("Voltage: "+String(Voltage)+"\t");
  Serial.print("X: "+String(event.acceleration.x)+"\t");
  Serial.print("Y: "+String(event.acceleration.y)+"\t");
  Serial.print("Z: "+String(event.acceleration.z)+"\t");
  Serial.print("\n");
  delay(1000);
  time=time+1;
  if(time==81)
  {
    time=0;
    Signal=0;
  }} 
}


