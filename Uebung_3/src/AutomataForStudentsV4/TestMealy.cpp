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
#include "Mealy.hpp"

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
    Mealy mealy([](char symbol) -> char {
        switch (symbol) {
            case 'b':
                return 'c';
            case 'z':
                return 'd';
            default:
                return symbol;
        } // switch
    });

    mealy.S = StateSet("{B,R}");
    mealy.V = SymbolSet("{b,z}");
    mealy.delta['B']['b'] = 'R';
    mealy.delta['R']['b'] = 'R';
    mealy.delta['R']['z'] = 'R';
    mealy.s1 = 'B';
    mealy.F = StateSet("{R}");

    cout << "Test Mealy. S={B,R}, V={b,z}" << endl;

    string tape = "bzbz";
    // current state B (=start), no visited states
    cout << "Valid: mealy.s1=B, mealy.F={R}, tape=[b]" << endl
         << "tape='" << tape << "'" << endl
         << "accepted: " << ((mealy.accepts(tape.data())) ? "true" : "false") << endl
         << "---------------------------------------------------" << endl;
} // int main

// end of DFATest.cpp
//======================================================================
