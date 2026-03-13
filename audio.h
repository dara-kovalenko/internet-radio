#pragma once
#include "AudioFileSourceHTTPStream.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

class AudioPlayer {
private:
    AudioGeneratorMP3* mp3;
    AudioFileSourceHTTPStream* file;
    AudioOutputI2S* out;

public:
    AudioPlayer() {
        out = new AudioOutputI2S(0, 1);
        mp3 = new AudioGeneratorMP3();
        file = nullptr;
    }

    void setVolume(int currentVol, int maxVol) {
        out->SetGain((float)currentVol / (float)maxVol);
    }

    void playStation(const String& url) {
        if (mp3->isRunning()) {
            mp3->stop();
        }
        if (file) {
            delete file;
        }
        file = new AudioFileSourceHTTPStream(url.c_str());
        mp3->begin(file, out);
    }

    void loop() {
        if (mp3->isRunning()) {
            if (!mp3->loop()) {
                mp3->stop();
            }
        }
    }
};