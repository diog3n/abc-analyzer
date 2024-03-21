#include "view.h"
#include <string_view>
#include <cassert>

namespace view {

std::string_view TrimSpaces(std::string_view view) {
    assert(!view.empty());

    while (view.front() == ' ') view.remove_prefix(1);
    while (view.back() == ' ') view.remove_suffix(1);

    return view;
}

std::string_view Substr(std::string_view view, 
                        size_t substr_begin, 
                        size_t substr_end) {
    assert(substr_begin < substr_end);
    
    return view.substr(substr_begin, substr_end - substr_begin);
}

std::vector<std::string_view> SplitBy(std::string_view view, char by) {
    std::vector<std::string_view> splits;
    
    while (!view.empty()) {
        const size_t first_of_by = view.find_first_of(by);
        splits.push_back(Substr(view, 0, first_of_by));
        
        if (first_of_by == std::string_view::npos) break;

        view.remove_prefix(1);
    }

    return splits;
}

std::string_view GetFirstWord(std::string_view view) {
    const size_t first_space = view.find_first_of(' ');
    return Substr(view, 0, first_space);
}

std::vector<std::string_view> ParseStrings(std::string_view view) {
    std::vector<std::string_view> strings;
    while (!view.empty()) {
        const size_t first_quote = view.find_first_of('\"');
        
        if (first_quote == std::string_view::npos) break;
        
        view = Substr(view, first_quote, view.length());
        view.remove_prefix(1);

        if (view.empty()) break;

        const size_t second_quote = view.find_first_of('\"');
        strings.push_back(Substr(view, 0, second_quote));

        if (second_quote == std::string_view::npos) break;

        view = Substr(view, second_quote, view.length());
        view.remove_prefix(1);

        if (view.empty()) break;
    }
    return strings;
}

}