#include "cli.h"
#include "debug.h"
#include "abc_entities.h"
#include "view.h"
#include <iostream>
#include <ostream>
#include <string_view>

namespace command_line {

CommandLineInterface::CommandLineInterface(const std::string& prompt):
    prompt(prompt) {}

void CommandLineInterface::Run(std::istream& in, std::ostream& out) {
    using namespace view;

    bool exiting = false;
    while (!exiting) {
        out << prompt << std::flush; 

        std::string line;
        std::getline(in, line);

        if (line.empty()) continue;

        std::string_view line_view = line;
        line_view = TrimSpaces(line_view);

        std::string_view first_token = GetFirstToken(line_view);
        
        std::vector<std::string_view> strings_views = ParseStrings(line_view);
        
        if (first_token == CLI_COMMAND_ADD_ACT) {
            AddActivity(strings_views.at(0));
            continue;
        } else if (first_token == CLI_COMMAND_ADD_COST) {
            double duration = std::stod(std::string(GetLastToken(line_view))); 
            AddCost(strings_views.at(0),
                    strings_views.at(1), 
                    duration);
            continue;
        } else if (first_token == CLI_COMMAND_ADD_SUB) {
            AddSubActivity(strings_views.at(0),
                           strings_views.at(1));
            continue;
        } else if (first_token == CLI_COMMAND_COST_CENTER) {
            double value = std::stod(std::string(GetLastToken(line_view)));
            AddCostCenter(strings_views.at(0), value);
            continue;
        } else if (first_token == CLI_COMMAND_CALCULATE) {
            CalculateAndPrint(out);
            continue;
        } else if (first_token == CLI_COMMAND_PRINT_ALL) {
            for (const ABCAnalyzer::CostCenter cost_center : cost_centers) {
                out << cost_center.ToString();
            }

            for (const ABCAnalyzer::Activity activity : activities) {
                out << activity.ToString();
            }
            continue;
        } else if (first_token == CLI_COMMAND_EXIT) {
            exiting = true;            
            continue;
        }

        std::cerr << "Invalid command." << std::endl;
    }
}

void CommandLineInterface::AddActivity(std::string_view name) {
    activities.emplace_back(std::string(name));
    names_to_act_ptrs[std::string_view(activities.back().GetName())] = &activities.back();   
}

void CommandLineInterface::AddSubActivity(std::string_view parent_name,
                                          std::string_view sub_name) {
    const ABCAnalyzer::Activity *sub_ptr = names_to_act_ptrs.at(sub_name);
    names_to_act_ptrs.at(parent_name)->AddSubActivity(sub_ptr);
}

void CommandLineInterface::AddCost(std::string_view activity, 
                                   std::string_view cost_center, 
                                   double duration) {
    DEBUG_PRINT_MESG("Adding cost");
    DEBUG_PRINT_VAL(activity);
    DEBUG_PRINT_VAL(cost_center);
    DEBUG_PRINT_VAL(duration);

    const ABCAnalyzer::CostCenter *costc_ptr = names_to_costcs_ptrs.at(cost_center);
    ABCAnalyzer::Activity *activity_ptr = names_to_act_ptrs.at(activity);
    
    activity_ptr->AddCost(costc_ptr->GetName(), duration);
}

void CommandLineInterface::AddCostCenter(std::string_view name, double value) {
    cost_centers.emplace_back(std::string(name), value);
    names_to_costcs_ptrs[std::string_view(cost_centers.back().GetName())] = &cost_centers.back();    
}

void CommandLineInterface::CalculateAndPrint(std::ostream& out) const {
    double total_cost = 0.0;
    std::unordered_set<const ABCAnalyzer::Activity *> visited;
    
    for (const ABCAnalyzer::Activity& activity : activities) {

        if (visited.count(&activity) != 0) continue;

        if (activity.HasSubActivities()) {
            total_cost += CalculateAndPrintImpl(std::cout, activity, visited, 0);
        } else {
            out << "Activity: " << activity.GetName() << std::endl; 
            double cost = ABCAnalyzer::Calculate(names_to_costcs_ptrs, activity);
            total_cost += cost;
            out << "Total cost: " << cost << std::endl;
        }
    }

    out << "Total activity cost: " << total_cost << std::endl; 
}

double CommandLineInterface::CalculateAndPrintImpl(
                        std::ostream& out,
                        const ABCAnalyzer::Activity& activity, 
                        std::unordered_set<const ABCAnalyzer::Activity *>& visited,
                        int level) const {
    double result = 0;
    std::string tab(level * 2, ' ');
    
    out << tab << "Activity: " << activity.GetName() << std::endl; 

    visited.insert(&activity);

    if (activity.HasSubActivities()) {
        for (const ABCAnalyzer::Activity *sub_activity : activity.GetSubActivies()) {
            result += CalculateAndPrintImpl(out, *sub_activity, visited, level + 1);
        }
    } else {
        result = ABCAnalyzer::Calculate(names_to_costcs_ptrs, activity);
    }

    out << tab << "Total cost: " << result << std::endl;

    return result;
}

}