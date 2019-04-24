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

vector<int> Language::randomPattern(int sample)
{
   int patternlength = 17;
   vector<int> pattern = {sample, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
   for(int i = 1; i < pattern.size(); i ++)
   {
       pattern[i] = round(ofRandom(0, 1));
       //cout << pattern[i];

   }
   return pattern;
}
