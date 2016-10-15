//
// Created by Thomas on 10/15/16.
//

#include <cstdarg>
#include <iostream>
#include <queue>

#include "GrammarUtil.hpp"

namespace GrammarUtil {

    /**
     * Generates a epsilon free grammar of the this grammar.
     * @param grammar the grammar to transform to epsilon free grammar
     * @param symbolPool the pool to generate symbols from
     * @return the transformed epsilon free grammar, or the given grammar if already epsilon free
     * @throw invalid_argument if an parameter is null
     */
    Grammar *epsilonFreeGrammarOf(Grammar *grammar, SymbolPoolPtr symbolPool) {
        if (grammar == nullptr) {
            throw invalid_argument("invalid nullptr for grammar");
        } // if
        if (symbolPool == nullptr) {
            throw invalid_argument("invalid nullptr for symbolPool");
        } // if

        // identify deletable rules on given grammar
        grammar->identifyDeletableNTs();

        // return grammar if already epsilon free
        if (grammar->isEpsilonFree()) {
            return grammar;
        } // if

        // Create new root which contains the alternative with the epsilon an the old root
        NTSymbol *root = symbolPool->ntSymbol("S'");
        NTSymbol *epsilonFreeRoot = symbolPool->ntSymbol("S");
        TSymbol *epsilon = symbolPool->tSymbol("EPS");
        Grammar *epsilonFreeGrammar = new Grammar(root);
        epsilonFreeGrammar->addRule(root, new Sequence(2, root, epsilon, epsilonFreeRoot));

        // iterate over all rules
        for (auto &rule: grammar->rules) {
            if (grammar->isDeletable(rule.first)) {
                cout << "deletable NT: " << rule.first->name << endl;

            } else {
                cout << "not deletable NT: " << rule.first << endl;
            }// if
        } // for

        return epsilonFreeGrammar;
    } // Grammar::epsilonFreeGrammarOf

    /**
     * Transforms the the sequences of the given rule of an deletable NTSymbol.
     * @param thr rule of an deletable NTSymbol to be transformed
     * @return the tranformed rule
     * @throw invalid_argument if the given set is a nullptr
     */
    SequenceSet *TransformRule(SequenceSet *sequences) {
        if (sequences == nullptr) {
            throw invalid_argument("Given sequences set is a nullptr.");
        }
        SequenceSet *tranformedSet = new SequenceSet();

        for (Sequence *seq: *sequences) {
            // epsilon not part of transformed
            if (seq->isEpsilon()) {
                continue;
            } // if

            Sequence *copiedSequence = new Sequence(*seq);

            // original sequence is always part of transformed
            tranformedSet->insert(copiedSequence);

            // if only terminals, then no transformation needed
            if (copiedSequence->hasTerminalsOnly()) {
                continue;
            } // if

            int length = copiedSequence->length();
            int startIdx = -1;
            int curIdx = 0;
            while (startIdx < (copiedSequence->length() - 1)) {
                Sequence *tmpSequence = new Sequence(*copiedSequence);
                int itIdx = -1;
                for (auto it = tmpSequence->begin(); it != tmpSequence->end(); it++) {
                    itIdx++;
                    Symbol *symbol = tmpSequence->symbolAt(it);

                    if (itIdx > startIdx) {
                        // TSymbols cannot be replaced by epsilon
                        if (symbol->isT()) {
                            continue;
                        }
                        // else replace symbols
                        tmpSequence->erase(it);
                        // At first replace all symbols with epsilon = remove
                        if (startIdx >= 0) {
                            break;
                        }
                    } else {
                        // skip NTSymbols
                        if (symbol->isT()) {
                            break;
                        }
                    }
                } // for
                tranformedSet->insert(tmpSequence);
                startIdx++;
            } // while
        }

        return tranformedSet;
    }
}