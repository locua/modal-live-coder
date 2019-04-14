#include "interpreter.h"

Interpreter::Interpreter()
{

}

Interpreter::~Interpreter()
{

}

void Interpreter::parser()
{
    for(int i = 0; i < gridstate.size(); i ++)
    {
        /* essential parse loop where the grid content is parsed and
         * into relevant pieces that will trigger execution
         * of audio producing code */
        if(gridstate[i]=='{')
        {
            current = EscapeModes::CURL;
        }

    }
}

void Interpreter::update()
{
    this->parser();

    if(current==EscapeModes::CURL)
    {

    }
}
