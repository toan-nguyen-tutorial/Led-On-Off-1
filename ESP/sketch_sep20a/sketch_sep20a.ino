#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Ngoc Hong";          // Tên WiFi của bạn
const char* password = "ngochong2020";   // Mật khẩu WiFi
const char* serverUrl = "http://192.168.1.3:3000/led";  // Địa chỉ Node.js server

const int ledPin = D2;  // Chân GPIO2 của ESP8266
WiFiClient client;     // Tạo đối tượng WiFiClient

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Ban đầu tắt đèn

  WiFi.begin(ssid, password);
  
  // Chờ kết nối WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Đang kết nối WiFi...");
  }
  Serial.println("Đã kết nối WiFi!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // Sử dụng WiFiClient khi gọi http.begin
    http.begin(client, serverUrl); // Địa chỉ URL của server
    int httpCode = http.GET(); // Thực hiện yêu cầu GET

    if (httpCode > 0) {
      String payload = http.getString();  // Nhận phản hồi từ server
      
      if (payload == "on") {
        digitalWrite(ledPin, HIGH);  // Bật đèn LED
        Serial.println("Đèn LED được bật!");
      } else if (payload == "off") {
        digitalWrite(ledPin, LOW);   // Tắt đèn LED
        Serial.println("Đèn LED được tắt!");
      }
    } else {
      Serial.println("Không thể kết nối đến server!");
    }

    http.end(); // Kết thúc kết nối HTTP
  }

  
}
