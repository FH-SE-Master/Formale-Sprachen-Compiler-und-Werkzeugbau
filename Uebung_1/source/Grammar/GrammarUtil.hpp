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

    typedef struct _GrammarMetaData {
    public:
        int minLength = 0;
        int maxLength = 0;
    } GrammarMetadata;

    NTSymbol reduceToNTSymbol(Sequence *sequence);

    GrammarMetadata collectGrammarMetadata(const Grammar *_grammar);

    NTSymbol *findNTSymbolForSequence(const Grammar *grammar, Sequence *_sequence);

    /**
     * Generates a epsilon free grammar of the this grammar.
     * @param _grammar the grammar to transform to epsilon free grammar
     * @return the transformed epsilon free grammar, or the given grammar if already epsilon free
     * @throw invalid_argument if an parameter is null
     */
    Grammar *epsilonFreeGrammarOf(const Grammar *_grammar);
}