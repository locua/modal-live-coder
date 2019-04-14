#ifndef GRIDNODE_H
#define GRIDNODE_H
#include "ofxOsc.h"
#include "ofMain.h"

class Gridnode
{
public:
    Gridnode(int, string&);
    ofxOscMessage returnMessage();
    void activate();
    void deactivate();
    void draw(float, float);
    void update(int activeNode);
    void receiveFont(ofTrueTypeFont);
    //void getsymbols(string&);
private:
    bool nodeActive;
    int id;
    int numNodes;
    ofTrueTypeFont font;
    string symbolstring;
    string symboli;
};

#endif // GRIDNODE_H