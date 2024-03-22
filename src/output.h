#pragma once

#include "abc_entities.h"
#include <iostream>

class OutputInterface {
public:
    virtual void Output(std::ostream& out, const ABCAnalyzer::Activity& root) = 0;
};

class CSVOutput : public OutputInterface {
public:
    virtual void Output(std::ostream& out, const ABCAnalyzer::Activity& root);
};