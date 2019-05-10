#include "langinterpreter.h"

LangInterpreter::LangInterpreter()
{
    cout << "interpreter constructed" << endl;
}

LangInterpreter::~LangInterpreter()
{
    cout << "interpreter destroyed" << endl;
}

void LangInterpreter::parser()
{
   // initialise empty array for storing instances of an 'r' function
   //vector<int> randInstances{};
   vector<int> gTicker{};
   // main parse loop
   for(int i = 0; i < gridstate.size(); i ++)
   {
       /* This is a basic parsing setup to check for and instance of the r
        * function and checking to see if it has an argument */
       if(gridstate[i]=="r" && gridstate[i+3]=="r")
       {

           // check if there is any random instances
           if(randInstances.size() > 0)
           {
                // loop through array to check this random function has not already
               // been added
                int rcounter = 0;
                for(int j = 0; j < randInstances.size(); j ++)
                {
                    // check r has not already been added
                    if(randInstances[j][0] == i)
                    {
                        rcounter ++;
                    }
                }
                if(rcounter==0)
                {
                    if(this->isInteger(gridstate[i+1]))
                    {
                       /* Push random function into array
                       /* push vector of ints into vector
                       /* the first int is its id and index in the gridstate
                       /* the second int is its first argument */
                       if(this->isInteger(gridstate[i+2])) // is there more than one digit
                       {
                           unsigned int id = i;
                           unsigned int tens = stoi(gridstate[i+1]);
                           unsigned int units = stoi(gridstate[i+2]);
                           unsigned int relatedSample = units + 10*tens;
                           vector<int> randomFunction = {id, relatedSample};
                           vector<int> _pattern = lang.randomPattern();
                           randomFunction.insert(randomFunction.end(), _pattern.begin(), _pattern.end());
                           randInstances.push_back(randomFunction);
                           //cout << "randInstances size: " << randInstances.size() << endl;
                       } else { // only one digit
                           unsigned int id = i;
                           unsigned int relatedSample = stoi(gridstate[i+1]);
                           vector<int> randomFunction = {id, relatedSample};
                           vector<int> _pattern = lang.randomPattern();
                           randomFunction.insert(randomFunction.end(), _pattern.begin(), _pattern.end());
                           randInstances.push_back(randomFunction);
                           //cout << "randInstances size: " << randInstances.size() << endl;
                       }
                    }
                }
           } else {
               // push first random function
               if(this->isInteger(gridstate[i+1]))
               {
                  /* push vector of ints into vector
                  // the first int is its id and index in the gridstate
                  // the second int is its first argument */

                   if(this->isInteger(gridstate[i+2])) // is there more than one digit
                   {
                       unsigned int id = i;
                       unsigned int units = stoi(gridstate[i+1]);
                       unsigned int tens = stoi(gridstate[i+2]);
                       unsigned int relatedSample = units + 10*tens;
                       vector<int> randomFunction = {id, relatedSample};
                       vector<int> _pattern = lang.randomPattern();
                       randomFunction.insert(randomFunction.end(), _pattern.begin(), _pattern.end());
                       randInstances.push_back(randomFunction);
                       //cout << "randInstances size: " << randInstances.size() << endl;
                   } else { // only one digit
                       unsigned int id = i;
                       unsigned int relatedSample = stoi(gridstate[i+1]);
                       vector<int> randomFunction = {id, relatedSample};
                       vector<int> _pattern = lang.randomPattern();
                       randomFunction.insert(randomFunction.end(), _pattern.begin(), _pattern.end());
                       randInstances.push_back(randomFunction);
                       //cout << "randInstances size: " << randInstances.size() << endl;
                   }
               }
           }

       }
       /* Check for Pattern function
        * This function allows you to choose when the sample is banged
        * by defining a pattern of 0's and 1's for the sample to played back in
        */
       if(gridstate[i]=="p")
       {
           if(patternInstances.size()>0)
           {
               // loop through array to check this pattern function has not already
               // been added
               int pcounter = 0;
               for(int j = 0; j < patternInstances.size(); j ++)
               {
                   // check p has not already been added
                   if(patternInstances[j][0] == i)
                   {
                       pcounter ++;
                   }
               }
               if(pcounter==0)
               {
                    // ie a pattern function at this index has not already been added
                    if(gridstate[i+3]=="p")
                    {
                        if(this->isInteger(gridstate[i+1]) && this->isInteger(gridstate[i+2]))
                        {
                            // "we have a pattern function baby"
                            int id = i;
                            int units = stoi(gridstate[i+2]);
                            int tens = stoi(gridstate[i+1]);
                            int sampleId = units +(10*tens);
                            vector<int> patternFunction{id, sampleId};
                            for(int z = 0; z < 16; z++)
                            {
                                if(gridstate[i+4+z]=="p")
                                {
                                    for(int q = 0; q <(i+4+z); q++)
                                    {
                                        if(this->isInteger(gridstate[q])) patternFunction.push_back(stoi(gridstate[q]));
                                    }
                                } else
                                {
                                    patternFunction.push_back(0);
                                }
                            }
                            patternInstances.push_back(patternFunction);
                        }
                    }

               }
           } else {
               /* add first pattern function instance */
               if(gridstate[i+3]=="p")
               {
                   if(this->isInteger(gridstate[i+1]) && this->isInteger(gridstate[i+2]))
                   {
                       int id = i;
                       int units = stoi(gridstate[i+2]);
                       int tens = stoi(gridstate[i+1]);
                       int sampleId = units +(10*tens);

                       for(int z = 0; z < 16; z++)
                       {
                           if(gridstate[i+4+z]=="p")
                           {
                               cout << "third p detected" << endl;
                               vector<int> patternFunction{id, sampleId};
                               for(int q = 0; q <(i+4+z); q++)
                               {
                                   if(this->isInteger(gridstate[q]))
                                   {
                                       patternFunction.push_back(stoi(gridstate[q]));
                                   } else {
                                       patternFunction.push_back(0);
                                   }
                               }
                               patternInstances.push_back(patternFunction);
                           }
                       }
                   }
               }
           }

       }
   }
   // loop over rand instance array and
   for(int i = 0; i < randInstances.size(); i ++)
   {
       // logic to check if previous instances of r have been removed
       if(gridstate[randInstances[i][0]] != "r")
       {
           // deletes removed r instance from array
            randInstances.erase(randInstances.begin() + i);
            //cout << "rand instance " << randIntances.begin() + i << " has been deleted" << endl;
       }
   }
   for(int i = 0; i < patternInstances.size(); i ++)
   {
       // logic to check if previous instances of r have been removed
       if(gridstate[patternInstances[i][0]] != "p" || gridstate[patternInstances[i][0]+3]!="p")
       {
           // deletes removed r instance from array
            patternInstances.erase(patternInstances.begin() + i);
            //cout << "rand instance " << randIntances.begin() + i << " has been deleted" << endl;
       }
   }
}

void LangInterpreter::update(vector<string> _gridstate)
{
    // updates gridstate with latest value of gridstate
    gridstate = _gridstate;
    // runs parse loop
    this->parser();
}

vector<vector<int>> LangInterpreter::getPatterns()
{
    return randInstances;
}
vector<vector<int>> LangInterpreter::getPatternFunctions()
{
    return patternInstances;
}

// Checks if string is an integer
inline bool LangInterpreter::isInteger(const string& s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
   char * p;
   strtol(s.c_str(), &p, 10);
   return (*p == 0);
}
