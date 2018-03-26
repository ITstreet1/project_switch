#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "54b8b03edd494f4a885171e47adf0a9e";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "dekip_network";
char pass[] = "0611975itstreet";

// Set your LED and physical button pins here
const int rlyPin1 = 13;
const int rlyPin2 = 12;
const int rlyPin3 = 14;
const int rlyPin4 = 4;
const int btnPin1 = 5;
const int btnPin2 = 16;
const int btnPin3 = 15;
const int btnPin4 = A0;

BlynkTimer timer;
void checkPhysicalButton();

int rlyState1 = LOW;
int rlyState2 = LOW;
int rlyState3 = LOW;
int rlyState4 = LOW;
int btnState1 = LOW;
int btnState2 = LOW;
int btnState3 = LOW;
int btnState4 = LOW;

// Every time we connect to the cloud...
BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);
  Blynk.syncVirtual(V4);

  // Alternatively, you could override server state using:
  //Blynk.virtualWrite(V2, ledState);
}

// When App button is pushed - switch the state
BLYNK_WRITE(V1) {
  rlyState1 = param.asInt();
  digitalWrite(rlyPin1, rlyState1);
}
BLYNK_WRITE(V2) {
  rlyState2 = param.asInt();
  digitalWrite(rlyPin2, rlyState2);
}
BLYNK_WRITE(V3) {
  rlyState3 = param.asInt();
  digitalWrite(rlyPin3, rlyState3);
}
BLYNK_WRITE(V4) {
  rlyState4 = param.asInt();
  digitalWrite(rlyPin4, rlyState4);
}

void checkPhysicalButton()
{
  if (digitalRead(btnPin1) == LOW) {
    // btnState is used to avoid sequential toggles
    if (btnState1 != LOW) {

      // Toggle LED state
      rlyState1 = !rlyState1;
      digitalWrite(rlyPin1, rlyState1);

      // Update Button Widget
      Blynk.virtualWrite(V1, rlyState1);
    }
    btnState1 = LOW;
  } else {
    btnState1 = HIGH;
  }
  if (digitalRead(btnPin2) == LOW) {
    // btnState is used to avoid sequential toggles
    if (btnState2 != LOW) {

      // Toggle LED state
      rlyState2 = !rlyState2;
      digitalWrite(rlyPin2, rlyState2);

      // Update Button Widget
      Blynk.virtualWrite(V2, rlyState2);
    }
    btnState2 = LOW;
  } else {
    btnState2 = HIGH;
  }
  if (digitalRead(btnPin3) == LOW) {
    // btnState is used to avoid sequential toggles
    if (btnState3 != LOW) {

      // Toggle LED state
      rlyState3 = !rlyState3;
      digitalWrite(rlyPin3, rlyState3);

      // Update Button Widget
      Blynk.virtualWrite(V3, rlyState3);
    }
    btnState3 = LOW;
  } else {
    btnState3 = HIGH;
  }
  int x=analogRead(btnPin4);
  int y;
  if(x<=300){
    y=LOW;
    }else{
      y=HIGH;
      }
  if (y == LOW) {
    // btnState is used to avoid sequential toggles
    if (btnState4 != LOW) {

      // Toggle LED state
      rlyState4 = !rlyState4;
      digitalWrite(rlyPin4, rlyState4);

      // Update Button Widget
      Blynk.virtualWrite(V4, rlyState4);
    }
    btnState4 = LOW;
  } else {
    btnState4 = HIGH;
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  pinMode(rlyPin1, OUTPUT);
  pinMode(rlyPin2, OUTPUT);
  pinMode(rlyPin3, OUTPUT);
  pinMode(rlyPin4, OUTPUT);
  pinMode(btnPin1, INPUT);
  pinMode(btnPin2, INPUT);
  pinMode(btnPin3, INPUT);
  pinMode(btnPin4, INPUT);
  digitalWrite(rlyPin1, LOW);
  digitalWrite(rlyPin2, LOW);
  digitalWrite(rlyPin3, LOW);
  digitalWrite(rlyPin4, LOW);

  // Setup a function to be called every 100 ms
  timer.setInterval(100L, checkPhysicalButton);
}

void loop()
{
  Blynk.run();
  timer.run();
}
