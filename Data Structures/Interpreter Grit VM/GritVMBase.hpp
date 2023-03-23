#ifndef GRITVMBASE_H
#define GRITVMBASE_H

#include <string>
#include <vector>

// All possibly instructions the GritVM can run
typedef enum _instruction_set {
  // Accumulator Functions
  CLEAR,

  // Data Memory Management Functions
  AT, SET, INSERT, ERASE,

  // Accumulator Maths with a constant
  ADDCONST, SUBCONST, MULCONST, DIVCONST,

  // Accumulator Maths with a memory location
  ADDMEM, SUBMEM, MULMEM, DIVMEM,

  // Instruction Jump Functions
  JUMPREL, JUMPZERO, JUMPNZERO,

  // Misc Functions
  NOOP, HALT, OUTPUT, CHECKMEM,

  // USE ONLY FOR BAD TRANSLATIONS READS (Ex: Typos in gvm file)
  UNKNOWN_INSTRUCTION
} INSTRUCTION_SET;

typedef enum _status {
  WAITING,  // Waiting to load a program 
  READY,    // Program loaded and ready to run
  RUNNING,  // Actively running a program
  HALTED,   // Program halted, whether by a HALT instruction or reaching the end of instruction
  ERRORED,  // The program stopped because of an error
  UNKNOWN   // Unknown status. Should never happen in normal control flow
} STATUS;


typedef struct _instruction {
  INSTRUCTION_SET operation; long argument;

  _instruction(INSTRUCTION_SET i, long arg = 0) : operation(i), argument(arg) {};
} Instruction;

class GritVMInterface {
public:
  virtual STATUS              load(const std::string filename, const std::vector<long> &initialMemory) = 0;
  virtual STATUS              run() = 0;
  virtual std::vector<long>   getDataMem() = 0;
  virtual STATUS              reset() = 0;
};

namespace GVMHelper {
  std::string     statusToString(STATUS s);
  STATUS          stringToStatus(std::string s);
  std::string     instructionToString(INSTRUCTION_SET s);
  INSTRUCTION_SET stringtoInstruction(std::string s);
  Instruction     parseInstruction(std::string gvmLine);
};

#endif /* GRITVM_H */