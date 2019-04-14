#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "ofMain.h"
#include "gridnode.h"
#include "gridsheet.h"

enum class EscapeModes {CURL, PAREN};

class Interpreter
{
public:
    Interpreter();
    ~Interpreter();
    void parser();
    void update();
private:
    vector<string> gridstate;
    EscapeModes current;

};

#endif // INTERPRETER_H
