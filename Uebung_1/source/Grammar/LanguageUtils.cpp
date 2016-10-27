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

    //region Private Functions Definition
    /**
     * Derives the given grammar recursively to all possible sentences with TSymbols only up to maxLength.
     *
     * @param _grammar the grammar to get sentences up to maxLenth for the language of the grammar
     * @param _currentSentence the current sentence to derive
     * @param sentences the sentences set holding all TSymbols sentences only
     * @param maxLength the maximum length of the sentences
     */
    void deriveRecursive(const Grammar *_grammar, Sequence _currentSentence, set<Sequence *> *sentences,
                         const int maxLength);
    //endregion

    //region Public Functions Implementation
    Language *generateLanguage(Grammar *_grammar, int _maxLength) {
        if (_grammar == nullptr) {
            throw invalid_argument("GrammarUtil::Language *generateLanguage: invalid nullptr for grammar");
        } // if
        if (_maxLength <= 0) {
            throw invalid_argument("GrammarUtil::Language *generateLanguage: maxLength must be greater than zero");
        } // if

        set<Sequence *> result = derive(_grammar, _maxLength);
        Language *language = new Language(_grammar);
        for (Sequence *sequence : result) {
            if (!language->appendSentence(sequence)) {
                delete (sequence);
            } // if
        } // for
        return language;
    } // Language *generateLanguage

    set<Sequence *> derive(const Grammar *_grammar, int maxLength) {
        set<Sequence *> sentences;
        Sequence sentence(_grammar->root);
        deriveRecursive(_grammar, sentence, &sentences, maxLength);
        return sentences;
    } // set<Sequence *> derive
    //endregion

    //region Private Functions Implementation
    void deriveRecursive(const Grammar *_grammar, Sequence _currentSentence, set<Sequence *> *sentences,
                         const int maxLength) {
        // anchor
        if (_currentSentence.hasTerminalsOnly()) {
            if (_currentSentence.length() <= maxLength) {
                sentences->insert(new Sequence(_currentSentence));
            }
            return;
        } else if (_currentSentence.length() > maxLength) {
            return;
        } // if

        for (int i = 0; i < _currentSentence.length(); i++) {
            Symbol *symbol = _currentSentence[i];
            if (symbol->isNT()) {
                auto const rule = _grammar->rules.find((NTSymbol *) symbol);
                if (rule != _grammar->rules.end()) {
                    for (const auto sequence : rule->second) {
                        Sequence newSentence;
                        newSentence.insert(newSentence.begin(), _currentSentence.begin(), _currentSentence.begin() + i);
                        newSentence.insert(newSentence.end(), sequence->begin(), sequence->end());
                        newSentence.insert(newSentence.end(), _currentSentence.begin() + i + 1, _currentSentence.end());
                        deriveRecursive(_grammar, newSentence, sentences, maxLength);
                    } // for
                } // if
            } // if
        } // for
    } // void deriveRecursive
    //endregion
}
