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
 * Answers the question if the given DFA is a minimal one.
 * @param dfa the dfa to check
 * @return true if minimal false otherwise
 */
bool isMinimalAutomat(const DFA *dfa);

int main(int argc, char **args) {
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
    cout << endl << "Is minimal DFA ? " << (isMinimalAutomat(&dfa) ? "true" : "false") << endl;
}

/**
 * Valdiates the given automat if its a minimal one
 * @param dfa the dfa to check
 * @return true if minimal false otherwise.
 */
bool isMinimalAutomat(const DFA *dfa) {
    if (dfa == nullptr) {
        throw invalid_argument("DFA must not be null");
    } // if

    // transform transition table
    // http://www.fh-wedel.de/~si/vorlesungen/cb/LexikalischeAnalyse/DFAmin.html
    // https://www.youtube.com/watch?v=mW6b9FgG768#t=388.966624
    // https://www.youtube.com/watch?v=rw4vSM2mxrQ#t=32.584981

    // init transformed table
    AutomateUtil::TableEntry transformed[STATES][STATES];
    for (const auto &fromState: dfa->S) {
        for (const auto &toState: dfa->S) {
            if (fromState == toState) {
                transformed[fromState][toState] = EQUIVALENT_ENTRY;
                break;
            } else if ((dfa->F.contains(fromState) && !dfa->F.contains(toState))
                       || (!dfa->F.contains(fromState) && dfa->F.contains(toState))) {
                transformed[fromState][toState] = NOT_EQUIVALENT_ENTRY;
                transformed[toState][fromState] = NOT_EQUIVALENT_ENTRY;
            } else {
                transformed[fromState][toState] = UNDEF_ENTRY;
                transformed[toState][fromState] = UNDEF_ENTRY;
            };
        } // for
    } // for

    int undefCount = -1;
    int oldUndefCount = undefCount;
    bool run = true;
    while (run) {
        for (const auto &fromState : dfa->S) {
            for (const auto &toState : dfa->S) {
                // ignore mirror side and mark self reference
                if (fromState == toState) {
                    break;
                }

                // skip if already marked or ignored
                if ((transformed[fromState][toState] != UNDEF_ENTRY)) {
                    continue;
                }
                    // determine if equivalent
                else {
                    for (const auto &symbol: dfa->V) {
                        State fromDestState = dfa->delta[fromState][symbol];
                        State toDestState = dfa->delta[toState][symbol];
                        // non existing transition on from or to
                        if (transformed[fromDestState][toDestState] == NOT_EQUIVALENT_ENTRY) {
                            transformed[fromState][toState] = NOT_EQUIVALENT_ENTRY;
                            transformed[toState][fromState] = NOT_EQUIVALENT_ENTRY;
                            break;
                        }
                    }
                }

                if (transformed[fromState][toState] == UNDEF_ENTRY) {
                    undefCount = undefCount + 1;
                }
            }
        }

        run = false;
        cout << endl;
        for (const auto &fromState: dfa->S) {
            cout << endl;
            for (const auto &toState: dfa->S) {
                AutomateUtil::TableEntry entry = transformed[fromState][toState];
                cout << entry << " ";
                if (fromState == toState) {
                    break;
                }
                // rerun only if changes have been detected
                if ((entry == UNDEF_ENTRY) && ((oldUndefCount == -1) || (undefCount < oldUndefCount))) {
                    run = true;
                }
            } // for
        } // for

        oldUndefCount = undefCount;
        undefCount = 0;
    } // while

    return oldUndefCount == 0;
} // bool isMinimalAutomat

// end of DFATest.cpp
//======================================================================
