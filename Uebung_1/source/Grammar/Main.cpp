// Main.cpp:                                             HDO, 2004-2013
// --------
// Main program for the object-oriented representation of formal
// languages uing classes for symbols, sequences and grammars.
// ====================================================================

#include <cstdio>

#include <iostream>
#include <typeinfo>

using namespace std;

#include "SymbolPool.h"
#include "SequenceStuff.h"
#include "Vocabulary.h"
#include "Grammar.h"
#include "GrammarUtil.hpp"

// Activation (with 1) allows simple build via command line
//   * for GNU       use:  g++ -std=c++11 Main.cpp
//   * for Microsoft use:  cl Main.cpp
#if (0)
#include "SymbolPool.cpp"
#include "SequenceStuff.cpp"
#include "Grammar.cpp"
#endif


int main(int argc, char *argv[]) {

    cout << "START Main" << endl << endl;

    try {

        SymbolPoolPtr sp = SymbolPool::getInstance();
        cout << *sp << endl;

        Grammar *g = nullptr;


// *** test case selection ***
#define TESTCASE 4
// ***************************

        cout << "TESTCASE " << TESTCASE << endl << endl;


#if TESTCASE == 1 // programmatical grammar construction

        // G(S):
        // S -> A ;
        // A -> a B | B B b
        // B -> b | a b
        NTSymbol *S  = sp->ntSymbol("S");
        NTSymbol *A  = sp->ntSymbol("A");
        NTSymbol *B  = sp->ntSymbol("B");
         TSymbol *a  = sp-> tSymbol("a");
         TSymbol *b  = sp-> tSymbol("b");
         TSymbol *sc = sp-> tSymbol(";");

#ifndef INITIALIZER_LIST_AVAILABLE
        Sequence *seq1 = new Sequence(2, A, sc   );
        Sequence *seq2 = new Sequence(2, a, B    );
        Sequence *seq3 = new Sequence(3, B, B, b );
#else
        Sequence *seq1 = new Sequence(  {S, sc  });
        Sequence *seq2 = new Sequence(  {a, B   });
        Sequence *seq3 = new Sequence(  {B, B, b});
#endif

        g = new Grammar(S);
        g->addRule(S, seq1);
#ifndef INITIALIZER_LIST
        g->addRule(A, 2, seq2, seq3 );
        g->addRule(B, 2, new Sequence(b), new Sequence(2, a, b) );
#else
        g->addRule(A,   {seq2, seq3});
        g->addRule(B,   {new Sequence(b), new Sequence(  {a, b}));
#endif

        cout << "Grammar g: " << endl << *g << endl;


#elif TESTCASE == 2 // grammar construction from text file

        g = new Grammar(string("Grammar1.txt"));

        cout << *g << endl;


#elif TESTCASE == 3 // grammar construction from C string literal

        g = new Grammar(
          "G(S):                          \n\
           S -> E ;                       \n\
           E -> a A b E | b B a E | EPS   \n\
           A -> a A b A | EPS             \n\
           B -> b B a B | EPS             ");

        cout << *g;

        g->identifyDeletableNTs();
        cout << "deletable nts identified:" << *g;


#elif TESTCASE == 4
        g = new Grammar(
                "G(S):                          \n\
                 S -> A B C                     \n\
                 A -> B B | EPS                 \n\
                 B -> C C | a                   \n\
                 C -> A A | b                     ");

        cout << *g;

        GrammarUtil::epsilonFreeGrammarOf(g, sp);

#else // none of the TESTCASEs above

        cerr << "ERROR: invalid TESTCASE == " << TESTCASE << endl;
#endif

        delete g;
        cout << *sp << endl;
        sp->clear(); // or SymbolPool::clear();

    } catch (const exception &e) {
        cerr << "ERROR (" << typeid(e).name() << "): " << e.what() << endl;
    } // catch

    cout << endl;
    cout << "END Main" << endl;

    cout << "type CR to continue ...";
    getchar();

    return 0;
} // main


// end of Main.cpp
//======================================================================
