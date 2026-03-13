#include <Arduino.h>
#include "config.h"
#include "wifi_connection.h"
#include "display.h"
#include "audio.h"
#include "buttons.h"

DisplayManager display(Config::PIN_TFT_CS, Config::PIN_TFT_DC, Config::PIN_TFT_RST);
AudioPlayer audioPlayer;
InputController input;

int currentVolume = Config::DEFAULT_VOLUME;
int stationIndex = 0;

void onWifiProgress() {
    Serial.print(".");
    display.printProgressDot();
}

void onWifiConnected() {
    Serial.println("\nCONNECTED");
    display.showConnected();
}

void updateFullUI() {
    display.updateStation(stationIndex, Config::STATION_COUNT, Config::STATION_NAMES[stationIndex]);
    display.updateVolume(currentVolume, Config::MAX_VOLUME);
}

void switchStation() {
    display.showLoading();
    audioPlayer.playStation(Config::STATIONS[stationIndex]);
    updateFullUI();
}

void setup() {
    Serial.begin(115200);

    input.begin();
    display.begin();
    display.showStartup();

    WifiHandler::connect(Config::SSID, Config::PASSWORD, onWifiProgress, onWifiConnected);
    delay(1000);

    display.drawStaticUI();
    
    audioPlayer.setVolume(currentVolume, Config::MAX_VOLUME);
    switchStation();
}

void loop() {
    audioPlayer.loop();
    ButtonAction action = input.checkButtons();
    
    switch (action) {
        case ButtonAction::NEXT:
            stationIndex = (stationIndex + 1) % Config::STATION_COUNT;
            switchStation();
            break;

        case ButtonAction::PREV:
            stationIndex = (stationIndex - 1 + Config::STATION_COUNT) % Config::STATION_COUNT;
            switchStation();
            break;

        case ButtonAction::VOL_UP:
            if (currentVolume < Config::MAX_VOLUME) {
                currentVolume++;
                audioPlayer.setVolume(currentVolume, Config::MAX_VOLUME);
                display.updateVolume(currentVolume, Config::MAX_VOLUME);
            }
            break;

        case ButtonAction::VOL_DOWN:
            if (currentVolume > 0) {
                currentVolume--;
                audioPlayer.setVolume(currentVolume, Config::MAX_VOLUME);
                display.updateVolume(currentVolume, Config::MAX_VOLUME);
            }
            break;

        case ButtonAction::NONE:
        default:
            break;
    }
}