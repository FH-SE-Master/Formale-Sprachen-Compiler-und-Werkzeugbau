//
// Created by Thomas on 11/21/16.
//

#ifndef AUTOMATAFORSTUDENTSV4_AUTOMATEUTIL_HPP
#define AUTOMATAFORSTUDENTSV4_AUTOMATEUTIL_HPP

#include "Grammar.h"
#include "NFA.h"

namespace AutomateUtil {

    /**
     * Converts a grammar to a non-determenistic automat called NFA.
     * @param grammar the grammar to build the NFA for
     * @return the build nfa
     * @throws invalid_argument if grammar is either nll or not a regular one.
     */
    NFA *nfaOfGrammar(const Grammar *grammar);

    Grammar *grammarOfNfa(const NFA *nfa);
}
#endif //AUTOMATAFORSTUDENTSV4_AUTOMATEUTIL_HPP
