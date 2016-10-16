//
// Created by Thomas on 10/16/16.
//

#include "SequenceStuff.h"
#include "ObjectCounter.h"

using namespace std;

/**
 * This class represents a set of sentences which are part of the language of a grammar.
 */
class Language : public std::set<Sequence *>,
                 private ObjectCounter<Language> {

private:
    /**
     * The custom type definition of the extended Base
     */
    typedef std::set<Sequence *> Base;

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
     * @param sequence the seuqnce representing the sentence
     * @throws invalid_argument if the seuqnece object is null
     */
    void appendSequence(Sequence *sequence);

    /**
     * Gets the sequence at the iterator position
     * @param it the iterator to get sequence from
     * @return the seuqence referenced by the iterator
     * @throws invalid_argument if the iterator object is null
     */
    Sequence *sequenceAt(set<Sequence *>::iterator it) const;

    /**
     * Answers the question if the given sequence is part of this language.
     * @param sequence the sequence to heck
     * @return  true if part of this language, false otherwise
     * @throws invalid_argument if the seuqnece object is null
     */
    bool hasSentence(Sequence *sequence) const;
};
