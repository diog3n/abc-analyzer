#pragma once
#include <iostream>
#define DEBUG_PRINT_VAL(value) std::cerr << #value " = " << value << std::endl
#define DEBUG_PRINT_MESG(mesg) std::cerr << __FILE__ " : "\
                                         << __FUNCTION__ << "(...)" << " : "\
                                         << mesg << std::endl 
