#include "gridnode.h"

Gridnode::Gridnode(int _id, string& symbolstring)
{
    id = _id;
    nodeActive = false;
    symboli = ofToString(symbolstring[int(ofRandom(0, symbolstring.size()))]);
}

ofxOscMessage Gridnode::returnMessage()
{
    cout << "gridNode " << id << " returned a message" << endl;
    ofxOscMessage m;
    m.setAddress("/nodetrigger");
    m.addIntArg(id);
    return m;
}

void Gridnode::changesymbol(int key)
{
    //cout << char(key) << endl;
    symboli = char(key);
}

void Gridnode::activate()
{
    nodeActive = true;
}

void Gridnode::deactivate()
{
    nodeActive = false;
}

void Gridnode::draw(float w, float h)
{
    ofSetColor(126, 0, 135);
    //ofDrawRectangle(w, h, 2, 2);
    font.drawString(symboli, w-5, h+5);
    if(nodeActive)
    {
        ofNoFill();
        ofDrawRectangle(w-5, h-7, 10, 14);
    }

}

void Gridnode::update(int activeNode)
{
    if(id == activeNode){
        this->activate();
    } else {
        this->deactivate();
    }
}

void Gridnode::receiveFont(ofTrueTypeFont f)
{
    font = f;
}

