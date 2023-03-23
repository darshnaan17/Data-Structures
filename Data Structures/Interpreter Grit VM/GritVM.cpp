/*
*********************************
*                               *
*         Darshan Vala          *
*         U39780959             *
*                               *
*********************************
*/

#ifndef GRITVM_CPP
#define GRITVM_CPP

#include "GritVM.hpp"

//Constructor,  start with waiting and at 0
GritVM::GritVM()
{
    machineStatus = WAITING;
    accumulator = 0;
}

//reset: accumulator 0, clears, WAITING
STATUS GritVM::reset()
{
    machineStatus = WAITING;
    accumulator = 0;
    dataMem.clear();
    instructMem.clear();
    return machineStatus;
}

//getting data memember
std::vector<long> GritVM::getDataMem()
{
    return dataMem;
}

//Load function to load in files
STATUS GritVM::load(const std::string filename, const std::vector<long> &initialMemory)
{

    if (machineStatus != WAITING )
    {
        return machineStatus;
    }

    ifstream code;
    string read_Doc;
    code.open(filename);

   //make sure file is open
    if(!code.good())
    {
        throw ("ERROR: FILE FAILED TO OPEN");
    }


    else
    {
        machineStatus = READY;

        while(getline(code, read_Doc))
        {
            if(read_Doc.empty())
            {
                continue;
            }

            if (read_Doc[0] == '#')
            {
                continue;
            }
            Instruction instructions = GVMHelper::parseInstruction(read_Doc);

            if(instructions.operation == UNKNOWN_INSTRUCTION)
            {
                return machineStatus = ERRORED;
            }

            instructMem.push_back(GVMHelper::parseInstruction(read_Doc));
        }
    }

    dataMem = initialMemory;

    if(instructMem.size() != 0)
    {
        machineStatus = READY;
    }

    else
    {
        machineStatus = WAITING;
    }

    return machineStatus;
}

//Starts the checks and returns the status.
STATUS GritVM::run()
{
    switch(machineStatus)
    {
        case WAITING:
        {
                    break;
        }

        case READY:
        {
                    machineStatus = RUNNING;
                    break;
        }

		    case RUNNING:
        {
                    break;
        }

		    case HALTED:
        {
                    GritVM::reset();
                    break;
        }

		    case ERRORED:
        {
                    GritVM::reset();
			              break;
        }

		    case UNKNOWN:
        {
                    GritVM::reset();
                    break;
        }
    }

    currentInstruct = instructMem.begin();
    while(machineStatus == RUNNING)
    {
        if (currentInstruct == instructMem.end())
        {
            machineStatus = HALTED;
        }

        switch(currentInstruct -> operation)
        {
            case CLEAR:
            {
                      accumulator = 0;
                      break;
            }

            case AT:
            {
                    accumulator = dataMem.at(currentInstruct -> argument);
                    break;
            }

            case SET:
            {
                    dataMem.at(currentInstruct -> argument) = accumulator;
                    break;
            }

            case INSERT:
            {
                        dataMem.insert(dataMem.begin() + (currentInstruct -> argument), accumulator);
      				          break;
            }

			      case ERASE:
            {
                      dataMem.erase(dataMem.begin() + currentInstruct -> argument);
      				        break;
            }

			      case ADDCONST:
            {
                          accumulator += currentInstruct -> argument;
      				            break;
            }

			      case SUBCONST:
            {
                          accumulator -= currentInstruct -> argument;
      				            break;
            }

			      case MULCONST:
            {
                          accumulator *= currentInstruct -> argument;
      				            break;
            }

			      case DIVCONST:
            {
                          accumulator /= currentInstruct -> argument;
                          break;
            }

			      case ADDMEM:
            {
                        accumulator += dataMem.at(currentInstruct -> argument);
      				          break;
            }

			      case SUBMEM:
            {
                        accumulator -= dataMem.at(currentInstruct -> argument);
      				          break;
            }

			      case MULMEM:
            {
                        accumulator *= dataMem.at(currentInstruct -> argument);
      				          break;
            }

			      case DIVMEM:
            {
                        accumulator /= dataMem.at(currentInstruct -> argument);
      				          break;
            }

            case JUMPREL:
            {
                        if (currentInstruct -> argument < 0)
                        {
                            for (int j = currentInstruct -> argument; j <= 0; j++)
                            {
                                currentInstruct--;
                            }
                        }
                        else if ( currentInstruct -> argument == 0)
                        {
                            continue;
                        }
                        else
                        {
                            for (int j =  currentInstruct -> argument; j >= 0; j--)
                            {
                                currentInstruct++;
                            }
                        }
                        break;
            }

            case JUMPZERO:
            {
                          if (accumulator == 0)
                          {
                              if(currentInstruct -> argument < 0)
                              {
                                  for (int j = currentInstruct -> argument; j < 0; j++)
                                  {
                                      currentInstruct--;
                                  }
                                  currentInstruct--;
                              }

                              else
                              {
                                  for (int j = currentInstruct -> argument; j > 0; j--)
                                  {
                                      currentInstruct++;
                                  }
                                    currentInstruct--;
                              }
                         }
                         break;
            }

            case JUMPNZERO:
            {
                          if(accumulator != 0)
                          {
                              if(currentInstruct -> argument < 0)
                              {
                                for (int j = currentInstruct -> argument; j < 0; j++)
                                {
                                    currentInstruct--;
                                }
                                currentInstruct--;
                              }

                              else
                              {
                                  for(int j = currentInstruct -> argument; j > 0; j--)
                                  {
                                      currentInstruct++;
                                  }
                                  currentInstruct--;
                              }
                          }
                          break;
            }

            case NOOP:
            {
                      break;
            }

            case HALT:
            {
                      machineStatus = HALTED;
                      break;
            }

            case OUTPUT:
            {
                        break;
            }

            case CHECKMEM:
            {
                          if(int(currentInstruct -> argument) <= int(dataMem.size()))
                          {
                              break;
                          }

                          else
                          {
                              machineStatus = ERRORED;
                          }
                          break;
            }

            case UNKNOWN_INSTRUCTION:
            {
                                    machineStatus = ERRORED;
                                    break;
            }

            default:
            {
                    machineStatus = HALTED;
                    break;
            }

        }// end of switch
    currentInstruct++;

    if(currentInstruct == instructMem.end())
    {
        machineStatus = HALTED;
    }
 } // end of while
    return machineStatus; // returns machine status
}
#endif
