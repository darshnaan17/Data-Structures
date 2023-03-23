/*
*********************************
*                               *
*         Darshan Vala          *
*         U39780959             *
*                               *
*********************************
*/

#ifndef GRITVM_HPP
#define GRITVM_HPP
#include <vector>
#include <list>
#include <iterator>
#include <string>
#include <fstream>
#include <iostream>

#include "GritVMBase.hpp"


using namespace std;

class GritVM : public GritVMInterface{

      public:
            GritVM ();
            STATUS load(const std::string filename, const std::vector<long> &initialMemory);
            STATUS run();
            std::vector<long> getDataMem();
            STATUS reset();

      private:
            std::vector<long> dataMem;
            std::list<Instruction> instructMem;
            std::list<Instruction>::iterator currentInstruct;
            STATUS machineStatus;
            long accumulator;

};

#endif
