#include <iostream>
#include <string>
using namespace std;

class Codec {
public:
    virtual void decode(const string& fileName) = 0;
    virtual ~Codec() {}
};

class MP3Codec : public Codec {
public:
    void decode(const string& fileName) override {
        cout << "Playing " << fileName << " using MP3 codec." << endl;
    }
};

class WAVCodec : public Codec {
public:
    void decode(const string& fileName) override {
        cout << "Playing " << fileName << " using WAV codec." << endl;
    }
};

class MusicPlayer {
protected:
    Codec* codec;
public:
    MusicPlayer(Codec* c) : codec(c) {}
    virtual void start(const string& fileName) = 0;
    virtual ~MusicPlayer() { delete codec; }
};

class JazzPlayer : public MusicPlayer {
public:
    JazzPlayer(Codec* c) : MusicPlayer(c) {}
    void start(const string& fileName) override {
        cout << "Started Jazz Player..." << endl;
        codec->decode(fileName);
    }
};

class PopPlayer : public MusicPlayer {
public:
    PopPlayer(Codec* c) : MusicPlayer(c) {}
    void start(const string& fileName) override {
        cout << "Started Pop Player..." << endl;
        codec->decode(fileName);
    }
};

class RockPlayer : public MusicPlayer {
public:
    RockPlayer(Codec* c) : MusicPlayer(c) {}
    void start(const string& fileName) override {
        cout << "Started Rock Player..." << endl;
        codec->decode(fileName);
    }
};

int main() {
    MusicPlayer* jazzMp3 = new JazzPlayer(new MP3Codec());
    MusicPlayer* popWav  = new PopPlayer(new WAVCodec());
    MusicPlayer* rockFlac = new RockPlayer(new MP3Codec());

    jazzMp3->start("smooth_jazz.mp3");
    popWav->start ("top_hits.wav");
    rockFlac->start("heavy_rock.mp3");

    delete jazzMp3;
    delete popWav;
    delete rockFlac;

    return 0;
}