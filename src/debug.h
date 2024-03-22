#pragma once

#define DEBUG_PRINT_VAL(value) std::cout << #value " = " << value << std::endl
#define DEBUG_PRINT_MESG(mesg) std::cout << __FILE__ " : "\
                                         << __FUNCTION__ << "(...)" << " : "\
                                         << mesg << std::endl 
