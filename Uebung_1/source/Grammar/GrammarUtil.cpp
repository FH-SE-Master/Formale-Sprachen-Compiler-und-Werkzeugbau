//
// Created by Thomas on 10/15/16.
//

#include <cstdarg>
#include <iostream>
#include <queue>

#include "GrammarUtil.hpp"

namespace GrammarUtil {
/**
     * Transforms the the sequences of the given rule of an deletable NTSymbol.
     * @param thr rule of an deletable NTSymbol to be transformed
     * @return the set of trqansformed sequences. Not of type SequenceSet because SeuqenceSet deletes its items
     * @throw invalid_argument if the given SequenceSet is a nullptr
     */
    set<Sequence *> *transformSequence(SequenceSet *oldSequences);

    Grammar *epsilonFreeGrammarOf(Grammar *grammar) {
        if (grammar == nullptr) {
            throw invalid_argument("invalid nullptr for grammar");
        } // if

        // identify deletable rules on given grammar
        grammar->identifyDeletableNTs();

        // return grammar if already epsilon free
        if (grammar->isEpsilonFree()) {
            return grammar;
        } // if

        // Create new root which contains the alternative with the epsilon an the old root.
        NTSymbol *root = SymbolPool::getInstance()->ntSymbol(grammar->root->name + "'");
        Grammar *epsilonFreeGrammar = new Grammar(grammar->root);
        epsilonFreeGrammar->addRule(root, 2, new Sequence(), new Sequence(grammar->root));

        // iterate over all rules
        for (auto &rule: grammar->rules) {
            if (grammar->isDeletable(rule.first)) { // transform sequence if NTSymbol is deletable
                set<Sequence *> *newSequences = transformSequence(&rule.second);
                for (auto newSeq : *newSequences) {
                    epsilonFreeGrammar->addRule(rule.first, 1, *newSeq);
                } // for

                // delete set (not items !!)
                delete (newSequences);
            } else { // copy sequence if NTSymbol is not deletable
                for (auto oldSeq : rule.second) {
                    epsilonFreeGrammar->addRule(rule.first, 1, new Sequence(*oldSeq));
                } // for
            } // if
        } // for

        return epsilonFreeGrammar;
    } // Grammar::epsilonFreeGrammarOf

    /**
     * Transforms the the sequences of the given rule of an deletable NTSymbol.
     * @param oldSequences the sequences of the old rule
     * @return the tranformed rule
     * @throw invalid_argument if the given set is a nullptr
     */
    set<Sequence *> *transformSequence(SequenceSet *oldSequences) {
        if (oldSequences == nullptr) {
            throw invalid_argument("Given oldSequences set is a nullptr.");
        }

        // use ordinary set and not SequenceSet because SequenceSet deletes its items
        set<Sequence *> *transformedSet = new set<Sequence *>();

        // iterate over all oldSequences
        for (Sequence *seq: *oldSequences) {
            int cursorIdx = -1;
            int length = seq->length();
            int innerCursorIdx = 0;

            // epsilon not part of transformed
            if (seq->isEpsilon()) {
                continue;
            } // if

            // original sequence is always part of transformed
            Sequence *originalSequence = new Sequence(*seq);
            if (!transformedSet->insert(originalSequence).second) {
                delete originalSequence;
            } // if

            // if only terminals, then no transformation needed
            if (seq->hasTerminalsOnly()) {
                continue;
            } // if

            // add sequence with first NT if NTSymbols only, otherwise get lost by following algorithm
            if (seq->hasNonTerminalsOnly()) {
                for (auto it = seq->begin(); it != seq->end(); it++) {
                    Symbol *symbol = seq->symbolAt(it);
                    if (symbol->isNT()) {
                        Sequence *firstSymbolSequence = new Sequence(symbol);
                        if (!transformedSet->insert(firstSymbolSequence).second) {
                            delete firstSymbolSequence;
                        } // if
                        break;
                    } // if

                    // move cursor by one which will stay one symbol before added one
                    cursorIdx++;
                } // for
            }

            // iterate as long the cursorIdx cursor can be moved
            while (cursorIdx != (length - 1)) {
                // iterate as long as inner cursor can be moved
                while (innerCursorIdx < length) {
                    Sequence *tmpSequence = new Sequence();
                    int itIdx = -1;
                    // iterate over each symbol in the sequence
                    for (auto it = seq->begin(); it != seq->end(); it++) {
                        itIdx++;
                        Symbol *symbol = seq->symbolAt(it);

                        // do not escape leading TSymbols
                        if (symbol->isT()) {
                            tmpSequence->appendSymbol(symbol);
                            // move inner cursor if it stands on TSymbol
                            if (itIdx == innerCursorIdx) {
                                innerCursorIdx++;
                            } // if
                            continue;
                        } //if

                        // ignore all before cursor and inner cursor position
                        if ((itIdx > cursorIdx) && (itIdx != innerCursorIdx)) {
                            tmpSequence->appendSymbol(symbol);
                        } // if
                    } // for

                    // move inner cursor
                    innerCursorIdx++;

                    // insert and delete sequence if insert failed
                    if ((tmpSequence->empty()) || (!transformedSet->insert(tmpSequence).second)) {
                        delete tmpSequence;
                    } // if
                } // while

                // move cursors
                cursorIdx++;
                innerCursorIdx = cursorIdx + 1;

            } // while
        } // for

        return transformedSet;
    }
}