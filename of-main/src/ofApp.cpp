#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    auto start = chrono::high_resolution_clock::now();
    /* sound setup */
    sampleRate = 44100;
    bufferSize = 512;
    numChannels = 2;
    ofxMaxiSettings::setup(sampleRate, numChannels, bufferSize);
    ofSoundStreamSettings soundSettings;
    soundSettings.setOutListener(this);
    soundSettings.sampleRate = sampleRate;
    soundSettings.bufferSize = bufferSize;
    soundSettings.numOutputChannels = numChannels;
    soundSettings.numInputChannels = 0;
    soundStream.setup(soundSettings);
    /* load samples */
    kick.load("data/samples/hk.wav");
    snare.load("data/samples/sn.wav");
    highhat.load("data/samples/oh.WAV");
    bass.load("data/samples/bass.wav");


    hit = {1, 0, 0, 0};
    highhit = {0}; // ={1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    basshit = {0}; // {0, 1, 0, 1, 0, 1 , 0, 1, 0, 1, 0, 1, 0, 1, 0, 0};
    snarehit = {0}; //= {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1};

    env0.setAttack(300);
    env0.setDecay(100);
    env0.setSustain(100);
    env0.setRelease(400);

    auto finish = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = finish - start;
    cout << elapsed.count() << endl;


}

//--------------------------------------------------------------
void ofApp::update(){
    grid.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    grid.draw();

}

void ofApp::audioOut(ofSoundBuffer& buffer)
{
    for(int i = 0; i < buffer.getNumFrames(); ++i)
    {
        float vol = 0.4;
        // metronome that ticks 8 times a second
        currentCount = (int)timer.phasor(8);

        if(currentCount)
        {
            kicktrigger = hit[playHead%16];
            snaretrigger = snarehit[playHead%16];
            basstrigger = basshit[playHead%16];
            hattrigger = highhit[playHead%16];
            playHead++;
            lastCount = 0;
            //cout << "tick" << endl;
        }

        if(kicktrigger==1) kick.trigger();
        if(snaretrigger==1) snare.trigger();
        if(basstrigger==1) bass.trigger();
        if(hattrigger==1) highhat.trigger(); //cout << "trig" << endl;


        // ouput buffer
        float speed_m = ofMap(mouseX, 0, ofGetWidth(), 0, 5);
        //float synth0 = filter0.lores(osc0.sinewave(300), mouseX, 2);
        double synth0 = osc0.sinewave(300);
        double output = kick.playOnce(speed_m) +
                highhat.playOnce() +
                snare.playOnce() +
                bass.playOnce(2) +
                env0.adsr(synth0, synthtrigger);
        //double output = osc0.sinewave(osc1.sinewave(osc2.sinewave(0.1)*10)*880);
        buffer [i * buffer.getNumChannels()] = output*vol;
        buffer [i * buffer.getNumChannels() + 1] = output*vol;

        // set trigger to 0 at the end of each sample to guarantee retriggering.
        kicktrigger = 0;
        snaretrigger = 0;
        basstrigger = 0;
        hattrigger = 0; 
        synthtrigger = 0;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    grid.navigate(key);

    if(key=='k') kicktrigger=1;
    if(key=='b') basstrigger=1;
    if(key=='s') synthtrigger=1;
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
