#ifndef GRIDSHEET_H
#define GRIDSHEET_H
#include "ofMain.h"
#include "gridnode.h"
#define PORT 57120
#define HOST "localhost"

class Gridsheet
{
public:
    Gridsheet();
    ~Gridsheet();
    void draw();
    void navigate(int);
    void update();
private:
    int cols;
    int rows;
    float edge;
    float width;
    float height;
    int numNodes;
    int activeNode;
    std::vector<Gridnode*> gridnodes;
    ofxOscSender sender;
    ofTrueTypeFont font;
    string symbols;
};

#endif // GRIDSHEET_H