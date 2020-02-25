#include <ESP8266WiFi.h>

const char* ssid = "Honor 10";
const char* password = "123dupadupa";

WiFiServer server(80);

int ENA = 4;
int ENB = 14;
int IN1 = 0;
int IN2 = 2;
int IN3 = 12;
int IN4 = 13;

void setup() {
  Serial.begin(9600);
  delay(10);
   
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  
  server.begin();
  Serial.println("Server started");

  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void left() {
  
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, LOW);
  
  delay(1000); 
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
}

void back() {
  
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, HIGH);
  
  delay(1000); 
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
}

void forward() {
  
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW);
  
  delay(1000); 
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
}

void right() {
  
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, HIGH);
  
  delay(1000); 
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
}

void loop() {
 WiFiClient client = server.available();
 if (!client) {
  return;
 }

 Serial.println("new client");
 while(!client.available()){
  delay(1);
 }

 String request = client.readStringUntil('r');
 Serial.println(request);
 client.flush();
 
 if (request.indexOf("/w") != -1) {
    forward();
 }
  
 if (request.indexOf("/s") != -1) {
    back();  
 }

 if (request.indexOf("/a") != -1) {
    left();
 }

 if (request.indexOf("/d") != -1) {
    right();
 }

 client.println("HTTP/1.1 200 OK");
 client.println("Content-Type: text/html");
 client.println(""); 
 client.println("<!DOCTYPE HTML>");
 client.println("<html>");
 client.println("<br><br>");
 client.println("<a href=\"/w\"\"><button>Forward</button></a>");
 client.println("<a href=\"/s\"\"><button>Back</button></a><br />");
 client.println("<a href=\"/a\"\"><button>Left</button></a><br />");
 client.println("<a href=\"/d\"\"><button>Right</button></a><br />");
 client.println("</html>");

 delay(1);
 Serial.println("Client disonnected");
 Serial.println("");
}
