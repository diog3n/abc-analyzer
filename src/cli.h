#pragma once

#include "abc_entities.h"
#include <ostream>
#include <string>
#include <iostream>
#include <unordered_map>

#define CLI_COMMAND_ADD_COST    "addcost"
#define CLI_COMMAND_ADD_ACT     "addact"
#define CLI_COMMAND_ADD_SUB     "addsub"
#define CLI_COMMAND_CALCULATE   "calculate"
#define CLI_COMMAND_EXIT        "exit"
#define CLI_COMMAND_COST_CENTER "addcostcenter"
#define CLI_COMMAND_PRINT_ALL   "printall"

namespace command_line {

class CommandLineInterface {
public:
    CommandLineInterface(const std::string& prompt);

    void Run(std::istream& in, std::ostream& out);
private:
    void AddActivity(std::string_view name);
    void AddSubActivity(std::string_view parent_name, std::string_view sub_name);
    void AddCost(std::string_view activity, std::string_view cost_center, double duration);

    void AddCostCenter(std::string_view name, double value);

    std::string prompt;
    std::deque<ABCAnalyzer::Activity> activities;
    std::deque<ABCAnalyzer::CostCenter> cost_centers;
    std::unordered_map<std::string_view, 
                       ABCAnalyzer::Activity *> names_to_act_ptrs;
    std::unordered_map<std::string_view,
                       ABCAnalyzer::CostCenter *> names_to_costcs_ptrs;
};

}