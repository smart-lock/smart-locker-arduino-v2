#ifndef BackendService_h
#define BackendService_h
#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>

class BackendService {
  public:
    BackendService(Client& espClient, const char *domain, const uint16_t port );
    void fetchLockerCluster(String macAddress);
  private:
    HttpClient *_client;
};
#endif