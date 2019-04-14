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

void LangInterpreter::update()
{
    if(current==EscapeMode::CURL)
    {
        cout << "curl detected" << endl;
    }
}
