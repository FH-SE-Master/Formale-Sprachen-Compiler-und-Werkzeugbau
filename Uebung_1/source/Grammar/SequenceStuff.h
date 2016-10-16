// SequenceStuff.h:                                       HDO, 2004-2013
// ---------------
// Classes Sequence and SeqeuenceSet for sets of Sequence objects.
// Sequence objects represent (possibly empty) sequences of
//   pointers to either T- or NTymbol objects.
// SequenceSet objects take ownership of their sequences.
// =====================================================================

#ifndef SequenceStuff_h
#define SequenceStuff_h


#if ( (__GNUG__ >= 4) && (__GNUC_MINOR__ >= 8) ) || \
    ( _MSC_VER >= 1800 )
  #define INITIALIZER_LIST_AVAILABLE
#endif

#include <memory>
#include <set>
#include <vector>
#ifdef INITIALIZER_LIST_AVAILABLE
  #include <initializer_list>
#endif

#include "ObjectCounter.h"
#include "SymbolPool.h"


// === class Sequence ==================================================

class Sequence: public  std::vector<Symbol *>,
                private ObjectCounter<Sequence> {

  private:

    typedef std::vector<Symbol *> Base;

    Sequence &operator=(const Sequence &seq);

    void check(iterator it) const;

  public:

    typedef Base::iterator iterator;

    Sequence(); // empty Sequence aka epsilon
    Sequence(Symbol *sy);
    Sequence(const Sequence &seq);
    Sequence(int n, ... /* n params. of type Symbol * */);
#ifdef INITIALIZER_LIST_AVAILABLE
    Sequence(initializer_list<Symbol *> il);
#endif

    virtual ~Sequence();

    int length() const; // in number of Symbols

    void appendSymbol(Symbol *sy);

    Symbol *&operator[](int i);
    Symbol * symbolAt(iterator it) const;

    void replaceSymbolAt(iterator it, Symbol   *sy);
    void replaceSymbolAt(iterator it, Sequence *seq);

    bool hasTerminalsOnly() const;
    bool hasNonTerminalsOnly() const;

    bool isEpsilon() const; // <=> length() == 0

}; // Sequence

bool operator< (const Sequence &seq1, const Sequence &seq2);
bool operator==(const Sequence &seq1, const Sequence &seq2);

struct LessForSequencePtrs { // uses operator<
  bool operator()(const Sequence *seq1, const Sequence *seq2) const;
}; // LessForSequencePtrs

struct EqualForSequencePtrs { // uses operator==
  bool operator()(const Sequence *seq1, const Sequence *seq2) const;
}; // EqualForSequencePtrs

std::ostream &operator<<(std::ostream &os, const Sequence &seq);


// === class SequenceSet ===============================================

class SequenceSet: public  std::set<Sequence *, LessForSequencePtrs>,
                   private ObjectCounter<SequenceSet> {

  private:

    typedef std::set<Sequence *, LessForSequencePtrs> Base;

#ifdef __GNUG__
    SequenceSet(const SequenceSet &ss); // prohibit copy construction ...
#endif
    SequenceSet &operator=(const SequenceSet &ss); // ... and assignment

  public:

    SequenceSet();
#ifdef _MSC_VER
    SequenceSet(const SequenceSet &ss); // MS cl needs the copy constructor
#endif
    ~SequenceSet(); // deletes the elements

}; // SequenceSet

bool operator==(const SequenceSet &ss1, const SequenceSet &ss2);

std::ostream &operator<<(std::ostream &os, const SequenceSet &ss);


#endif


// end of SequenceStuff.h
//======================================================================
