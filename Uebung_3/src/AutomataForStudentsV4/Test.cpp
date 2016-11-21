// DFATest.cpp:                                           HDO, 2006-2014
// -----------
// Test program for deterministic finite automata.
//======================================================================

#include <cstdio>  // for getchar only
#include <cstdlib> // for system only

#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

#include "SymbolStuff.h"
#include "StateStuff.h"
#include "FA.h"
#include "DFA.h"
#include "NFA.h"
#include "AutomateUtil.hpp"
#include "Grammar.h"

using namespace std;

int main(int argc, char **args) {

    SymbolPool *sp = SymbolPool::getInstance();
    Grammar *g = new Grammar(
            "G(S):                          \n\
     S -> a R | a M                    \n\
     M -> b | a M                    \n\
     R -> b R | z R     ");

    NFA *nfa = AutomateUtil::nfaOfGrammar(g);
    Grammar *fromNfa = AutomateUtil::grammarOfNfa(nfa);

    cout << *nfa << endl;

    cout << *fromNfa << endl;

    delete g;
    delete fromNfa;
    delete nfa;
    delete sp;
}

// end of DFATest.cpp
//======================================================================
