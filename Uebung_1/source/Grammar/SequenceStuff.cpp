// SequenceStuff.cpp:                                     HDO, 2004-2013
// -----------------
// Classes Sequence and SeqeuenceSet for sets of Sequence objects.
// Sequence objects represent (possibly empty) sequences of
//   pointers to either T- or NTymbol objects.
// SequenceSet objects take ownership of their sequences.
// =====================================================================

#include <cstdarg>

#include <iostream>
#include <stdexcept>

using namespace std;

#include "SequenceStuff.h"


// === class Sequence ==================================================

Sequence::Sequence() {
  // nothing to do for the empty sequence
} // Sequence::Sequence

Sequence::Sequence(Symbol *sy) {
  if (sy == nullptr)
    throw invalid_argument("invalid nullptr for symbol");
  push_back(sy);
} // Sequence::Sequence

Sequence::Sequence(const Sequence &seq)
  : Base(seq), ObjectCounter<Sequence>() {
  // nothing left to do
} // Sequence::Sequence

Sequence::Sequence(int n, ... /* n params. of type Symbol* */ ) {
  if (n <= 0)
    throw invalid_argument("invalid number of elements");
  va_list vaList;
  va_start(vaList, n);
  for (int i = 0; i < n; i++) {
    Symbol *sy = va_arg(vaList, Symbol*);
    if (sy == nullptr)
      throw invalid_argument("invalid nullptr for element");
    push_back(sy);
  } // for
  va_end(vaList);
} // Sequence::Sequence

#ifdef INITIALIZER_LIST_AVAILABLE
Sequence::Sequence(initializer_list<Symbol *> il) {
  for (auto sy: il) {
    push_back(sy);
  } // for
} // Sequence::Sequence
#endif

Sequence::~Sequence() {
  // nothing left to do
} // Sequence::~Sequence

void Sequence::check(iterator it) const {
  if ( (begin() <= it) && (it < end()) )
    return;
  throw range_error("sequence iterator out of range");
} // Sequence::check

int Sequence::length() const {
  return size();
} // Sequence::length

void Sequence::appendSymbol(Symbol *sy) {
  if (sy == nullptr)
    throw invalid_argument("invalid nullptr for symbol");
  push_back(sy);
} // Sequence::appendSymbol

Symbol *&Sequence::operator[](int i) {
  if ( (i < 0) || (size_t)i >= size() )
    throw range_error("index for sequence out of range");
  return Base::operator[](i);
} //

Symbol *Sequence::symbolAt(iterator it) const {
  check(it);
  return *it;
} // symbolAt

void Sequence::replaceSymbolAt(iterator it, Symbol *sy) {
  check(it);
  if (sy == nullptr)
    throw invalid_argument("invalid nullptr for symbol");
  *it = sy;
} // replaceSymbolAt

void Sequence::replaceSymbolAt(iterator it, Sequence *seq) {
  check(it);
  if (seq == nullptr)
    throw invalid_argument("invalid nullptr for sequence");
  it = erase(it);
  if (seq->size() > 0)
    insert(it, seq->begin(), seq->end());
} // Sequence::replaceElementAt

bool Sequence::hasTerminalsOnly() const {
  for (const Symbol *sy: *this) {
    if (sy->isNT())
      return false;
  } // for
  return true;
} // Sequence::hasTerminalsOnly

bool Sequence::hasNonTerminalsOnly() const {
  for (const Symbol *sy: *this) {
    if (sy->isT())
      return false;
  } // for
  return true;
}

bool Sequence::isEpsilon() const {
  return size() == 0;
} // Sequence::isEpsilon


bool operator<(const Sequence &seq1, const Sequence &seq2) {
  if (&seq1 == &seq2)
    return false;
  Sequence::const_iterator it1 = seq1.begin();
  Sequence::const_iterator it2 = seq2.begin();
  while ( (it1 != seq1.end()) &&
          (it2 != seq2.end()) ) {
    int cmpRes = (*it1)->name.compare((*it2)->name);
    if (cmpRes != 0)
      return (cmpRes < 0);
    // cmpRes == 0, so continue
    it1++;
    it2++;
  } // while
  return ( (it1 == seq1.end()) &&
           (it2 != seq2.end()) );
} // operator<


bool operator==(const Sequence &seq1, const Sequence &seq2) {
  if (&seq1 == &seq2)
    return true;
  if (seq1.size() != seq2.size())
    return false;
  return equal(seq1.begin(), seq1.end(),
               seq2.begin(),
               EqualForSymbolPtrs());
} // operator==


