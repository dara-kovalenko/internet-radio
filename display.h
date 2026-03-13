#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

class DisplayManager {
private:
    Adafruit_ST7735 tft;

public:
    DisplayManager(int cs, int dc, int rst) : tft(cs, dc, rst) {}

    void begin() {
        tft.initR(INITR_BLACKTAB);
        tft.setRotation(1); 
        tft.fillScreen(ST7735_BLACK);
    }

    void showStartup() {
        tft.setTextColor(ST7735_CYAN);
        tft.setTextSize(1);
        tft.setCursor(10, 20);
        tft.println("ESP32 Radio Starting...");
        tft.setCursor(10, 40);
        tft.print("Connecting to WiFi");
    }

    void printProgressDot() {
        tft.print(".");
    }

    void showConnected() {
        tft.setCursor(10, 60);
        tft.setTextColor(ST7735_GREEN);
        tft.println("WiFi OK!");
    }

    void drawStaticUI() {
        tft.fillScreen(ST7735_BLACK);
        tft.fillRect(0, 0, 160, 20, ST7735_BLUE);
        tft.setTextColor(ST7735_WHITE);
        tft.setTextSize(1);
        tft.setCursor(20, 6);
        tft.print("ESP32 INTERNET RADIO");
        tft.drawLine(0, 80, 160, 80, ST7735_WHITE);
    }

    void showLoading() {
        tft.fillRect(0, 21, 160, 58, ST7735_BLACK); 
        tft.setCursor(10, 45);
        tft.setTextColor(ST7735_YELLOW);
        tft.setTextSize(2);
        tft.print("Loading...");
    }

    void updateStation(int index, int total, const String& name) {
        tft.fillRect(0, 21, 160, 58, ST7735_BLACK); 
        tft.setCursor(10, 30);
        tft.setTextColor(ST7735_YELLOW);
        tft.setTextSize(1);
        tft.print("Channel: ");
        tft.print(index + 1);
        tft.print("/");
        tft.print(total);

        tft.setCursor(10, 50);
        tft.setTextColor(ST7735_CYAN);
        tft.setTextSize(2);
        tft.print(name);
    }

    void updateVolume(int volume, int maxVolume) {
        tft.fillRect(0, 85, 160, 43, ST7735_BLACK); 
        tft.setCursor(10, 90);
        tft.setTextColor(ST7735_WHITE);
        tft.setTextSize(1);
        tft.print("Volume: ");
        tft.print(volume);

        int max_bar_width = 140;
        int bar_width = map(volume, 0, maxVolume, 0, max_bar_width); 

        tft.drawRect(10, 105, max_bar_width, 10, ST7735_WHITE); 
        tft.fillRect(10, 105, bar_width, 10, ST7735_GREEN); 
    }
};