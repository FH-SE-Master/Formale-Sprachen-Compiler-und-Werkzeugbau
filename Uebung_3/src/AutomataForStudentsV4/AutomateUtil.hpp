//
// Created by Thomas on 11/21/16.
//

#ifndef AUTOMATAFORSTUDENTSV4_AUTOMATEUTIL_HPP
#define AUTOMATAFORSTUDENTSV4_AUTOMATEUTIL_HPP

#include <ctime>
#include <string>
#include "Grammar.h"
#include "NFA.h"
#include "DFA.h"

#define UNDEF_ENTRY  'u'
#define EQUIVALENT_ENTRY 'e'
#define NOT_EQUIVALENT_ENTRY  'n'

namespace AutomateUtil {

    /**
     * The type for the table entries used during minimal check
     */
    typedef char TableEntry;

    /**
     * Simple Clock for time measureing
     */
    struct Clock {
        double duration = 0;
        std::clock_t start;
        std::clock_t end;

        void startMeasure() {
            start = end = std::clock();
        }

        void endMeasure() {
            end = std::clock();
            std::cout << "Duration: " << (duration = (end - start) / (double) CLOCKS_PER_SEC) << std::endl;
        }
    };

    /**
     * Converts a grammar to a non-determenistic automat called NFA.
     * @param grammar the grammar to build the NFA for
     * @return the build nfa
     * @throws invalid_argument if grammar is either nll or not a regular one.
     */
    NFA *nfaOfGrammar(const Grammar *grammar);

    /**
     * Creates the Grammar corresponding zu the given NFA.
     * @param nfa the nfa instance to get grammar for
     * @return the created grammar
     * @throw invalid_argument if the nfa instance is null
     */
    Grammar *grammarOfNfa(const NFA *nfa);
}
#endif //AUTOMATAFORSTUDENTSV4_AUTOMATEUTIL_HPP
