#include "cli.h"
#include <iostream>

int main(int argc, char **argv) {
    command_line::CommandLineInterface cmd("abc-analyzer > ");

    cmd.Run(std::cin, std::cout);
    return 0;
}