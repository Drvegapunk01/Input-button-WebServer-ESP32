#include <WiFi.h>
#include <WebServer.h>


const char* ssid = "123456789";
const char* pass = "123456789";
String html;
WebServer server(80);


void handleRoot(){
 
html = "<!DOCTYPE html>";
html += "<html>";
html += "<head>";
html += "<title>Input buttonL</title>";
html += "</head>";
html += "<body>";
html += "<h1 style=\"text-align: center;\" > Press the button</h1>";
html += "<button onclick=\"ON()\"> ON</button>";
html += "<button onclick=\"OFF()\"> OFF</button>";
html += "<script>";
html +="function ON(){fetch(\"/led/on\");}";
html +="function OFF(){fetch(\"/led/off\");}";
html +="</script>";
html +="</body>";
html +="</html>";
server.send(200,"text/html" ,html);
}



void ON(){
  digitalWrite(2,1);
    server.send(200,"text/html" ,html);
}



void OFF(){
    digitalWrite(2,0);
    server.send(200,"text/html" ,html);
}



void setup() {
  //inisialisasi bout rate
Serial.begin(115200);

pinMode(2,OUTPUT);
  //inisialisasi WIFI ssid dan pw
WiFi.begin(ssid,pass);

  Serial.println("menghubungkan ke " + String(ssid));


while(WiFi.status() != WL_CONNECTED){
  Serial.print(".");
}
    Serial.println("");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", handleRoot);
    server.on("/led/on", ON);
      server.on("/led/off", OFF);
  server.begin();
}

void loop() {
server.handleClient();

}
