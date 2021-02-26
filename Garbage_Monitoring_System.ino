#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

//#define trig D2
//#define echo D4

int trigPin = 2;
int echoPin = 4;

long duration;
int distance;

// You should get Auth Token in the Blynk App.

char auth[] = "M9EN7Nqfxu_ACkxjcL31W7LxXeI0L5Sj";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ruhan";
char pass[] = "ruhan119";

BlynkTimer timer;

void setup()
{
  // Debug console
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
void sendSensor()
{
  digitalWrite(trigPin, LOW);   // Makes trigPin low
  delayMicroseconds(2);       // 2 micro second delay

  digitalWrite(trigPin, HIGH);  // tigPin high
  delayMicroseconds(10);      // trigPin high for 10 micro seconds
  digitalWrite(trigPin, LOW);   // trigPin low

  duration = pulseIn(echoPin, HIGH);   //Read echo pin, time in microseconds
  distance = duration * 0.034 / 2;   //Calculating actual/real distance

  Serial.print("Distance = ");        //Output distance on arduino serial monitor
  Serial.println(distance);
  
  if(distance <= 10)
  {
//    Blynk.tweet("My Arduino project is tweeting using @blynk_app and it’s awesome!\n #arduino #IoT #blynk");
    Blynk.notify("Your trash is almost full!!!");
  }
  Blynk.virtualWrite(V0, distance);
  delay(1000);                        //Pause for 3 seconds and start measuring distance again
}
