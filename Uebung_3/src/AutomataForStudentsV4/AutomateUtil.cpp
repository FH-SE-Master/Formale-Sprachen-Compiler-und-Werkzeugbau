//
// Created by Thomas on 11/21/16.
//
#include "AutomateUtil.hpp"
#include <stdexcept>

using namespace std;

NFA *AutomateUtil::nfaOfGrammar(const Grammar *grammar) {
    if ((grammar == nullptr) || (!grammar->isRegular())) {
        throw invalid_argument("Grammar must be regular and not null");
    } // if

    NFA *nfa = new NFA();

    // build state map = left side of grammar
    StateSet stateSet;
    for (const auto &item : grammar->vNt) {
        stateSet.insert(item->name[0]);
    } // for
    nfa->S = stateSet;

    // build symbol set = TSymbols
    SymbolSet symbolSet;
    for (const auto &item : grammar->vT) {
        symbolSet.insert(item->name[0]);
    } // for
    nfa->V = symbolSet;

    // build transitions
    for (Grammar::Rule rule : grammar->rules) {
        for (const auto &sequence : rule.second) {
            // add transition to itself which is terminal state too if only TSymbol
            if (sequence->size() == 1) {
                nfa->delta[rule.first->name[0]][((*(sequence->begin()))->name[0])].insert(
                        rule.first->name[0]);
            }
                // add transition to NTSymbol via TSymbol
            else {
                nfa->delta[rule.first->name[0]][((*(sequence->begin()))->name[0])].insert(
                        ((*(--sequence->end()))->name[0]));
            } // if
        } // for
    } // for

    return nfa;
} // NFA *AutomateUtil::nfaOfGrammar

Grammar *AutomateUtil::grammarOfNfa(const NFA *nfa) {
    if (nfa == nullptr) {
        throw invalid_argument("nfa  must not be null");
    } // if

    SymbolPool *sp = SymbolPool::getInstance();
    Grammar *grammar = nullptr;

    // iterator over all possible states
    for (const auto &state : nfa->S) {
        NTSymbol *ntSymbol = sp->ntSymbol(string(1, state));
        // init grammar on root symbol
        if (grammar == nullptr) {
            grammar = new Grammar(ntSymbol);
        }

        // iterate over all symbols
        for (const auto &symbol: nfa->V) {
            // for all destination states for the source state and current symbol
            for (const auto &destinationState: nfa->delta[state][symbol]) {
                Sequence *sequence = new Sequence();
                sequence->append(sp->tSymbol(string(1, symbol)));
                sequence->append(sp->ntSymbol(string(1, destinationState)));
                // add rule to grammar
                grammar->addRule(ntSymbol, sequence);
            } // for
        } // for
    } // for

    return grammar;
} // Grammra *AutomateUtil::grammarOfNfa

bool AutomateUtil::isMinimalAutomat(const DFA *dfa) {
    if (dfa == nullptr) {
        throw invalid_argument("DFA must not be null");
    } // if

    // transform transition table
    // http://www.fh-wedel.de/~si/vorlesungen/cb/LexikalischeAnalyse/DFAmin.html
    // https://www.youtube.com/watch?v=mW6b9FgG768#t=388.966624

    // init transformed table
    TableEntry transformed[STATES][STATES];
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
                TableEntry entry = transformed[fromState][toState];
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

    return false;
} // bool AutomateUtil::isMinimalAutomat



