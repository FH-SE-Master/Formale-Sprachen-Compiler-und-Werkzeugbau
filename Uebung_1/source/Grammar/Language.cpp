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
} // Sequence::Sequence

Language::~Language() {

}
//endregion

void Language::appendSequence(Sequence *sequence) {

}

Sequence *Language::sequenceAt(set<Sequence *>::iterator it) const {
    return nullptr;
}

bool Language::hasSentence(Sequence *sequence) const {
    return false;
}

