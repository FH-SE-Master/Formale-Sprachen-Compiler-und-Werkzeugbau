//
// Created by Thomas on 10/16/16.
//
#include "Language.hpp"
#include <cstdarg>

#include <iostream>
#include <stdexcept>

using namespace std;

//region Constructors and Destructors
Language::Language() {
    // nothing to do here
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

bool Language::appendSentence(Sequence *sentence) {
    if (sentence == nullptr) {
        throw invalid_argument("Language::appendSentence: invalid nullptr for sentence");
    } // if
    return insert(sentence).second;
} // Language::appendSentence

bool Language::hasSentence(Sequence *sentence) const {
    if (sentence == nullptr) {
        throw invalid_argument("Language::hasSentence: invalid nullptr for sequence");
    } // if
    return false;
} // Language::hasSentence

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

