#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "gridsheet.h"
#include "ofxMaxim.h"
#include <dirent.h>
#include <regex>

class ofApp : public ofBaseApp{

public:
    ~ofApp();
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void audioOut(ofSoundBuffer& buffer);
       // interface control stuff
    Gridsheet grid;
    ofTrueTypeFont font;
    string chars =  string("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVB NM1234567890");

    // ofxmaxim stuff
    int sampleRate;
    int bufferSize;
    int numChannels;
    ofSoundStream soundStream;
    // oscillators and samples
    ofxMaxiOsc osc0, osc1, osc2;
    ofxMaxiOsc timer;
    ofxMaxiSample kick;
    ofxMaxiSample snare;
    ofxMaxiSample highhat;
    ofxMaxiSample bass;
    vector<string> samplenames;
    vector<ofxMaxiSample> samples;
    vector<vector<int>> samplePatterns;
    vector<int> sampleTriggers;
    // envelopes
    maxiEnv env0;
    //ofxMaxiEnvelope env0;
    // filters
    maxiFilter filter0;
    //
    // delays
    //maxiFractionalDelay delay0;
    //
    //std::vector<ofxMaxiSample> samples;
    //int currentCount,lastCount,playHead,hit[16]={1,0,0,1,0,1,1,1,1,1,0,0,1,0,0,1}; //This is the sequence for the kick
    //int snarehit[16]={0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0};//This is the sequence for the snare
    int kicktrigger,snaretrigger,basstrigger,hattrigger, synthtrigger;

    std::vector<int> hit, snarehit, highhit, basshit;
    int currentCount,lastCount,playHead;

    // Language patterns and functions

    vector<vector<int>> randompatterns;
    vector<vector<int>> patternPatterns; // lol great name

    vector<int> randomTicker;

    maxiRecorder recorder;
};
