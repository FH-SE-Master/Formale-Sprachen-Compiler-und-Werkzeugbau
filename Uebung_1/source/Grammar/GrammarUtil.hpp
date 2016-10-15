//
// Created by Thomas on 10/15/16.
//
#include "Grammar.h"
#include "string"

using namespace std;

// see: http://www.informatikseite.de/theorie/node43.php
namespace GrammarUtil {

    /**
     * Generates a epsilon free grammar of the this grammar.
     * @param grammar the grammar to transform to epsilon free grammar
     * @param symbolPool the pool to generate symbols from
     * @return the transformed epsilon free grammar, or the given grammar if already epsilon free
     * @throw invalid_argument if an parameter is null
     */
    Grammar *epsilonFreeGrammarOf(Grammar *grammar, SymbolPoolPtr symbolPool);
}