#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp()
{
//    recorder.stopRecording();
}

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
        sampleTriggers.push_back(0);
        vector<int> patt = {0};
        samplePatterns.push_back(patt);
        randomTicker.push_back(0);
    }
    cout << "number of samples: " << samples.size() << ", " << sampleTriggers.size() << ", " << samplePatterns.size() << endl;

//    /* recording stuff */
//    recorder.setup("../test.wav");
//    recorder.startRecording();
}

//--------------------------------------------------------------
void ofApp::update()
{
    grid.update();
    randompatterns = grid.getPatterns();
    patternPatterns = grid.getPatternFunctions();
    for(int i = 0; i < samplePatterns.size();i++)
    {
        samplePatterns[i]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        for(int j = 0; j < randompatterns.size(); j ++)
        {
            if(randompatterns[j][1]==i)
            {
                vector<int>::const_iterator first = randompatterns[j].begin() + 2;
                vector<int>::const_iterator last = randompatterns[j].end();
                vector<int> tmpvec(first, last);
                samplePatterns[i]=tmpvec;
            }
        }
    }

    for(int i = 0; i <samplePatterns.size(); i++)
    {
        for(int j = 0; j < patternPatterns.size(); j ++)
        {
            if(patternPatterns[j][1]==i)
            {
                vector<int>::const_iterator first = patternPatterns[j].begin() + 2;
                vector<int>::const_iterator last = patternPatterns[j].end();
                vector<int> tmpvec(first, last);
                samplePatterns[i]=tmpvec;
            }
        }
    }
}



//--------------------------------------------------------------
void ofApp::draw()
{
    grid.draw();
    // cout << randompatterns.size() << endl;
}

void ofApp::audioOut(ofSoundBuffer& buffer)
{
    for(int i = 0; i < buffer.getNumFrames(); i++)
    {
        float vol = 0.4;
        // metronome that ticks 8 times a second
        currentCount = (int)timer.phasor(8);
        // sequencing loop
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
        //float synth0 = filter0.lores(osc0.sinewave(300), mouseX, 2);
        //double synth0 = osc0.sinewave(300);
        double output;
        if(samples.size()>0){
            output = samples[0].playOnce(1.0);
            for(int j = 1; j < samples.size(); j ++)
            {
                output += samples[j].playOnce(1.0);
            }
        }
        //double output = osc0.sinewave(osc1.sinewave(osc2.sinewave(0.1)*10)*880);
        buffer [i * buffer.getNumChannels()] = output*vol;
        buffer [i * buffer.getNumChannels() + 1] = output*vol;
        // pass output to recorder //
        //recorder.passData(&buffer[i*buffer.getNumChannels()], buffer.getNumFrames());

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
    //if(key=='s') samplePatterns[0] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
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
    for(int i = 0; i < samplePatterns.size(); i++)
    {
        for(int j =0; j < samplePatterns[i].size(); j++)
        {
            cout << samplePatterns[i][j];
        }
        cout << "" << endl;
    }
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
