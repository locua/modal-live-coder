#include "gridsheet.h"

Gridsheet::Gridsheet()
{
    // init grid parameters
    cols = 40;
    rows = 30;
    edge = 20;
    width = ofGetWidth() - edge;
    height = ofGetHeight() - edge;
    numNodes = cols*rows;
    activeNode = 0;
    font.load("arial.ttf", 10);
    chars_ =  string("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVB NM1234567890");
    symbols = string("+");
    // initialise gridnodes
    for(int i = 0; i < numNodes; ++i)
    {
        Gridnode* gridnode = new Gridnode{i, symbols};
        gridnodes.push_back(gridnode);
    }
    // activate initial node
    gridnodes[activeNode]->activate();
    // setup sender socket
    sender.setup(HOST, PORT);

    for(Gridnode* n : gridnodes)
    {
        n->receiveFont(font);
        gridstate.push_back("+");
    }
}

Gridsheet::~Gridsheet()
{
    // delete nodes in destructor
    for(Gridnode* n : gridnodes)
    {
        delete n;
    }
    cout << "nodes deleted" << endl;
}

void Gridsheet::draw()
{

    // draw nodes of grid
    for(int i = 0; i < cols; ++i)
    {
        for(int j = 0; j < rows; ++j)
        {
            //ofSetColor(20);
            float wspace = (width/cols)*i + cols/2;
            float hspace = (height/rows)*j + rows/2;
            //ofDrawEllipse(wspace, hspace, 4, 4);
            int index = i + j * cols;
            gridnodes[index]->draw(wspace, hspace);

        }
    }
}

// This method defines the arrow key interaction allowing the
// navigate the grid
void Gridsheet::navigate(int key)
{
    if(key==57356) // left
    {
       //cout << "left" << endl;
       activeNode--;
    }
    if(key==57358) // right
    {
       //cout << "right" << endl;
       activeNode++;
    }
    if(key==57357) // up
    {
       //cout << "up" << endl;
       activeNode -= cols;
    }
    if(key==57359) // down
    {
       //cout << "down" << endl;
       activeNode += cols;
    }
    // BACKSPACE
    if(key==8)
    {
        activeNode--;
        gridnodes[activeNode]->changesymbol('+');
    }
    if(key==13)
    {
        ofxOscMessage message0;
        message0 = gridnodes[activeNode]->returnMessage();
        sender.sendMessage(message0, false);
    }
//    cout << key << endl;
    if(key!=57359 && key!=57357 && key!=57358 && key!=57356 && key !=8)
    {
        gridnodes[activeNode]->changesymbol(key);
        activeNode++;
        //cout << key << endl;
    }

    // print gridstate
//    if(key==32)
//    {
//        for(int i = 0; i < gridstate.size(); ++i)
//        {
//            cout << gridstate[i];
//        }
//        cout << ' ' << endl;
//    }
}


void Gridsheet::update()
{

    for(int i = 0; i < numNodes; ++i)
    {
        // updates the active node so it can check whether it is active
        gridnodes[i]->update(activeNode);
        gridstate[i] = gridnodes[i]->getsymboli();
    }
    // run interpreter updating it with latest gridstates
    interpreter.update(gridstate);
}

vector<vector<int>> Gridsheet::getPatterns()
{
    return interpreter.getPatterns();
}

vector<vector<int>> Gridsheet::getPatternFunctions()
{
    return interpreter.getPatternFunctions();
}

