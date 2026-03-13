#pragma once
#include <Arduino.h>

namespace Config {
    constexpr int PIN_TFT_CS = 5;
    constexpr int PIN_TFT_RST = 4;
    constexpr int PIN_TFT_DC = 17;
    
    constexpr int PIN_VOL_UP = 27;
    constexpr int PIN_VOL_DOWN = 14;
    constexpr int PIN_PREV = 13;
    constexpr int PIN_NEXT = 33;

    const char* SSID = "OA_Inet_Free";
    const char* PASSWORD = "iloveoa!";

    constexpr int MAX_VOLUME = 21;
    constexpr int DEFAULT_VOLUME = 3;

    const String STATIONS[] = {
        "http://online.hitfm.ua/HitFM",
        "http://online.kissfm.ua/KissFM",
        "http://online.melodiafm.ua/MelodiaFM",
        "http://stream.radioparadise.com/mp3-128",
        "http://online.radioroks.ua/RadioROKS",         
        "http://icecastlv.luxnet.ua/luxlviv_hd",           
        "http://media-ice.musicradio.com/HeartLondonMP3",
        "http://media-ice.musicradio.com/SmoothUKMP3" 
    };

    const String STATION_NAMES[] = {
        "Hit FM", 
        "Kiss FM", 
        "Melodia FM", 
        "Paradise",
        "Radio ROKS", 
        "Lux FM", 
        "Heart London", 
        "Smooth Radio"
    };

    constexpr int STATION_COUNT = sizeof(STATIONS) / sizeof(STATIONS[0]);
}