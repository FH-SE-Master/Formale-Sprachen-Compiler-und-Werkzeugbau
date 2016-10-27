//
// Created by Thomas on 10/15/16.
//
#ifndef _INCLUDES_LANGUAGE_UTILS_HPP
#define _INCLUDES_LANGUAGE_UTILS_HPP

#include "Grammar.h"
#include "string"

#endif

using namespace std;

// see: http://www.informatikseite.de/theorie/node43.php
namespace GrammarUtil {

    /**
     * Generates a epsilon free grammar of the this grammar.
     * @param _grammar the grammar to transform to epsilon free grammar
     * @return the transformed epsilon free grammar, or the given grammar if already epsilon free
     * @throw invalid_argument if an parameter is null
     */
    Grammar *epsilonFreeGrammarOf(const Grammar *_grammar);

    /**
     * Finds all NTSymbols the given sequence can be reduced to.
     * @param grammar the related grammar
     * @param _sequence the sequene to be tried to be reduced
     * @return the set of found NTSymbols
     */
    set<NTSymbol *> findNTSymbolSForSequence(const Grammar *grammar, Sequence *_sequence);

    /**
     * Reduces the given sentences up to the root NTSymbol.
     * @param grammar the related grammar
     * @param _sentence the sentence to be reduced
     * @return the last symbol which should be the root symbol of the grammar if the sentence
     *          is a sentence of the grammar related language
     */
    Symbol *reduce(const Grammar *grammar, Sequence _sentence);
}