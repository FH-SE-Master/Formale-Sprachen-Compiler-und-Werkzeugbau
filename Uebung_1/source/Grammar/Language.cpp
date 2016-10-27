// Created by Thomas on 10/16/16.
//

#ifndef _INCLUDES_LANGUAGE_CPP
#define _INCLUDES_LANGUAGE_CPP

#include <cstdarg>
#include "GrammarUtil.hpp"
#include "Language.hpp"

#include <iostream>
#include <stdexcept>

#endif

using namespace std;

//region Constructors and Destructors
Language::Language(const Grammar *_grammar) {
    if (_grammar == nullptr) {
        throw invalid_argument("Language::Language: invalid nullptr for grammar");
    } // if
    this->grammar = _grammar;
} // Language::Language

Language::Language(const Language &ss) : Base(ss), ObjectCounter<Language>() {
    // nothing left to do
} // Language::Language

Language::~Language() {
    for (Sequence *sequence: *this) {
        delete (sequence);
    } // for
} // Language::~Language
//endregion

//region Public Methods
bool Language::appendSentence(Sequence *_sentence) {
    if (_sentence == nullptr) {
        throw invalid_argument("Language::appendSentence: invalid nullptr for _sentence");
    } // if
    return (hasSentence(_sentence)) ? insert(_sentence).second : false;
} // Language::appendSentence

bool Language::hasSentence(Sequence *_sentence) {
    if (_sentence == nullptr) {
        throw invalid_argument("Language::hasSentence: invalid nullptr for sequence");
    } // if

    Symbol *ntSymbol = GrammarUtil::reduce(this->grammar, *_sentence);

    return ((ntSymbol != nullptr) && (this->grammar->root->name == ntSymbol->name));
} // Language::hasSentence
//endregion

//region Other stuff
bool LessSequenceComparator::operator()(const Sequence *seq1,
                                        const Sequence *seq2) const {
    return seq1->length() <= seq2->length();
} // LessSequenceComparator::operator()

std::ostream &operator<<(std::ostream &os, const Language &language) {
    cout << "Language contained sentences:" << endl;
    for (const Sequence *sentence: language) {
        cout << *sentence << endl;
    } // for
    return os;
} // operator<<
//endregion


