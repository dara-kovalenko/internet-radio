#pragma once
#include <WiFi.h>

class WifiHandler {
public:
    static void connect(const char* ssid, const char* password, void (*onProgress)(), void (*onConnected)()) {
        WiFi.disconnect();
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            if(onProgress) onProgress();
        }

        WiFi.setSleep(false);
        if(onConnected) onConnected();
    }
};