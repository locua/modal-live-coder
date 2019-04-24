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
       if(gridstate[i]=="r")
       {
           // check if there is any random instances
           if(randInstances.size() > 0)
           {
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
                       /* push vector of ints into vector
                       // the first int is its id and index in the gridstate
                       // the second int is its first argument */
                       unsigned int id = i;
                       unsigned int relatedSample = stoi(gridstate[i+1]);
                       vector<int> randomFunction = {id, relatedSample};
                       randInstances.push_back(randomFunction);
                       //cout << "randInstances size: " << randInstances.size() << endl;
                    }
                }
           } else {
               // push first random function
               if(this->isInteger(gridstate[i+1]))
               {
                  /* push vector of ints into vector
                  // the first int is its id and index in the gridstate
                  // the second int is its first argument */
                  unsigned int id = i;
                  unsigned int relatedSample = stoi(gridstate[i+1]);
                  vector<int> randomFunction = {id, relatedSample};
                  randInstances.push_back(randomFunction);
                  //cout << "randInstances size: " << randInstances.size() << endl;
               }
           }

       }
       //cout << randInstances.size() << endl;
       // detect g
       if(gridstate[i]=="g")
       {
           gTicker.push_back(1);
       }
   }
   // loop over rand instance array and
   for(int i = 0; i < randInstances.size(); i ++)
   {
       // execute random function of the language
       EscapeMode emtemp = EscapeMode::RAND;
       vector<int> pattern = lang.randomPattern(randInstances[i][1]);

       // logic to check if previous instances of r have been removed
       if(gridstate[randInstances[i][0]] != "r")
       {
           // deletes removed r instance from array
            randInstances.erase(randInstances.begin() + i);
            //cout << "rand instance " << randIntances.begin() + i << " has been deleted" << endl;
       }

   }
   // loop over g instance array
   for(int i = 0; i < gTicker.size(); i ++)
   {
       cout << "number " << i << " g is happening" << endl;
   }

}

void LangInterpreter::update(vector<string> _gridstate)
{
    // updates gridstate with latest value of gridstate
    gridstate = _gridstate;
    // runs parse loop
    this->parser();
}

// Checks if string is an integer
inline bool LangInterpreter::isInteger(const string& s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
   char * p;
   strtol(s.c_str(), &p, 10);
   return (*p == 0);
}
