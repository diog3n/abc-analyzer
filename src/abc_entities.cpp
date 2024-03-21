#include "abc_entities.h"
#include <cassert>

namespace ABCAnalyzer {

Activity::Activity(const std::string& name): name(name) {}

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

void Activity::AddCost(const std::string_view cost_center_name, double duration) {
    assert(!HasSubActivities());
    costs[cost_center_name] += duration;
}

void Activity::AddSubActivity(const Activity& activity) { 
    sub_activities.push_back(&activity);
} 

double Calculate(const CostCenters &cost_centers, const Activity &activity) {
    double result = 0.0;
    
    if (!activity.HasSubActivities()) {
        for (const auto& [cost_center_name, duration] : activity.GetCosts()) {
            result += cost_centers.at(std::string(cost_center_name)) * duration;
        }

        return result;
    }

    for (const Activity *sub_act : activity.GetSubActivies()) {
        result += Calculate(cost_centers, *sub_act); 
    }

    return result;
}

}