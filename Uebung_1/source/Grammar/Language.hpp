//
// Created by Thomas on 10/16/16.
//

#include "SequenceStuff.h"
#include "ObjectCounter.h"

using namespace std;

struct LessSequenceComparator { // uses operator<
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

    /**
     * Empty constructo for creating an empty Language
     * @return the empty language instance
     */
    Language();

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
     * @param sentence the sentence set representing the sentence
     * @return true if inserted, false otherwise
     * @throws invalid_argument if the seuqnece object is null
     */
    bool appendSentence(Sequence *sentence);

    /**
     * Answers the question if the given sequence is part of this language.
     * @param sentence the sequence to check if a sentence of this laguage
     * @return  true if part of this language, false otherwise
     * @throws invalid_argument if the seuqnece object is null
     */
    bool hasSentence(Sequence *sentence) const;
};

std::ostream &operator<<(std::ostream &os, const Language &language);