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
     *
     * @param thr rule of an deletable NTSymbol to be transformed
     * @return the set of trqansformed sequences. Not of type SequenceSet because SeuqenceSet deletes its items
     * @throw invalid_argument if the given SequenceSet is a nullptr
     */
    set<Sequence *> *transformSequence(SequenceSet *_oldSequences);

    /**
     * Generates the language with recursion and builds all sentences up to maxLength.
     * This function does not validate the maxLength, the curLength and the the grammar.
     * Make sure the calls are save to this function
     *
     * @param _grammar the grammar to generate sentences for
     * @param _language the language to append generated sentences too
     * @param _maxLength the max length of the to generate sentences
     * @param _curLength the current length of the in the invocation generated sentence length
     * @return the generated language
     */
    Language *generateLanguageRecursive(Grammar *_grammar, Language *_language, int _maxLength, int _curLength);

    Grammar *epsilonFreeGrammarOf(Grammar *_grammar) {
        if (_grammar == nullptr) {
            throw invalid_argument("invalid nullptr for _grammar");
        } // if

        // identify deletable rules on given _grammar
        _grammar->identifyDeletableNTs();

        // return _grammar if already epsilon free
        if (_grammar->isEpsilonFree()) {
            return _grammar;
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
    set<Sequence *> *transformSequence(SequenceSet *_oldSequences) {
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

    Language *generateLanguage(Grammar *_grammar, int _maxLength) {
        if (_grammar == nullptr) {
            throw invalid_argument("GrammarUtil::Language *generateLanguage: invalid nullptr for grammar");
        } // if
        if (_maxLength <= 0) {
            throw invalid_argument("GrammarUtil::Language *generateLanguage: maxLength must be greater than zero");
        } // if

        return generateLanguageRecursive(_grammar, nullptr, _maxLength, -1);
    } // Language *generateLanguage

    Language *generateLanguageRecursive(Grammar *_grammar, Language *_language, int _maxLength, int _curLength) {
        // initialize
        if (_language == nullptr) {
            _language = new Language();
            for (auto it = _grammar->vT.begin(); it != _grammar->vT.end(); it++) {
                _language->appendSentence(new Sequence(SymbolPool::getInstance()->tSymbol((*it)->name)));
            } // for
        }
            // Generate sentences
        else {
            for (auto it = _grammar->vT.begin(); it != _grammar->vT.end(); it++) {
                set<Sequence *> generatedSentences;

                for (auto sentenceIt = _language->begin(); sentenceIt != _language->end(); sentenceIt++) {
                    if ((*sentenceIt)->length() == _curLength) {
                        Sequence *sentence = new Sequence(**sentenceIt);
                        sentence->appendSymbol(SymbolPool::getInstance()->tSymbol((*it)->name));
                        if (!generatedSentences.insert(sentence).second) { ;
                            delete (sentence);
                        }
                    }
                } // for

                for (auto generatedIt = generatedSentences.begin();
                     generatedIt != generatedSentences.end(); generatedIt++) {
                    Sequence *sentence = *generatedIt;
                    // TODO: Add check if valid sentence
                    if (!_language->appendSentence(sentence)) { ;
                        delete (sentence);
                    }
                } // for
            } // for
        } // if

        // anchor
        if (_maxLength == _curLength) {
            return _language;
        } // if

        return generateLanguageRecursive(_grammar, _language, _maxLength, (_curLength + 1));
    } // Language *generateLanguageRecursive
}