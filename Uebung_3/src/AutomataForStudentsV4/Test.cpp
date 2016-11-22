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

/**
 * This function tests the DFA automat for the given automat.
 */
void test_dfa() {
    DFA dfa;

    dfa.S = StateSet("{B,R}");
    dfa.V = SymbolSet("{b,z}");
    dfa.delta['B']['b'] = 'R';
    dfa.delta['R']['b'] = 'R';
    dfa.delta['R']['z'] = 'R';
    dfa.s1 = 'B';
    dfa.F = StateSet("{R}");

    cout << "Test DFA. S={B,R}, V={b,z}" << endl;

    string tape = "bbbb";
    // current state B (=start), no visited states
    cout << "Valid: dfa.s1=B, dfa.F={R}, tape=[b]" << endl
         << "tape='" << tape << "'" << endl
         << "accepted: " << ((dfa.accepts(tape.data())) ? "true" : "false") << endl
         << "---------------------------------------------------" << endl;

    tape = "bzzz";
    // current state B (=start), no visited states
    cout << "Valid: dfa.s1=B, dfa.F={R,R,R}, tape=[bzzz]" << endl
         << "tape='" << tape << "'" << endl
         << "accepted: " << ((dfa.accepts(tape.data())) ? "true" : "false") << endl
         << "---------------------------------------------------" << endl;

    tape = "zbbb";
    // current state B (=start), no visited states
    cout << "Invalid: dfa.s1=B, dfa.F={R,R,R}, tape=[zzzzzzzzzzzzz]" << endl
         << "tape='" << tape << "'" << endl
         << "accepted: " << ((dfa.accepts(tape.data())) ? "true" : "false") << endl
         << "---------------------------------------------------" << endl;
}

void test_mealy() {
    Mealy mealy([](char symbol) -> char {
        switch (symbol) {
            case 'b':
                return 'c';
            case 'z':
                return 'd';
            default:
                return symbol;
        }
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


}

void test_dfa_rgb() {
    NFA nfa;
    AutomateUtil::Clock clock;

    nfa.S = StateSet("{S,A,B,C,R}");
    nfa.V = SymbolSet("{a,b,c}");

    nfa.delta['S']['a'] = StateSet("{S,A}");
    nfa.delta['S']['b'] = StateSet("{S,B}");
    nfa.delta['S']['c'] = StateSet("{S,C}");

    nfa.delta['A']['a'] = StateSet("{A,R}");
    nfa.delta['A']['b'] = StateSet("{A}");
    nfa.delta['A']['c'] = StateSet("{A}");

    nfa.delta['B']['a'] = StateSet("{B,R}");
    nfa.delta['B']['b'] = StateSet("{B}");
    nfa.delta['B']['c'] = StateSet("{B}");

    nfa.delta['C']['a'] = StateSet("{C,R}");
    nfa.delta['C']['b'] = StateSet("{C}");
    nfa.delta['C']['c'] = StateSet("{C}");

    nfa.s1 = 'S';
    nfa.F = StateSet("{R}");

    cout << "Test NFA RGB. S={S,A,B,C,R}, V={a,b,c}" << endl;

    string tape = "aaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbcccccccccccccccccccccccccca";
    tape = tape + "ccccccccccccccccccccccccccccccbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    tape = tape + "ccccccccccccccccccccccccccccccbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    tape = tape + "ccccccccccccccccccccccccccccccbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    tape = tape + "ccccccccccccccccccccccccccccccbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    tape = tape + "ccccccccccccccccccccccccccccccbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    tape = tape + "aaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbcccccccccccccccccccccccccca";
    // current state B (=start), no visited states
    cout << "Valid: nfa.s1=S, nfa.F={R}, tape=[aaabbbcccaba]" << endl
         << "tape='" << tape << "'" << endl;
    clock.startMeasure();
    cout << "accepts() : " << ((nfa.accepts(tape.data())) ? "true" : "false") << endl;
    clock.endMeasure();
    clock.startMeasure();
    cout << "accepts2(): " << ((nfa.accepts2(tape.data())) ? "true" : "false") << endl;
    clock.endMeasure();
    cout << "---------------------------------------------------" << endl;

    tape = "abc";
    // current state B (=start), no visited states
    cout << "Valid: nfa.s1=S, nfa.F={R}, tape=[aaabbbcccaba]" << endl
         << "tape='" << tape << "'" << endl;
    clock.startMeasure();
    cout << "accepts() : " << ((nfa.accepts(tape.data())) ? "true" : "false") << endl;
    clock.endMeasure();
    clock.startMeasure();
    cout << "accepts2(): " << ((nfa.accepts2(tape.data())) ? "true" : "false") << endl;
    clock.endMeasure();
    cout << "---------------------------------------------------" << endl;

    // Calculate deterministic automat
    DFA dfa = nfa.dfaOf();
    dfa.generateGraphVizFile("2c-automat.gv");
    DFA minimizedDfa = dfa.minimalDfaOf();
    minimizedDfa.generateGraphVizFile("2c-minimized-automat.gv");
    cout << "Is minimal DFA ? " << (AutomateUtil::isMinimalAutomat(&dfa) ? "true" : "false") << endl;
}

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

    cout << "test_dfa()" << endl;
    test_dfa();

    cout << "test_mealy()" << endl;
    test_mealy();

    cout << "test_dfa_rgb()" << endl;
    test_dfa_rgb();

    delete g;
    delete fromNfa;
    delete nfa;
    delete sp;
}

// end of DFATest.cpp
//======================================================================
