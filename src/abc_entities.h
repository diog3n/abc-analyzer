#pragma once

#include <deque>
#include <string>
#include <string_view>
#include <unordered_map>

namespace ABCAnalyzer {

using CostCenters = std::unordered_map<std::string, double>;

class Activity {
public:
    Activity(const std::string& name);

    bool HasSubActivities() const;

    const std::string& GetName() const;
    const std::deque<const Activity *>& GetSubActivies() const;
    const std::unordered_map<std::string_view, double>& GetCosts() const;

    void AddCost(const std::string_view cost_center_name, double duration);
    void AddSubActivity(const Activity& activity); 
private:
    std::string name;
    std::unordered_map<std::string_view, double> costs;
    std::deque<const Activity *> sub_activities; 
};

// class CostCenter {
// public:
//     CostCenter(const std::string& name, double value);
// 
//     const std::string& GetName() const;
// private:
//     std::string name;
//     double value;    
// };

double Calculate(const CostCenters& cost_centers, const Activity& activity);

}