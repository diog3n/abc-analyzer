#include "cli.h"
#include <clocale>
#include <iostream>

int main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    command_line::CommandLineInterface cmd;

    cmd.Run(std::cin, std::cout);
    return 0;
}