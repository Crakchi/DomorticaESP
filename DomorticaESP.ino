#include <Arduino.h>

#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

const char* WIFI_SSID = "AccessNet_Nacho";
const char* WIFI_PASSWORD= "dobleele";


const char* API_KEY= "AIzaSyAU8Ah6vwr5btaVVfmx0sRnWf3e_LbHiac";

const char* DATABASE_URL= "https://riveradomotica-default-rtdb.firebaseio.com/"; //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app;

const char* USER_EMAIL= "brandon@rivera.com";
const char* USER_PASSWORD= "brandon@rivera.com";


FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;

const int BtCocina =23, BtBano =22, BtLavanderia =21,BtCuarto =19,BtSala =18, BtGaraje =5;
bool buttonState = false;


void setup_WIFI(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void setupFirebase() {
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
  config.signer.tokens.legacy_token = "<database secret>";
  Firebase.reconnectNetwork(true);
  fbdo.setBSSLBufferSize(4096, 1024);
  fbdo.setResponseSize(2048);
  Firebase.begin(&config, &auth);
  Firebase.setDoubleDigits(5);
  config.timeout.serverResponse = 10 * 1000;
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

}

void setup() {
    Serial.begin(115200);
    setup_WIFI();
    setupFirebase();
    pinMode(BtCocina,INPUT);
    pinMode(BtBano,INPUT);
    pinMode(BtCuarto,INPUT);
    pinMode(BtGaraje,INPUT);
    pinMode(BtLavanderia,INPUT);
    pinMode(BtSala,INPUT);
}

void loop() {

  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))  {
      buttonState = digitalRead(BtCocina);
      Serial.printf("MandandoDatos... %s\n", Firebase.RTDB.setBool(&fbdo, F("/Casa/Cocina"), buttonState) ? "ok" : fbdo.errorReason().c_str());
  }
  
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))  {
      buttonState = digitalRead(BtBano);
      Serial.printf("MandandoDatos... %s\n", Firebase.RTDB.setBool(&fbdo, F("/Casa/Bano"), buttonState) ? "ok" : fbdo.errorReason().c_str());
  }
  
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))  {
      buttonState = digitalRead(BtCuarto);
      Serial.printf("MandandoDatos... %s\n", Firebase.RTDB.setBool(&fbdo, F("/Casa/Cuarto"), buttonState) ? "ok" : fbdo.errorReason().c_str());
  }
  
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))  {
      buttonState = digitalRead(BtGaraje);
      Serial.printf("MandandoDatos... %s\n", Firebase.RTDB.setBool(&fbdo, F("/Casa/Garaje"), buttonState) ? "ok" : fbdo.errorReason().c_str());
  }
  
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))  {
      buttonState = digitalRead(BtSala);
      Serial.printf("MandandoDatos... %s\n", Firebase.RTDB.setBool(&fbdo, F("/Casa/Sala"), buttonState) ? "ok" : fbdo.errorReason().c_str());
  }
  
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))  {
      buttonState = digitalRead(BtLavanderia);
      Serial.printf("MandandoDatos... %s\n", Firebase.RTDB.setBool(&fbdo, F("/Casa/Lavanderia"), buttonState) ? "ok" : fbdo.errorReason().c_str());
  }

}
