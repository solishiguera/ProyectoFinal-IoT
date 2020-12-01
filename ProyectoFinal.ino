#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <FirebaseObject.h>

#define WIFI_SSID "InterCable97649063"
#define WIFI_PASSWORD "m78719ce82802"
#define FIREBASE_HOST "proyectocincoiot.firebaseio.com"
#define FIREBASE_AUTH "sNcrGfwNxSYsmtBC6XC9z1U0u7SWLAu6k24V4cfj"

#define LDR A0 // Mide luz
#define led D1 // Conectado a NODEMCU
int cont = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  Serial.println('\n');
    wifiConnect();

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    if (Firebase.failed()) {
        Serial.print(F("setting number failed:"));
        Serial.println(Firebase.error());
    } else {
        Serial.println("Firebase connected ");
    }
  
  delay(100);
}

void loop() {
  int *lightValue;
  int temp = calculaLumens(); 
  lightValue = &temp;  

  // Almacena datos en base de datos
  Firebase.setInt("Light",*lightValue);
  Serial.print("Light value:  ");
  Serial.println(*lightValue);

  if(WiFi.status() != WL_CONNECTED) {
      Serial.println("Disconnected");
  }

  // Cuando detecte menos de 150 lumens, enciende el LED
  if(*lightValue > 150) { 
    digitalWrite(led, HIGH);
    Firebase.setInt("LEDStatus", 0);
  } else {
    digitalWrite(led, LOW);
    Firebase.setInt("LEDStatus", 1);
  }
}


int calculaLumens() {
  /* Esta función permite calcular la cantidad de lumens que emite una fuente de luz*/
  // MY light bulb emits 800 Lumens
  float value = (analogRead(A0) * -1) + 1024;
  value *= 1.075; 
  return value; 
}


void wifiConnect() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);     //Conectar con la red WiFi
    Serial.print("Conectando WiFi --> ");
    Serial.print(WIFI_SSID); Serial.println(" ...");

    int teller = 0;
    while (WiFi.status() != WL_CONNECTED) {   //Esperar por la conexión WiFi
        delay(1000);
        Serial.print(++teller); Serial.print(' ');
    }

    Serial.println('\n');
    Serial.println("WiFi conectado!");  
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
} //End wifiConnect()
