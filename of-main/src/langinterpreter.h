#ifndef LANGINTERPRETER_H
#define LANGINTERPRETER_H
#include "ofMain.h"

enum class EscapeMode {CURL, PAREN};

class LangInterpreter
{
public:
    LangInterpreter();
    ~LangInterpreter();
    void parser();
    void update();
    EscapeMode current;
};

#endif // LANGINTERPRETER_H
