#pragma once

#include "abc_entities.h"
#include <string>
#include <iostream>
#include <unordered_map>

#define CLI_COMMAND_ADD_COST  "addcost"
#define CLI_COMMAND_ADD_ACT   "addact"
#define CLI_COMMAND_ADD_SUB   "addsub"
#define CLI_COMMAND_CALCULATE "calculate"
#define CLI_COMMAND_EXIT      "exit"

namespace command_line {

class CommandLineInterface {
public:
    CommandLineInterface(const std::string& prompt);

    void Run(std::istream& in);
private:
    std::string prompt;
    std::deque<ABCAnalyzer::Activity> activities;
    std::unordered_map<std::string_view, 
                       ABCAnalyzer::Activity *> names_to_act_ptrs;
};

}