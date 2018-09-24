#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
#include <BackendService.h>
#include <ArduinoJson.h>

BackendService::BackendService(Client& espClient, const char *domain, const uint16_t port) {
  _client = new HttpClient(espClient, domain, port);
}

String response;
int statusCode = 0;

struct Response {
  LockerExternal locker[];
};

void BackendService::fetchLockerCluster(String macAddress, std::vector<LockerExternal> *lockers) {
  Serial.println("making GET request");
  String endpoint = "/locker-cluster/" + macAddress;
  _client->get(endpoint.c_str());

  // read the status code and body of the response
  statusCode = _client->responseStatusCode();
  response = _client->responseBody();
  
  const size_t capacity = JSON_ARRAY_SIZE(6) + JSON_OBJECT_SIZE(1) + 6*JSON_OBJECT_SIZE(8) + 1403;
  DynamicJsonBuffer jsonBuffer(capacity);

  // Parse JSON object
  JsonObject& root = jsonBuffer.parseObject(response);

  if (!root.success()) {
    Serial.println(F("Parsing failed!"));
    return;
  }

  JsonArray& jsonLockers = root["lockers"];
  for (JsonObject& jsonLocker : jsonLockers) {
    LockerExternal locker;
    locker.id = jsonLocker["id"];
    const char *idInCluster = jsonLocker["idInCluster"].as<char*>();
    locker.idInCluster = idInCluster[0];
    locker.busy = jsonLocker["busy"];
    locker.row = jsonLocker["row"];
    locker.column = jsonLocker["column"];
    locker.sensorPin = jsonLocker["sensorPin"];
    locker.alarmPin = jsonLocker["alarmPin"];
    locker.lockPin = jsonLocker["lockPin"];
    lockers->push_back(locker);
  }
}