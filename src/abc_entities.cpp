#include "abc_entities.h"
#include "debug.h"
#include <cassert>
#include <cmath>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

namespace ABCAnalyzer {

Activity::Activity(const std::string& name, 
                   const std::unordered_map<std::string_view, 
                                      const CostCenter *> *cost_centers)
                   : name(name), cost_centers(cost_centers) {}

bool Activity::HasSubActivities() const {
    return !sub_activities.empty();
}

const std::string& Activity::GetName() const {
    return name; 
}

const std::unordered_map<std::string_view, double>& Activity::GetCosts() const {
    return costs;
}

const std::deque<const Activity *>& Activity::GetSubActivies() const {
    return sub_activities; 
}

double Activity::GetTotalCost() const {
    return total_cost;
}

bool Activity::IsSubActivity() const {
    return parent != nullptr;
}

void Activity::RecalculateTotalCost() {
    double result = 0.0;
    
    if (!HasSubActivities()) {
        for (const auto& [cost_center_name, duration] : costs) {
            result += cost_centers->at(cost_center_name)->GetValue() * duration;
        }
    }

    for (const Activity *sub_act : sub_activities) {
        result += sub_act->GetTotalCost(); 
    }

    total_cost = result;
    
    if (IsSubActivity()) {
        parent->RecalculateTotalCost();
    }
}

void Activity::AddCost(const std::string_view cost_center_name, double duration) {
    costs[cost_center_name] += duration;
    RecalculateTotalCost();
}

void Activity::AddSubActivity(Activity& activity) { 
    activity.parent = this; 
    sub_activities.push_back(&activity);
    RecalculateTotalCost();
} 

void Activity::AddSubActivity(Activity *activity) { 
    AddSubActivity(*activity);
} 

std::string Activity::ToString(int level) const {
    std::ostringstream out;
    std::string tab(level * 2, ' ');
    
    out << tab << "Activity name: " << name << std::endl;
    
    out << tab << "Costs: " << std::endl;
    for (const auto& [cost_name, duration] : costs) {
        out << tab << cost_name << ", duration: " << duration << std::endl; 
    }
    
    if (sub_activities.empty()) return out.str();

    out << tab << "Sub activities: " << std::endl;    
    
    level++;
    
    for (const Activity *act_ptr : sub_activities) {
        out << act_ptr->ToString(level) << std::endl;
    }

    return out.str();
}

CostCenter::CostCenter(const std::string& name, double value)
    : name(name)
    , value(value) {}

const std::string& CostCenter::GetName() const {
    return name;
}

double CostCenter::GetValue() const {
    return value;
} 

std::string CostCenter::ToString() const {
    std::ostringstream out;
    out << "Cost center name: " << name << ", value: " << value << std::endl;

    return out.str();
}

double Calculate(const CostCenters &cost_centers, const Activity &activity) {
    double result = 0.0;
    
    if (!activity.HasSubActivities()) {
        for (const auto& [cost_center_name, duration] : activity.GetCosts()) {
            result += cost_centers.at(cost_center_name)->GetValue() * duration;
        }

        return result;
    }

    for (const Activity *sub_act : activity.GetSubActivies()) {
        result += Calculate(cost_centers, *sub_act); 
    }

    return result;
}

}