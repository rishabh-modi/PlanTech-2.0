


#include "dht.h"
#define dht_apin A1 // Analog Pin sensor is connected to





#define SensorPin A2            //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00            //deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection



int sensor_pin = A0; // Soil Sensor input at Analog PIN A0
int relay_pin = 8;



dht DHT;


int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;






int base_map = 700;
int top_map = 5;
int output_value;










void setup() {
  
  pinMode(sensor_pin,INPUT);

  pinMode(LED,OUTPUT);  

  pinMode(relay_pin,OUTPUT);
  
  Serial.begin(9600); 

  //Serial.println("DHT11 Humidity & temperature Sensor\n\n");



}














void loop() {
  
   output_value = map(analogRead(sensor_pin),base_map,top_map,0,100);
 
   Serial.print("Mositure : ");
 
   Serial.print(output_value);
 
   Serial.println("%");
 
  if(output_value<25) digitalWrite(relay_pin,LOW);
   else digitalWrite(relay_pin,HIGH);


   //-----------------------------temp-----------------------------







 DHT.read11(dht_apin);
    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    Serial.println("");




//------------------------------pH------------------------------------------








  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = 8.2*voltage+Offset;
      samplingTime=millis();
  }
  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
  Serial.print("Voltage:");
        Serial.print(voltage,2);
        Serial.print("    pH value: ");
  Serial.println(pHValue,2);
        digitalWrite(LED,digitalRead(LED)^1);
        printTime=millis();
  }
 

     delay(2000);//Wait 5 seconds before accessing sensor again.

   

}




double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}
