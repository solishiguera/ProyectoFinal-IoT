#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <FirebaseObject.h>

#define WIFI_SSID "InterCable97649063"
#define WIFI_PASSWORD "m78719ce82802"
#define FIREBASE_HOST "proyectocincoiot.firebaseio.com"
#define FIREBASE_AUTH "sNcrGfwNxSYsmtBC6XC9z1U0u7SWLAu6k24V4cfj"

//#define FIREBASE_HOST "testingpushdiego.firebaseio.com"
//#define FIREBASE_AUTH "cUUQrHZ2F1AslFmT0TPnZ8LmjWYorDctnggA0y88"

#define LDR A0 // Mide luz
#define led D1 // Conectado a NODEMCU
int cont = 0; 
int contador = 0;
int anterior = 0; 

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
  if(*lightValue != anterior) {
    if(contador == 0){
      Firebase.setInt("E0/Luz_Diego",*lightValue);
      ++contador;
    }
    else if(contador == 1){
      Firebase.setInt("E1/Luz_Diego",*lightValue);
      ++contador;
    }
    else if(contador == 2){
      Firebase.setInt("E2/Luz_Diego",*lightValue);
      ++contador;
    }
    else if(contador == 3){
      Firebase.setInt("E3/Luz_Diego",*lightValue);
      ++contador;
    }
    else if(contador == 4){
      Firebase.setInt("E4/Luz_Diego",*lightValue);
      contador = 0;
    }
    //Firebase.push("Luz",*lightValue); // Cambié a push
    Serial.print("Light value:  ");
    Serial.println(*lightValue);
  }

  if(WiFi.status() != WL_CONNECTED) {
      Serial.println("Disconnected");
  }

  // Verifica que la cantidad de lumens es menor a 150
  if(*lightValue <= 150) {
    cont ++;
  } else {
    cont = 0; 
  }
  
  // Cuando detecte que el contador es mayor a 5, se enciende LED
  // Esto se hace con la intención de evitar que se encienda y apague continuamente la luz, 
  // Y después de estar debajo de 150 lumens en 5 iteraciones seguidas, se enciende LED
  if(cont >= 5) { 
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }

  anterior = temp; 
  delay(100);
}


int calculaLumens() {
  /* Esta función permite calcular la cantidad
  de lumens que emite una fuente de luz*/
  // El foco de mi lámpara emite 800 Lumens. 
  //float value = (analogRead(A0) * -1) + 1024;
  float value = analogRead(A0); 
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
