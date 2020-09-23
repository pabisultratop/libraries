#include "Connect.h"

Connect::Connect()
{

}

int Connect::Begin(const char* ssid, const char* password, const char* host)
{
  if (!Wifi(ssid, password))
    return 0;

  if (!DNS(host))
	return 0;

  if (!OTAServer())
	return 0;

  return 1;
}

int Connect::Wifi(const char* ssid, const char* password)
{
  /* Conecta-se a rede wi-fi */
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Conectado a rede wi-fi ");
  Serial.println(ssid);
  Serial.print("IP obtido: ");
  Serial.println(WiFi.localIP());

  return 1;
}

int Connect::DNS(const char* host)
{
  /* Usa MDNS para resolver o DNS */
  if (!MDNS.begin(host))
  {
    //http://host.local
    Serial.println("Erro ao configurar mDNS.");
    delay(1000);
    return 0;
  }

  Serial.println("mDNS configurado e inicializado;");
  return 1;
}

int Connect::OTAServer()
{
  /* Configfura as páginas de login e upload de firmware OTA */
  server.on("/", HTTP_GET, []()
  {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", loginIndex);
  });

  server.on("/serverIndex", HTTP_GET, []()
  {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });

  /* Define tratamentos do update de firmware OTA */
  server.on("/update", HTTP_POST, []()
  {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();

    if (upload.status == UPLOAD_FILE_START)
    {
      /* Inicio do upload de firmware OTA */
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN))
        Update.printError(Serial);
    }
    else if (upload.status == UPLOAD_FILE_WRITE)
    {
      /* Escrevendo firmware enviado na flash do ESP32 */
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize)
        Update.printError(Serial);
    }
    else if (upload.status == UPLOAD_FILE_END)
    {
      /* Final de upload */
      if (Update.end(true))
        Serial.printf("Sucesso no update de firmware: %u\nReiniciando ESP32...\n", upload.totalSize);
      else
        Update.printError(Serial);
    }
  });
  server.begin();
  return 1;
}

void Connect::OTAHandler()
{
  server.handleClient();
  delay(1);
}
