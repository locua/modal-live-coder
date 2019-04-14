#ifndef LANGINTERPRETER_H
#define LANGINTERPRETER_H
#include "ofMain.h"
#include "language.h"

enum class EscapeMode {NONE, CURL, PAREN};

class LangInterpreter
{
public:
    LangInterpreter();
    ~LangInterpreter();
    void parser();
    void update(vector<string> _gridstate);
    EscapeMode current;
private:
    vector<string> gridstate;
};

#endif // LANGINTERPRETER_H
