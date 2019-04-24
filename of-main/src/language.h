#ifndef LANGUAGE_H
#define LANGUAGE_H
#include "ofMain.h"

class Language
{
public:
    Language();
    ~Language();
    vector<int> setSampleSequence(vector<int>);
    vector<int> randomPattern(int sample);
};

#endif // LANGUAGE_H
