#include "langinterpreter.h"

LangInterpreter::LangInterpreter()
{
    cout << "interpreter created" << endl;
}

LangInterpreter::~LangInterpreter()
{

}

void LangInterpreter::parser()
{
   for(int i = 0; i < gridstate.size(); i ++)
   {
       if(gridstate[i]=="{")
       {
          current = EscapeMode::CURL;
       }
   }
}

void LangInterpreter::update(vector<string> _gridstate)
{
    if(current==EscapeMode::CURL)
    {
        cout << "curl detected" << endl;
    }
    gridstate = _gridstate;
    this->parser();
}
