#include "GritVMBase.hpp"

#include <map>
#include <sstream>
#include <iterator>

std::string GVMHelper::statusToString(STATUS s) {
  switch (s) {
    case WAITING: return "WAITING";
    case READY:   return "READY";
    case RUNNING: return "RUNNING";
    case HALTED:  return "HALTED";
    case ERRORED: return "ERRORED";
    default:      return "UNKNOWN";
  }
}

std::string GVMHelper::instructionToString(INSTRUCTION_SET s) {
  switch (s) {
    case CLEAR:     return "CLEAR";
    case AT:        return "AT";
    case SET:       return "SET";
    case INSERT:    return "INSERT";
    case ERASE:     return "ERASE";
    case ADDCONST:  return "ADDCONST";
    case SUBCONST:  return "SUBCONST";
    case MULCONST:  return "MULCONST";
    case DIVCONST:  return "DIVCONST";
    case ADDMEM:    return "ADDMEM";
    case SUBMEM:    return "SUBMEM";
    case MULMEM:    return "MULMEM";
    case DIVMEM:    return "DIVMEM";
    case JUMPREL:   return "JUMPREL";
    case JUMPZERO:  return "JUMPZERO";
    case JUMPNZERO: return "JUMPNZERO";
    case NOOP:      return "NOOP";
    case HALT:      return "HALT";
    case OUTPUT:    return "OUTPUT";
    case CHECKMEM:  return "CHECKMEM";
    default:        return "UNKNOWN_INSTRUCTION";
  }
}

STATUS GVMHelper::stringToStatus(std::string s) {
  static std::map<std::string, STATUS> statusMapping = {
    { "WAITING",  WAITING },
    { "READY",    READY   },
    { "RUNNING",  RUNNING },
    { "HALTED",   HALTED  },
    { "ERRORED",  ERRORED }
  };

  return (statusMapping.count(s) == 0) ? UNKNOWN : statusMapping[s];
}

INSTRUCTION_SET GVMHelper::stringtoInstruction(std::string s) {
  static std::map<std::string, INSTRUCTION_SET> instructionSetMapping = {
    { "CLEAR", CLEAR },
    { "AT", AT },
    { "SET", SET },
    { "INSERT", INSERT },
    { "ERASE", ERASE },
    { "ADDCONST", ADDCONST },
    { "SUBCONST", SUBCONST },
    { "MULCONST", MULCONST },
    { "DIVCONST", DIVCONST },
    { "ADDMEM", ADDMEM },
    { "SUBMEM", SUBMEM },
    { "MULMEM", MULMEM },
    { "DIVMEM", DIVMEM },
    { "JUMPREL", JUMPREL },
    { "JUMPZERO", JUMPZERO },
    { "JUMPNZERO", JUMPNZERO },
    { "NOOP", NOOP },
    { "HALT", HALT },
    { "OUTPUT", OUTPUT },
    { "CHECKMEM", CHECKMEM }
  };

  return (instructionSetMapping.count(s) == 0) ? UNKNOWN_INSTRUCTION : instructionSetMapping[s];
}

Instruction GVMHelper::parseInstruction(std::string gvmLine) {
  if (gvmLine.empty()) return Instruction(UNKNOWN_INSTRUCTION, 0);

  std::istringstream ss(gvmLine);
  std::istream_iterator<std::string> it(ss);

  INSTRUCTION_SET instruct = UNKNOWN_INSTRUCTION;
  long arg = 0;

  try {
    instruct = GVMHelper::stringtoInstruction(*it);
    it++;
    arg = std::stol(*it);
  } catch (std::exception) {
    // The argument is invalid, either way we will read it in as zero
  }

  return Instruction(instruct, arg);
}
