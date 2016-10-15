// SymbolPool.h:                                          HDO, 2004-2013
// ------------
// Abstract base class Symbol is an interface for T- and NTSymbol only.
// Objects of derived classes TSymbol and NTSymbol represent terminal and
// non-terminal symbols for use in grammars respectively.
// Class SymbolPool provides a garbage collecting singleton
// that provides factory methods for T- and NTSymbols.
// =====================================================================

#ifndef SymbolPool_h
#define SymbolPool_h


#include <iosfwd>
#include <unordered_map>
#include <memory>
#include <string>
#include <typeinfo>

#include "ObjectCounter.h"


class   SymbolPool;  // singleton providing a factory for T- and NTSymbols
class   Symbol;      // abstract class
class  TSymbol;      // concrete class
class NTSymbol;      // concrete class


// === class SymbolPool ================================================

typedef std::shared_ptr<SymbolPool> SymbolPoolPtr; // shared_ptr for GC

class SymbolPool final: // no public base class
                        private ObjectCounter<SymbolPool> {

  friend std::ostream &operator<<(std::ostream &os, const SymbolPool &sp);

  private:

    static SymbolPoolPtr instance; // the one and only SymbolPool (singleton)

    std::unordered_map<std::string,  TSymbol *>  tSyMap;
    std::unordered_map<std::string, NTSymbol *> ntSyMap;

    SymbolPool();
    SymbolPool(const SymbolPool *sp); // prohibit copy construciton and ...
    SymbolPool &operator=(const SymbolPool *sp); // ... assignment

  public:

    static SymbolPoolPtr getInstance(); // get the singleton
    static void clear();

    ~SymbolPool();

     TSymbol * tSymbol(const std::string name);
    NTSymbol *ntSymbol(const std::string name);

}; // SymbolPool

std::ostream &operator<<(std::ostream &os, const SymbolPool &sp);


// === class Symbol ====================================================

class Symbol { // abstract class, so no object counting

private:

    Symbol(const Symbol *sy); // prohibit copy construction and ...
    Symbol &operator=(const Symbol *sy); // ... assignment

  protected:

    Symbol(const std::string &name);
    virtual ~Symbol() = 0;     // abstract method which needs implementation (!)

  public:

    const std::string name;    // const as symbols may be elements of set

    virtual bool isT () const; // is symbol a T  in a grammar
    virtual bool isNT() const; // is symbol a NT in a grammar

}; // Symbol

bool isT (const Symbol *sy);   // sy->isT () <==> isT (sy)
bool isNT(const Symbol *sy);   // sy->isNT() <==> isNT(sy)

bool operator< (const Symbol &sy1, const Symbol &sy2);
bool operator> (const Symbol &sy1, const Symbol &sy2);
bool operator==(const Symbol &sy1, const Symbol &sy2);
bool operator!=(const Symbol &sy1, const Symbol &sy2);

struct LessForSymbolPtrs {
  bool operator()(const Symbol *sy1, const Symbol *sy2) const;
}; // LessForSymbolPtrs

struct EqualForSymbolPtrs {
  bool operator()(const Symbol *sy1, const Symbol *sy2) const;
}; // EqualForSymbolPtrs

std::ostream &operator<<(std::ostream &os, const Symbol &sy);


// === class TSymbol ===================================================

class TSymbol final: public  Symbol,
                     private ObjectCounter<TSymbol> {

  friend class SymbolPool; // for construction and destruction only

  private:

    TSymbol(const TSymbol *tSy)= delete; // prohibit copy construction and ...
    TSymbol &operator=(const TSymbol *tSy)= delete; // ... assignment

  protected:

    TSymbol(const std::string &name);
    virtual ~TSymbol();

}; // TSymbol


// === class NTSymbol ==================================================

class NTSymbol final: public  Symbol,
                      private ObjectCounter<NTSymbol> {

  friend class SymbolPool; // for construction and destruction only

  private:

    NTSymbol(const NTSymbol *tSy) = delete; // prohibit copy construction and
    NTSymbol &operator=(const NTSymbol *tSy) = delete; // assignment

  protected:

    NTSymbol(const std::string &name);
    virtual ~NTSymbol();

}; // NTSymbol


#endif


// end of SymbolPool.h
// =====================================================================
