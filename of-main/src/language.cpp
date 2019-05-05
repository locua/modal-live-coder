#include "language.h"

Language::Language()
{

}

Language::~Language()
{

}

vector<int> Language::setSampleSequence(vector<int> sequence)
{
    vector<int> sampleSequence = sequence;
    return sampleSequence;
}

vector<int> Language::randomPattern()
{
   //int patternlength = 16;
   vector<int> pattern = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
   for(int i = 0; i < pattern.size(); i ++)
   {
       pattern[i] = round(ofRandom(0, 1));
       //cout << pattern[i];

   }
   return pattern;
}
