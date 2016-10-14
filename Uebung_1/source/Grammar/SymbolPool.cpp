// SymbolPool.cpp:                                        HDO, 2004-2013
// --------------
// Abstract base class Symbol is an interface for T- and NTSymbol only.
// Objects of the derived classes TSymbol and NTSymbol represent terminal
// and nonterminal symbols for use in (different) grammars respectively.
// Class SymbolPool provides a garbage collecting singleton
// that has factory methods for T- and NTSymbols.
// =====================================================================

#include <iostream>
#include <stdexcept>

using namespace std;

#include "SymbolPool.h"


// === implementation of class SymbolPool ==============================


SymbolPoolPtr SymbolPool::instance = nullptr;

SymbolPoolPtr SymbolPool::getInstance() {
  if (instance == nullptr)
    instance = SymbolPoolPtr(new SymbolPool);
  return instance;
} // SymbolPool::getInstance

void SymbolPool::clear() {
  if (instance != nullptr) {
    instance.reset();
    instance = nullptr;
  } // if
} // SymbolPool::clear


SymbolPool::SymbolPool() {
  if (instance != nullptr)
    instance.reset();
} // SymbolPool::SymbolPool

SymbolPool::~SymbolPool() {
  for (auto e: tSyMap) {
    delete e.second;
  } // for
  for (auto e: ntSyMap) {
    delete e.second;
  } // for
} // SymbolPool::~SymbolPool


static void checkName(const string name) {
  if (name.length() == 0)
    throw invalid_argument("invalid empty symbol name");
} // checkName

TSymbol *SymbolPool::tSymbol(const string name) {
  checkName(name);
  TSymbol *tSy = tSyMap[name];
  if (tSy == nullptr) {
    tSy = new TSymbol(name);
    tSyMap[name] = tSy;
  } // if
  return tSy;
} // SymbolPool::tSymbol

NTSymbol *SymbolPool::ntSymbol(const string name) {
  checkName(name);
  NTSymbol *ntSy = ntSyMap[name];
  if (ntSy == nullptr) {
    ntSy = new NTSymbol(name);
    ntSyMap[name] = ntSy;
  } // if
  return ntSy;
} // SymbolPool::ntSymbol


std::ostream &operator<<(std::ostream &os, const SymbolPool &sp) {
  os << "symbol pool: " <<
        sp. tSyMap.size() << " terminals and " <<
        sp.ntSyMap.size() << " nonterminals" << endl;
#if (1) // with contents
  bool first = true;
  os << "  terminals    = { ";
  for (auto e: sp.tSyMap) {
    if (!first)
      os << ", ";
    os << *e.second;
    first = false;
  } // for
  os << " }" << endl;
  first = true;
  os << "  nonterminals = { ";
  for (auto e: sp.ntSyMap) {
    if (!first)
      os << ", ";
    os << *e.second;
    first = false;
  } // for
  os << " }" << endl;
#endif
  return os;
} // operator<<


// === implementation of class Symbol ==================================

Symbol::Symbol(const string &name)
: name(name) {
  // nothing to do
} // Symbol::Symbol

Symbol::~Symbol() {
  // nothing to do
} // Symbol::~Symbol

bool Symbol::isT() const {
  return typeid(*this) == typeid( TSymbol);
} // Symbol::isT

bool Symbol::isNT() const {
  return typeid(*this) == typeid(NTSymbol);
} // Symbol::isT


bool isT(const Symbol *sy) {
   return sy->isT();
} // isT

bool isNT(const Symbol *sy) {
   return sy->isNT();
} // isNT


bool operator<(const Symbol &sy1, const Symbol &sy2) {
  return sy1.name < sy2.name;
} // operator<

bool operator>(const Symbol &sy1, const Symbol &sy2) {
  return sy1.name > sy2.name;
} // operator>

bool operator==(const Symbol &sy1, const Symbol &sy2) {
  return sy1.name == sy2.name;
} // operator==

bool operator!=(const Symbol &sy1, const Symbol &sy2) {
  return sy1.name != sy2.name;
} // operator!=


bool LessForSymbolPtrs::operator()(const Symbol* sy1,
                                   const Symbol* sy2) const {
  return sy1->name < sy2->name;
} // LessForSymbolPtrs::operator()

bool EqualForSymbolPtrs::operator()(const Symbol* sy1,
                                   const Symbol* sy2) const {
  return sy1->name == sy2->name;
} // EqualForSymbolPtrs::operator()


ostream &operator<<(ostream &os, const Symbol &sy) {
  os << sy.name;
  return os;
} // operator<<


// === implementation of class TSymbol =================================

TSymbol::TSymbol(const string &name)
  : Symbol(name) {
  // nothing to do
} // TSymbol::TSymbol

TSymbol::~TSymbol() {
  // nothing to do
} // TSymbol::~TSymbol


// === implementation of class NTSymbol ================================

NTSymbol::NTSymbol(const string &name)
  : Symbol(name) {
  // nothing to do
} // NTSymbol::NTSymbol

NTSymbol::~NTSymbol() {
  // nothing to do
} // NTSymbol::~NTSymbol


// === test ============================================================

#if 0

#include <cstdio>
#include <typeinfo>

int main(int argc, char *argv[]) {
try {

  SymbolPoolPtr sp = SymbolPool::getInstance();

  Symbol  * sy;
  TSymbol *tSy1, *tSy2;

  sp->getSymbol("b", tSy1);
  tSy2 = sp->tSymbol("a");
  cout << "tSy1        : " << tSy1       << endl;
  cout << "tSy2        : " << tSy2       << endl;
  cout << "tSy1->name  : " << tSy1->name << endl;
  cout << "tSy2->name  : " << tSy2->name << endl;
  cout << " tSy1 <  sy2: " << ( tSy1 <  tSy2) << endl;
  cout << "*tSy1 < *sy2: " << (*tSy1 < *tSy2) << endl;
  cout << "type of tSy1: " << tSy1->isT() << endl; // error
  cout << "type of tSy2: " << isNT(tSy2)  << endl; // error

  TSymbol  *tSy;

  NTSymbol *ntSy;

  ntSy = sp->ntSymbol("NT");
  sy   = ntSy;
  cout << "ntS:  " << *ntSy         << endl;
  cout << "kind: " <<  ntSy->isNT() << endl;

  cout << "sp.use_count: " << sp.use_count()   << endl;

} catch(const exception &e) {
  cerr <<  "ERROR (" << typeid(e).name() << "): " << e.what() << endl;
} // catch

  SymbolPool::clear();

  // cout << "type CR to continue ...";
  // getchar();

  return 0;
} // main

#endif


// end of SymbolPool.cpp
//======================================================================
