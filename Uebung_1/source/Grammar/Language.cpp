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
    return insert(_sentence).second;
} // Language::appendSentence

bool Language::hasSentence(Sequence *_sentence) {
    if (_sentence == nullptr) {
        throw invalid_argument("Language::hasSentence: invalid nullptr for sequence");
    } // if

    Symbol *ntSymbol = nullptr;
    GrammarUtil::GrammarMetadata metadata = GrammarUtil::collectGrammarMetadata(this->grammar);

    Sequence *sequence = nullptr;
    Sequence *oldSequence = nullptr;
    for (auto symbolIt = _sentence->begin(); symbolIt != _sentence->end(); symbolIt++) {
        // create new sequence if old is null
        if (sequence == nullptr) {
            sequence = new Sequence();
        }
        sequence->appendSymbol(*symbolIt);

        // do nothing if not long enough
        if (sequence->length() < metadata.minLength) {
            continue;
        }

        // try to get rule for this sequence
        ntSymbol = GrammarUtil::findNTSymbolForSequence(this->grammar, sequence);

        // no Nt symbol found for whole sentence
        if (ntSymbol == nullptr) {
            // done if no NT has a that long sequence
            if (sequence->length() >= metadata.maxLength) {
                break;
            }

            Sequence tmp(*symbolIt);
            ntSymbol = GrammarUtil::findNTSymbolForSequence(this->grammar, &tmp);
            if (oldSequence != nullptr) {
                delete (sequence);
                sequence = new Sequence(*oldSequence);
            }
            if (ntSymbol == nullptr) {
                sequence->appendSymbol(ntSymbol);
            } else {
                sequence->appendSymbol(*symbolIt);
            }

        } else {
            delete (sequence);
            sequence = new Sequence(ntSymbol);
        }

        oldSequence = sequence;
    }

    if (sequence != nullptr) {
        delete (sequence);
    }
    if (oldSequence != nullptr) {
        delete (sequence);
    }

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


