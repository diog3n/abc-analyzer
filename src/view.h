#pragma once

#include <string_view>
#include <vector>

namespace view {

std::string_view TrimSpaces(std::string_view view);

std::string_view Substr(std::string_view view, 
                        size_t substr_begin, 
                        size_t substr_end);

std::vector<std::string_view> SplitBy(std::string_view view, char by);

std::string_view GetFirstToken(std::string_view view);

std::string_view GetLastToken(std::string_view view);

std::vector<std::string_view> ParseStrings(std::string_view view);

}