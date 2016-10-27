//
// Created by Thomas on 10/15/16.
//

#ifndef _INCLUDES_GRAMMAR_UTIL_CPP
#define _INCLUDES_GRAMMAR_UTIL_CPP

#include <cstdarg>
#include <iostream>
#include <queue>

#include "GrammarUtil.hpp"

#endif

namespace GrammarUtil {
    /**
     * Transforms the the sequences of the given rule of an deletable NTSymbol.
     *
     * @param thr rule of an deletable NTSymbol to be transformed
     * @return the set of trqansformed sequences. Not of type SequenceSet because SeuqenceSet deletes its items
     * @throw invalid_argument if the given SequenceSet is a nullptr
     */
    set<Sequence *> *transformSequence(const SequenceSet *_oldSequences);

    void deriveRecursive(const Grammar *_grammar, Sequence _currentSentence, set<Sequence *> *_currentSentences,
                         int maxLength);

    Grammar *epsilonFreeGrammarOf(const Grammar *_grammar) {
        if (_grammar == nullptr) {
            throw invalid_argument("invalid nullptr for _grammar");
        } // if

        // identify deletable rules on given _grammar
        _grammar->identifyDeletableNTs();

        // return _grammar if already epsilon free
        if (_grammar->isEpsilonFree()) {
            return nullptr;
        } // if

        // Create new root which contains the alternative with the epsilon an the old root.
        NTSymbol *root = SymbolPool::getInstance()->ntSymbol(_grammar->root->name + "'");
        Grammar *epsilonFreeGrammar = new Grammar(_grammar->root);
        epsilonFreeGrammar->addRule(root, 2, new Sequence(), new Sequence(_grammar->root));

        // iterate over all rules
        for (auto &rule: _grammar->rules) {
            if (_grammar->isDeletable(rule.first)) { // transform sequence if NTSymbol is deletable
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
     * @param _oldSequences the sequences of the old rule
     * @return the tranformed rule
     * @throw invalid_argument if the given set is a nullptr
     */
    set<Sequence *> *transformSequence(const SequenceSet *_oldSequences) {
        if (_oldSequences == nullptr) {
            throw invalid_argument("Given _oldSequences set is a nullptr.");
        }

        // use ordinary set and not SequenceSet because SequenceSet deletes its items
        set<Sequence *> *transformedSet = new set<Sequence *>();

        // iterate over all _oldSequences
        for (Sequence *seq: *_oldSequences) {
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
            // TODO: For loop should not be necessary
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

    GrammarMetadata collectGrammarMetadata(const Grammar *_grammar) {
        if (_grammar == nullptr) {
            throw invalid_argument("Language::reduceToNTSymbol: invalid nullptr for _grammar");
        } // if
        GrammarMetadata result;
        result.minLength = -1;
        for (auto ruleIt = _grammar->rules.begin(); ruleIt != _grammar->rules.end(); ruleIt++) {
            for (auto sequenceIt = ruleIt->second.begin(); sequenceIt != ruleIt->second.end(); sequenceIt++) {
                const int curLength = (*sequenceIt)->length();
                if (result.maxLength < curLength) {
                    result.maxLength = curLength;
                }
                if ((result.minLength == -1)
                    || (result.minLength > curLength)) {
                    result.minLength = curLength;
                }
            } // for
        } // for

        return result;
    } // GrammarMetadata collectGrammarMetadata

    set<NTSymbol *> findNTSymbolSForSequence(const Grammar *_grammar, Sequence *_sequence) {
        if (_grammar == nullptr) {
            throw invalid_argument("Language::reduceToNTSymbol: invalid nullptr for grammar");
        } // if
        if (_sequence == nullptr) {
            throw invalid_argument("Language::reduceToNTSymbol: invalid nullptr for sentence");
        } // if

        set<NTSymbol *> result;
        for (auto ruleIt = _grammar->rules.begin(); ruleIt != _grammar->rules.end(); ruleIt++) {
            if (ruleIt->second.find(_sequence) != ruleIt->second.end()) {
                result.insert(ruleIt->first);
            } // if
        } // for

        return result;
    } // Grammar::Rule findRuleForSequence


    Symbol *reduce(const Grammar *grammar, Sequence _sentence) {
        Symbol *result = nullptr;
        if ((_sentence.length() == 1) && ((*_sentence.begin())->isNT())) {
            result = *_sentence.begin();
        }
        for (int i = 0; i < _sentence.length(); ++i) {
            for (int j = i; j < _sentence.length(); ++j) {
                Sequence sequence;
                sequence.insert(sequence.begin(), _sentence.begin() + i, _sentence.begin() + j + 1);

                set<NTSymbol *> ntSymbols = findNTSymbolSForSequence(grammar, &sequence);
                if (!ntSymbols.empty()) {
                    for (auto foundSymbol: ntSymbols) {
                        Sequence tmp(_sentence);
                        tmp.erase(tmp.begin() + i, tmp.begin() + j + 1);
                        tmp.insert(tmp.begin() + i, foundSymbol);
                        result = reduce(grammar, tmp);
                    }
                }
            }
        }

        return result;
    }

    set<Sequence *> derive(const Grammar *grammar, Sequence sentence) {
        set<Sequence *> sentences;
    }

    void deriveRecursive(const Grammar *_grammar,
                         NTSymbol *_currentSymbol,
                         Sequence _currentSentence,
                         set<Sequence *> sentences,
                         int maxLength) {
        if (_currentSentence.hasTerminalsOnly()) {
            sentences.insert(&_currentSentence);
            return;
        } else if (_currentSentence.length() >= maxLength) {
            return;
        }

        auto rule = _grammar->rules.find(_currentSymbol);
        if (rule != _grammar->rules.end()) {

        }


    }
}