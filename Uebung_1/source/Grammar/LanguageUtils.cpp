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
    Language *generateLanguageRecursive(Grammar *_grammar, Language *_language, int _maxLength, int _curLength);


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
        set<Sequence *> generatedSentences;
        // initialize
        if (_language == nullptr) {
            _language = new Language(_grammar);
            // Empty sentence always part of language
            _language->appendSentence(new Sequence());
            for (auto it = _grammar->vT.begin(); it != _grammar->vT.end(); it++) {
                _language->appendSentence(new Sequence(SymbolPool::getInstance()->tSymbol((*it)->name)));
            } // for
        }
            // Generate sentences
        else {
            for (auto it = _grammar->vT.begin(); it != _grammar->vT.end(); it++) {
                for (auto sentenceIt = _language->begin(); sentenceIt != _language->end(); sentenceIt++) {
                    if ((*sentenceIt)->length() == _curLength) {
                        Sequence *sentence = new Sequence(**sentenceIt);
                        sentence->appendSymbol(*it);
                        if (_language->hasSentence(sentence)) {
                            if (generatedSentences.insert(sentence).second) {
                                continue;
                            }
                        }
                        delete (sentence);
                    }
                } // for
            } // for
        } // if

        for (Sequence *sequence : generatedSentences) {
            if (!_language->appendSentence(sequence)) {
                delete (sequence);
            }
        }

        // anchor
        if (_maxLength == _curLength) {
            return _language;
        } // if

        return generateLanguageRecursive(_grammar, _language, _maxLength, (_curLength + 1));
    } // Language *generateLanguageRecursive
}
