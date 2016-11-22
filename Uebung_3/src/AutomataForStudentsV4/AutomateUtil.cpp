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

    return false;
} // bool AutomateUtil::isMinimalAutomat



