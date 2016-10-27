//
// Created by Thomas on 10/16/16.
//
#ifndef _INCLUDES_LANGUAGE_HPP
#define _INCLUDES_LANGUAGE_HPP

#include "SequenceStuff.h"
#include "ObjectCounter.h"
#include "Grammar.h"

#endif

using namespace std;

/**
 * Orders the sequences ascending by the symbol length
 */
struct LessSequenceComparator {
    bool operator()(const Sequence *seq1, const Sequence *seq2) const;
}; // LessSequenceComparator

/**
 * This class represents a set of sentences which are part of the language of a grammar.
 */
class Language : public std::set<Sequence *, LessSequenceComparator>,
                 private ObjectCounter<Language> {

private:
    /**
     * The custom type definition of the extended Base
     */
    typedef std::set<Sequence *, LessSequenceComparator> Base;

public:

    const Grammar *grammar;

    /**
     * Empty constructo for creating an empty Language
     * @return the empty language instance
     */
    Language(const Grammar *grammar);

    /**
     * Copy constructor for copying the Language
     * @param language the language to copy
     * @return the copied language
     * @throws invalid_argument if the language object is null
     */
    Language(const Language &language);

    /**
     * Destructor for deleting the Language and the held Sequences
     */
    ~Language();

    /**
     * Appends a sentence to the language
     * @param _sentence the sentence set representing the sentence
     * @return true if inserted, false otherwise
     * @throws invalid_argument if the seuqnece object is null
     */
    bool appendSentence(Sequence *_sentence);

    /**
     * Answers the question if the given sequence is part of this language.
     * @param _sentence the sequence to check if a sentence of this laguage
     * @return  true if part of this language, false otherwise
     * @throws invalid_argument if the seuqnece object is null
     */
    bool hasSentence(Sequence *_sentence);

    /**
     * Answers the question if a sentence represented by the given sequence is already part of this language instance
     * @param _sentence the pointer to the sequence object
     * @return true if sentece already registered in language, false otherwise
     */
    bool containsSentence(Sequence *_sentence);
};

/**
 * The outstream operator implementation.
 *
 * @param os the current ouput stream
 * @param language the language object to be put on stream
 * @return the manipulated output stream
 */
std::ostream &operator<<(std::ostream &os, const Language &language);