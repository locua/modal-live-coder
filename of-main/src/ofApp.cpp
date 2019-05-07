#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
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
    env0.setAttack(300);
    env0.setDecay(100);
    env0.setSustain(100);
    env0.setRelease(400);

    auto finish = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = finish - start;
    //cout << elapsed.count() << endl;
    /* Search through sample folder and retrieve file list and names
     * */
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("data/samples")) != NULL) {
      /* retrieve all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
          // cout << ent->d_name << endl;
          string filename = ent->d_name;
          smatch m;
          regex e1 (".wav");
          regex e2 (".WAV");
          if(std::regex_search(filename, m, e1) || std::regex_search(filename, m, e2))
          {
              cout << "sample found: " << filename << endl;
              samplenames.push_back(filename);
              ofxMaxiSample sample;
              samples.push_back(sample);
          }
      }
      closedir (dir);
    } else {
      /* could not open directory */
      perror ("");
    }
    /* load samples from sample list */
    for(int i = 0; i < samplenames.size(); i ++)
    {
        samples[i].load("data/samples/" + samplenames[i]);
        cout << samplenames[i] << " loaded" << endl;
        vector<int> patt = {0};
        sampleTriggers.push_back(0);
        samplePatterns.push_back(patt);
    }
    cout << "number of samples: " << samples.size() << ", " << sampleTriggers.size() << ", " << samplePatterns.size() << endl;
}

//--------------------------------------------------------------
void ofApp::update()
{
    grid.update();
    randompatterns = grid.getPatterns();

    for(int i = 0; i < randompatterns.size(); i++)
    {

        if(randompatterns[i][1]==j) // first argument is 0, ie sample 0
        {
            vector<int>::const_iterator start = randompatterns[i].begin() + 2;
            vector<int>::const_iterator end = randompatterns[i].end();
            vector<int> tmpvec(start, end);
            samplePatterns[j] = tmpvec;
        } else {
            samplePatterns[j] = {0};
            cout << "" << endl;
        }
    }

//    cout << randompatterns.size() << endl;
}

//--------------------------------------------------------------
void ofApp::draw()
{
    grid.draw();
}

void ofApp::audioOut(ofSoundBuffer& buffer)
{
    for(int i = 0; i < buffer.getNumFrames(); i++)
    {
        float vol = 0.4;
        // metronome that ticks 8 times a second
        currentCount = (int)timer.phasor(8);

        if(lastCount!=currentCount)
        {
            for(int j = 0; j < samplePatterns.size(); j ++)
            {
                sampleTriggers[j] = samplePatterns[j][playHead%16];
            }
            playHead++;
            lastCount = 0;
            //cout << "tick " << playHead << endl;
        }
        for(int j = 0; j < sampleTriggers.size(); j ++)
        {
            if(sampleTriggers[j]==1) samples[j].trigger();
        }

        // ouput buffer
        float speed_m = ofMap(mouseX, 0, ofGetWidth(), 0, 5);
        //float synth0 = filter0.lores(osc0.sinewave(300), mouseX, 2);
        double synth0 = osc0.sinewave(300);
        double output;
        if(samples.size()>0){
            output = samples[0].playOnce();
            for(int j = 1; j < samples.size(); j ++)
            {
                output += samples[j].playOnce();
            }
        }
        //double output = osc0.sinewave(osc1.sinewave(osc2.sinewave(0.1)*10)*880);
        buffer [i * buffer.getNumChannels()] = output*vol;
        buffer [i * buffer.getNumChannels() + 1] = output*vol;

        // set trigger to 0 at the end of each sample to guarantee retriggering.
        for(int j = 0; j < sampleTriggers.size(); j++)
        {
            sampleTriggers[j]=0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    grid.navigate(key);

    if(key=='k') sampleTriggers[0]=1;
    if(key=='b') sampleTriggers[1]=1;
    if(key=='s') sampleTriggers[2]=1;
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