bool LessForSequencePtrs::operator()(const Sequence* seq1,
                                     const Sequence* seq2) const {
    return (*seq1) < (*seq2);
} // LessForSequencePtrs::operator()

bool EqualForSequencePtrs::operator()(const Sequence* seq1,
                                      const Sequence* seq2) const {
    return (*seq1) == (*seq2);
} // EqualForSequencePtrs::operator()


ostream &operator<<(ostream &os, const Sequence &seq) {
  if (seq.isEpsilon())
    os << "EPS";
  else {
    bool first = true;
    for (const Symbol *sy: seq) {
      if (!first)
        os << " ";
      os << *sy;
      first = false;
    } // for
  } // else
  return os;
} // operator<<


// === class SequenceSet ===============================================

SequenceSet::SequenceSet() {
  // nothing to do
} // SequenceSet::SequenceSet

#ifdef _MSC_VER
SequenceSet::SequenceSet(const SequenceSet &ss) {
  for (auto &seq: ss) {
    insert(new Sequence(*seq));
  } // for
} // SequenceSet::SequenceSet
#endif

SequenceSet::~SequenceSet() {
  for (auto &seq: *this) {
    delete seq;
  } // for
} // SequenceSet::~SequenceSet


bool operator==(const SequenceSet &ss1, const SequenceSet &ss2) {
  if (&ss1 == &ss2)
    return true;
  if (ss1.size() != ss2.size())
    return false;
  return equal(ss1.begin(), ss1.end(),
               ss2.begin(),
               EqualForSequencePtrs());
} // operator==

ostream &operator<<(ostream &os, const SequenceSet &ss) {
  os << "{ ";
  bool first = true;
  for (auto &seq: ss) {
    if (!first)
      os << ", ";
    os << *seq;
    first = false;
  } // for
  os << " }" << endl;
  return os;
} // operator<<



// === test ============================================================

#if 0

#include <cstdio>
#include <typeinfo>

#include "SymbolPool.cpp"

int main(int argc, char *argv[]) {
try {

  Sequence *epsilon = new Sequence();
  cout << "epsilon = " << *epsilon << endl;

  SymbolPoolPtr sp = SymbolPool::getInstance();

   TSymbol *tSy  = sp->tSymbol("terminal");
   TSymbol *aSy  = sp->tSymbol("a");
   TSymbol *bSy  = sp->tSymbol("b");
  NTSymbol *ntSy = sp->ntSymbol("nonterminal");
  NTSymbol *ASy  = sp->ntSymbol("A");
  NTSymbol *BSy  = sp->ntSymbol("B");

  Sequence *seq1    = new Sequence(tSy);
  seq1->appendSymbol(ntSy);

  Sequence *seq2;

#ifdef INITIALIZER_LIST_AVAILABLE
  seq2 = new Sequence(  {ntSy, tSy});
#else
  seq2 = new Sequence(2, ntSy, tSy);
#endif

  cout << "seq1 = " << *seq1 << endl;
  cout << "seq2 = " << *seq2 << endl;

  cout << endl;

  delete epsilon;
  delete seq1;
  delete seq2;

#ifdef INITIALIZER_LIST_AVAILABLE
  seq1 = new Sequence(  {aSy, ASy});
  seq2 = new Sequence(  {aSy, BSy});
#else
  seq1 = new Sequence(2, aSy, ASy);
  seq2 = new Sequence(2, aSy, BSy);
#endif

  cout << "seq1 = " << *seq1 << endl;
  cout << "seq2 = " << *seq2 << endl;

  cout << "seq1 <  seq2 == " << (*seq1 <  *seq2) << endl;
  LessForSequencePtrs lfsp;
  cout << "seq1 <  seq2 == " << lfsp(seq1, seq2) << endl;
  cout << "seq1 == seq2 == " << (*seq1 == *seq2) << endl;
  cout << "seq1 >  seq2 == " << (*seq1 >  *seq2) << endl;

  cout << endl;

  SequenceSet ss;
  ss.insert(seq1);
  ss.insert(seq2);
  ss.insert(new Sequence());
  cout << "sequence set = " << ss;

#ifdef _MSC_VER
  SequenceSet ss2(ss);
  cout << "copy of sequence set = " << ss2;
  cout << "original == copy ? : " << (ss == ss2) << endl;
  // ss2 deletes copies of seq1 and seq2
#endif

  // ss deletes seq1 and seq2

} catch(const exception &e) {
  cerr <<  "ERROR (" << typeid(e).name() << "): " << e.what() << endl;
} // catch

  SymbolPool::clear();

  // cout << "type CR to continue ...";
  // getchar();

  return 0;
} // main

#endif


// end of SequenceStuff.cpp
//======================================================================
