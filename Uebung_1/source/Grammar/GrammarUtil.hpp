//
// Created by Thomas on 10/15/16.
//
#include "Grammar.h"
#include "Language.hpp"
#include "string"

using namespace std;

// see: http://www.informatikseite.de/theorie/node43.php
namespace GrammarUtil {

    /**
     * Generates a epsilon free grammar of the this grammar.
     * @param _grammar the grammar to transform to epsilon free grammar
     * @return the transformed epsilon free grammar, or the given grammar if already epsilon free
     * @throw invalid_argument if an parameter is null
     */
    Grammar *epsilonFreeGrammarOf(Grammar *_grammar);

    /**
     * Generates a language of the given grammar with sentences length up to given maxLength
     * @param grammar the grammar to generate language for
     * @param maxLength the max length of the to generate sentences
     * @return the generatd language
     */
    Language *generateLanguage(Grammar *grammar, int maxLength);
}