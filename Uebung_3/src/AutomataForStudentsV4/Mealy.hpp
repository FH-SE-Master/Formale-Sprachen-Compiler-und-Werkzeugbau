//
// Created by Thomas on 11/10/16.
//

#ifndef AUTOMATAFORSTUDENTSV4_MEALY_HPP
#define AUTOMATAFORSTUDENTSV4_MEALY_HPP

#include "DFA.h"
#include "string.h"

using namespace std;

typedef std::function<char(char)> Mapper;

class Mealy : public DFA {

private:
    Mapper mapper;

public:
    Mealy(Mapper mapper): mapper(mapper){}
};


#endif //AUTOMATAFORSTUDENTSV4_MEALY_HPP
