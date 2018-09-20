#include <LockerWifi.h>
#include <ESP8266WiFi.h>

LockerWifi::LockerWifi(const char* ssid, const char* password) {
 _ssid = ssid;
 _password = password;
}

void LockerWifi::setup() {
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

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void LockerWifi::loop() {
  // noop for now
}