/* NodeMCU Obstacle detection using Ultrasonic Sensor with BLYNK IOT
 * The RGB LED used in this project works under COMMON ANODE configuration
 *  
 */

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLGYSTexqw"  // Blynk Template ID
#define BLYNK_DEVICE_NAME "NodeMCU"  // Blynk Device Name
#include <BlynkSimpleEsp8266.h>
char auth[] = "uWCVD14-BYBBp1vwQjcSVvV9qyfOdqer"; // Blynk AUTHORIZATION token 

#define trig 5  //Trigger pin of Ultrasonic Sensor
#define echo 4  //Echo pin of Ultrasonic Sensor
#define red 14  // Red pin of the RGB LED
#define green 12 //Green pin of the RGB LED
#define blue 13  //Blue pin of the RGB LED  
#define buzz 0  //Buzzer pin    

void setup() 
{
  Serial.begin(115200);
  pinMode(trig,OUTPUT);   
  pinMode(echo,INPUT);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(buzz,OUTPUT);
  Blynk.begin(auth,"SSID","PASSWORD"); //SSID AND PASSWORD
  
}

BLYNK_CONNECTED() //Sync the previous state of the LED from Blynk
{
  
  Blynk.syncAll();
  Blynk.syncVirtual(V10);
  Blynk.syncVirtual(V11);
  Blynk.syncVirtual(V12);
  
}

void loop() {

  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  float duration = pulseIn(echo,HIGH);
  float distance = duration * 0.034 /2; //Distance Calculation for the ultrasonic sensor 
  Serial.print("Distance :");
  Serial.println(distance);
  Blynk.virtualWrite(V2,distance);   
  if(distance<=25)  //Obstacle is very close
  { 
    Serial.print(" TOO CLOSE : RED \n");
    digitalWrite(red,LOW);  //LOW activates the pin due to the LED being in Common Anode Configuration
    digitalWrite(green,HIGH); //HIGH turns off the pin 
    digitalWrite(blue,HIGH);
    Blynk.virtualWrite(V10,HIGH);
    Blynk.virtualWrite(V11,LOW);
    Blynk.virtualWrite(V12,LOW);
    tone(buzz,1000,100);  

    
  }
  else if(distance>25 && distance<=75)  //Nearing an obstacle
  { Serial.print(" Approaching Obstacle : YELLOW \n");
    digitalWrite(red,LOW);
    digitalWrite(green,LOW);
    digitalWrite(blue,HIGH);
    Blynk.virtualWrite(V10,HIGH);
    Blynk.virtualWrite(V11,HIGH);
    Blynk.virtualWrite(V12,LOW);
    tone(buzz,440,150);
     
  }
  else //No obstacle in the path
  { Serial.print(" Route Clear : GREEN \n");
    digitalWrite(red,HIGH);
    digitalWrite(green,LOW);
    digitalWrite(blue,HIGH);
    Blynk.virtualWrite(V10,LOW);
    Blynk.virtualWrite(V11,HIGH);
    Blynk.virtualWrite(V12,LOW);
  }
  
  Blynk.run();

}
