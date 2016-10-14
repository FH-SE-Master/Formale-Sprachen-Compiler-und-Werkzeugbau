// ObjectCounter.h:                                            HDO, 2013
// ---------------
// Simple mechanism to count objects of any user defined class and
// report garbage on termination. Usage:
//   class Any: ..., private ObjectCounter<Any> { ... };
// Implementation based on CRTP (curiously recurring template pattern),
// see en.wikipedia.org/wiki/Curiously_recurring_template_pattern.
// =====================================================================

#ifndef ObjectCounter_h
#define ObjectCounter_h


#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <unordered_map>


// Activation or deactivation of object counting with #define or #undef
#define DO_OBJECT_COUNTING


#ifndef DO_OBJECT_COUNTING  // no object counting


  template <class DC>
  class ObjectCounter {     // dummy object counter
  }; // ObjectCounter<DC>


#else                       // do object counting


template <class DC>
class OCData;               // short for ObjectCounterData, see below

template <class DC>         // DC is a derived class of ObjectCounter, which
class ObjectCounter {       //   counts objects of class DC

  private:

    static OCData<DC> d;

    ObjectCounter(const ObjectCounter &oc); // prohibit copy construction

  protected:

    ObjectCounter() {       // called by each of DC's constructors
      d.nConstr++;
      auto ic = d.om.insert(make_pair(this, d.nConstr));
      if (!ic.second) // this already has been an element of om
        throw std::logic_error("re-construction of object");
    } // ObjectCounter

    virtual ~ObjectCounter() {      // called by DC's destructor
      size_t ec = d.om.erase(this);
      if (ec == 1) // this has been an element of om
        d.nDestr++;
      else // ec == 0, so this has not been registered in om
        d.nDestrUnreg++;
  } //~ObjectCounter

}; // ObjectCounter<DC>

template <class DC>
OCData<DC> ObjectCounter<DC>::d(std::string(typeid(DC).name()));


template <class DC>
class OCData final {        // short for ObjectCounterData

  friend class ObjectCounter<DC>;

  private:

    const std::string className; // format depends on RTTI, roughly "...DC..."
    int nConstr, nDestr; // number of calls for constructors and destructor
    int nDestrUnreg;     // number of destructions of unregistered objects
    std::unordered_map<void *, int> om; // object map: address -> nConstr

    OCData(); // prohibit default construction, ...
    OCData(const OCData &ocd); // ... copy construction and ...
    OCData &operator=(const OCData &ocd); // ... assignment

    OCData(const std::string &className)
    : className(className), nConstr(0), nDestr(0), nDestrUnreg(0), om() {
      // nothing to do
    } // OCData

    virtual ~OCData() {
      int nAlive = nConstr - nDestr;
      if (!cout.good())
        return;
      std::cout << std::endl;
      std::cout << "ObjectCounter<" << className << ">: " <<
                   "+" << nConstr << " -" << nDestr << " = " << nAlive << " alive";
      if (nDestrUnreg > 0)
        std::cout << ", destr. of unreg. obj. = " << nDestrUnreg;
      std::cout << std::endl;
      if (nAlive > 0) {
        std::map<int, void *> iom; // inverted om: nConstr -> address
        for (auto &e: om) {
          iom[e.second] = e.first;
        } // for
        for (auto &e: iom) {
          std::cout << "  constrNr=" << e.first << ", address=" << e.second;
#if (0) // activate if  all classes DC have operator<< defined
          std::cout << ": " << *((DC*)e.second);
#endif
          std::cout << std::endl;
        } // for
      } // if
    } // ~OCData

}; // OCData<DC>


#endif // DO_OBJECT_COUNTING


#endif


// end of ObjectCounter.h
// =====================================================================
