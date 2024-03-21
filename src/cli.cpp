#include "cli.h"
#include "view.h"

namespace command_line {

CommandLineInterface::CommandLineInterface(const std::string& prompt):
    prompt(prompt) {}

void CommandLineInterface::Run(std::istream& in) {
    using namespace view;

    bool exiting = false;
    while (!exiting) {
        std::string line;
        std::getline(in, line);

        std::string_view line_view = line;
        line_view = TrimSpaces(line_view);

        std::string_view first_token = GetFirstWord(line_view);
        
        if (line_view == CLI_COMMAND_ADD_ACT) {
            std::vector<std::string_view> name_strings = ParseStrings(line_view);
        } else if (line_view == CLI_COMMAND_ADD_COST) {

        } else if (line_view == CLI_COMMAND_ADD_SUB) {

        } else if (line_view == CLI_COMMAND_CALCULATE) {

        } else if (line_view == CLI_COMMAND_EXIT) {

        }

        std::cerr << "Invalid command." << std::endl;
    }

    // interpret the input

    // determine which command it is

    // call the appropriate function
}

}