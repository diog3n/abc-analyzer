#pragma once

#include "abc_entities.h"
#include <memory>
#include <ostream>
#include <string>
#include <iostream>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#define CLI_COMMAND_ADD_COST    "addcost"
#define CLI_COMMAND_ADD_ACT     "addact"
#define CLI_COMMAND_ADD_SUB     "addsub"
#define CLI_COMMAND_CALCULATE   "calculate"
#define CLI_COMMAND_EXIT        "exit"
#define CLI_COMMAND_COST_CENTER "addcostcenter"
#define CLI_COMMAND_PRINT_ALL   "printall"

namespace command_line {

struct ControlFlags {
    bool no_prompt; 
};

class CommandLineInterface {
public:
    CommandLineInterface() {}
    CommandLineInterface(const std::string& prompt);

    void Run(std::istream& in, std::ostream& out);
private:
    void AddActivity(std::string_view name);
    void AddSubActivity(std::string_view parent_name, std::string_view sub_name);
    void AddCost(std::string_view activity, std::string_view cost_center, 
                 double duration);

    void AddCostCenter(std::string_view name, double value);

    [[ deprecated ]] 
    void CalculateAndPrint(std::ostream& out) const;

    [[ deprecated ]]
    double CalculateAndPrintImpl(std::ostream& out, 
                                 const ABCAnalyzer::Activity& activity, 
                                 std::unordered_set<const ABCAnalyzer::Activity *>& visited, 
                                 int level = 0) const;

    void PrintCosts(std::ostream& out);

    void PrintCostsImpl(std::ostream& out, const ABCAnalyzer::Activity& activity, int level = 0);

    void BuildActivityTree();

    void BuildActivityTreeImpl(const ABCAnalyzer::Activity& activity, 
                               std::unordered_set<const ABCAnalyzer::Activity *>& visited); 

    std::string prompt;
    std::shared_ptr<ABCAnalyzer::Activity> root_ptr;
    std::deque<ABCAnalyzer::Activity> activities;
    std::deque<ABCAnalyzer::CostCenter> cost_centers;
    std::unordered_map<std::string_view, 
                       ABCAnalyzer::Activity *> names_to_act_ptrs;
    std::unordered_map<std::string_view,
                       const ABCAnalyzer::CostCenter *> names_to_costcs_ptrs;
};

}