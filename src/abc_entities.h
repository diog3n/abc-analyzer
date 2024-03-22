#pragma once

#include <deque>
#include <string>
#include <string_view>
#include <unordered_map>

namespace ABCAnalyzer {

class CostCenter {
public:
    CostCenter(const std::string& name, double value);

    const std::string& GetName() const;
    double GetValue() const;

    std::string ToString() const; 
private:
    std::string name;
    double value;    
};

class Activity {
public:
    Activity(const std::string& name, 
             const std::unordered_map<std::string_view, 
                                      const CostCenter *> *cost_centers);

    bool HasSubActivities() const;

    const std::string& GetName() const;
    const std::deque<const Activity *>& GetSubActivies() const;
    const std::unordered_map<std::string_view, double>& GetCosts() const;
    double GetTotalCost() const;

    void AddCost(const std::string_view cost_center_name, double duration);
    void AddSubActivity(Activity& activity); 
    void AddSubActivity(Activity *activity); 

    std::string ToString(int level = 0) const;
private:
    bool IsSubActivity() const;
    void RecalculateTotalCost();

    std::string name;
    Activity *parent;
    std::deque<const Activity *> sub_activities;
    std::unordered_map<std::string_view, 
                       double> costs;
    const std::unordered_map<std::string_view, 
                       const CostCenter *> *cost_centers;
    double total_cost; 
};

using CostCenters = std::unordered_map<std::string_view, const CostCenter *>; 

[[ deprecated ]]
double Calculate(const CostCenters& cost_centers, const Activity& activity);

}