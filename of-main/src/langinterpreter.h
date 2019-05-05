#ifndef LANGINTERPRETER_H
#define LANGINTERPRETER_H
#include "ofMain.h"
#include "language.h"

enum class EscapeMode {NONE, CURL, PAREN, RAND};

class LangInterpreter
{
public:
    LangInterpreter();
    ~LangInterpreter();
    void parser();
    void update(vector<string> _gridstate);
    vector<EscapeMode> activeModes;
    inline bool isInteger(const string& );
    vector<vector<int>> getPatterns();
private:
    vector<string> gridstate;
    Language lang;
    // vector to store instances of the random function
    // and its relevant attributes
    vector<vector<int>> randInstances{};
    vector<vector<int>> patterns{};
};

#endif // LANGINTERPRETER_H
