#include "connection.hpp"
#include "comm_panel.hpp"

const char* WIFI_SSID = "U+Net8540";
const char* WIFI_PASSWORD = "6#9522K082";

const char* SERVER_IP = "192.168.219.107";
const uint16_t SERVER_PORT = 5555;

WiFiClient client;


void connectToWiFi()
{
    Serial.print("Connecting to Wi-Fi");

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("Wi-Fi connected");

    Serial.print("Wemos IP: ");
    Serial.println(WiFi.localIP());

    Serial.print("Signal strength: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
}

bool connectToServer()
{
    Serial.print("Connecting to server ");
    Serial.print(SERVER_IP);
    Serial.print(":");
    Serial.println(SERVER_PORT);

    if (client.connect(SERVER_IP, SERVER_PORT))
    {
        Serial.println("TCP connection established");
        return true;
    }

    Serial.println("TCP connection failed");
    return false;
}


void sendTelemetry(int angle, int btn1, int btn2)
{
    if (!client.connected())
    {
        client.stop();
        if (!connectToServer()){return;}
    }

    String message =
    "ANG=" + String(angle) +
    ";BT1=" + String(btn1) +
    ";BT2=" + String(btn2);

    Serial.print("Sending: ");
    Serial.println(message);

    client.println(message);

    unsigned long timeout = millis();

    while (!client.available())
    {
        if (millis() - timeout > 2000)
        {
            Serial.println("Server response timeout");
            client.stop();
            return;
        }

        delay(1);
    }

    String response = client.readStringUntil('\n');
    response.trim();

    Serial.print("Server response: ");
    Serial.println(response);
}
