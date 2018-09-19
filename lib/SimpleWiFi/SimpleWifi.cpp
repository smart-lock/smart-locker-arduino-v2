#include "SimpleWifi.h"
#include <ESP8266WiFi.h>

void byteArrayToCharArray(byte array[], unsigned int len, char buffer[])
{
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
        buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
    }
    buffer[len*2] = '\0';
}


SimpleWifi::SimpleWifi(const char* ssid, const char* password) {
 _ssid = ssid;
 _password = password;
  
  // byte mac[6];
  // char macChar[6];
  // WiFi.macAddress(mac);
  // byteArrayToCharArray(mac, 6, macChar);
  // deviceId = String(macChar);
}

void SimpleWifi::setup() {
 delay(10);
  // Connect to WIFI
  Serial.print("Connecting to ");
  Serial.println(_ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}