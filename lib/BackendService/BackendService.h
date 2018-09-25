#ifndef BackendService_h
#define BackendService_h
#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>


struct LockerExternal {
  char idInCluster;
  const char *id;
  bool busy;
  int row;
  int column;
  uint8_t sensorPin;
  uint8_t lockPin;
  uint8_t alarmPin;
};


class BackendService {
  public:
    BackendService(Client& espClient, const char *domain, const uint16_t port );
    void fetchLockerCluster(String macAddress, std::vector<LockerExternal> *response);
    void fetchNextLocker(String macAddress, LockerExternal* lockerExternal);
  private:
    HttpClient *_client;
};
#endif