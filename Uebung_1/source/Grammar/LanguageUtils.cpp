//
// Created by Thomas on 10/26/16.
//
#ifndef _INCLUDES_LANGUAGE_UTILS_CPP
#define _INCLUDES_LANGUAGE_UTILS_CPP

#include <cstdarg>
#include <iostream>
#include <queue>
#include "LanguageUtils.hpp"

#endif

namespace LanguageUtil {
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
    set<Sequence *> *
    generateLanguageRecursive(Grammar *_grammar, set<Sequence *> *current, int _maxLength, int _curLength);


    Language *generateLanguage(Grammar *_grammar, int _maxLength) {
        if (_grammar == nullptr) {
            throw invalid_argument("GrammarUtil::Language *generateLanguage: invalid nullptr for grammar");
        } // if
        if (_maxLength <= 0) {
            throw invalid_argument("GrammarUtil::Language *generateLanguage: maxLength must be greater than zero");
        } // if

        set<Sequence *> *result = generateLanguageRecursive(_grammar, nullptr, _maxLength, -1);
        Language *language = new Language(_grammar);
        for (Sequence *sequence : *result) {
            language->appendSentence(sequence);
        }
        return language;
    } // Language *generateLanguage

    set<Sequence *> *
    generateLanguageRecursive(Grammar *_grammar, set<Sequence *> *current, int _maxLength, int _curLength) {
        set<Sequence *> generatedSentences;
        // initialize
        if (current == nullptr) {
            current = new set<Sequence *>();
            // Empty sentence always part of language
            current->insert(new Sequence());
            for (auto it = _grammar->vT.begin(); it != _grammar->vT.end(); it++) {
                current->insert(new Sequence(SymbolPool::getInstance()->tSymbol((*it)->name)));
            } // for
        }
            // Generate sentences
        else {
            for (auto it = _grammar->vT.begin(); it != _grammar->vT.end(); it++) {
                for (auto sentenceIt = current->begin(); sentenceIt != current->end(); sentenceIt++) {
                    if ((*sentenceIt)->length() == _curLength) {
                        Sequence *sentence = new Sequence(**sentenceIt);
                        sentence->appendSymbol(*it);
                        if (!generatedSentences.insert(sentence).second) {
                            cout << "declined: " << *sentence << endl;
                            delete (sentence);
                        }
                    }
                } // for
            } // for
        } // if

        current->insert(generatedSentences.begin(), generatedSentences.end());
        // anchor
        if (_maxLength == _curLength) {
            return current;
        } // if

        return generateLanguageRecursive(_grammar, current, _maxLength, (_curLength + 1));
    } // Language *generateLanguageRecursive
}
