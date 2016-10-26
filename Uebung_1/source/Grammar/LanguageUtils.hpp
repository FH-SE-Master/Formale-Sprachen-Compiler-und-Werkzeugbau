//
// Created by Thomas on 10/26/16.
//
#ifndef _INCLUDES_LANGUAGE_UTILS_HPP
#define _INCLUDES_LANGUAGE_UTILS_HPP

#include "Grammar.h"
#include "Language.hpp"
#include "string"

#endif

using namespace std;

// see: http://www.informatikseite.de/theorie/node43.php
namespace LanguageUtil {

    /**
     * Generates a language of the given grammar with sentences length up to given maxLength
     * @param grammar the grammar to generate language for
     * @param maxLength the max length of the to generate sentences
     * @return the generatd language
     */
    Language *generateLanguage(Grammar *grammar, int maxLength);
}