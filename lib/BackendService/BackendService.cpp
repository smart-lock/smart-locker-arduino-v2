#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
#include <BackendService.h>

BackendService::BackendService(Client& espClient, const char *domain, const uint16_t port) {
  _client = new HttpClient(espClient, domain, port);
}

String response;
int statusCode = 0;

void BackendService::fetchLockerCluster(String macAddress) {
  Serial.println("making GET request");
  String endpoint = "/locker-cluster/" + macAddress;
  _client->get(endpoint.c_str());

  // read the status code and body of the response
  statusCode = _client->responseStatusCode();
  response = _client->responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
}





// RestClient client = RestClient("http://192.168.1.34:3003");

// void fetchLockerCluster(String macAddress) {
//   String response;
//   String endpoint = "/locker-cluster/" + macAddress;

//   Serial.println(endpoint);

//   int code = client.get(endpoint.c_str(), &response);
//   Serial.println(code);
//   Serial.println(response);
// }
