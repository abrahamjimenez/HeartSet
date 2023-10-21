#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h> // Include the WiFiClientSecure library

ESP8266WiFiMulti WiFiMulti;

const char* ssid = "BYUI_Visitor";
const char* serverUrl = "https://heartset.us:443/receive";

int readBPMFromSerial() {
    if (Serial.available()) {
        String bpmString = Serial.readStringUntil('\n');
        return bpmString.toInt();
    }
    return -1;
}

void setup() {
  Serial.begin(9600);

  for (uint8_t t = 4; t > 0; t--) {
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid);

  pinMode(A0, INPUT);
}

void loop() {
  if (WiFiMulti.run() == WL_CONNECTED) {

    int bpm = readBPMFromSerial();
    if(bpm != -1 && bpm > 50) {
        String postData = "{\"heartRate\":" + String(bpm) + "}";

        WiFiClientSecure client; // Use WiFiClientSecure for SSL

        HTTPClient http;
        client.setInsecure();

        if (http.begin(client, serverUrl)) {
          http.addHeader("Content-Type", "application/json");
          Serial.print("[HTTP] POST...");
          Serial.println(postData);
          int httpCode = http.POST(postData);

          if (httpCode > 0) {
            Serial.printf("[HTTP] POST... code: %d\n", httpCode);

            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
              String payload = http.getString();
              Serial.println(payload);
            }
          } else {
            Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
          }

          http.end();
        } else {
          Serial.println("[HTTP] Unable to connect");
        }
    } else {
        Serial.println("No valid value detected on analog port.");
    }
  }

  delay(5000);
}